//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2012-2013 LunarG, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

#include "ParseHelper.h"
#include "Scan.h"

#include "osinclude.h"
#include <stdarg.h>
#include <algorithm>

#include "preprocessor/PpContext.h"

extern int yyparse(void*);

namespace glslang {

TParseContext::TParseContext(TSymbolTable& symt, TIntermediate& interm, bool pb, int v, EProfile p, EShLanguage L, TInfoSink& is,
                             bool fc, EShMessages m) :
            intermediate(interm), symbolTable(symt), infoSink(is), language(L),
            version(v), profile(p), forwardCompatible(fc), messages(m),
            contextPragma(true, false), loopNestingLevel(0), controlFlowNestingLevel(0), structNestingLevel(0),
            tokensBeforeEOF(false), limits(resources.limits), currentScanner(0),
            numErrors(0), parsingBuiltins(pb), afterEOF(false),
            anyIndexLimits(false)
{
    // ensure we always have a linkage node, even if empty, to simplify tree topology algorithms
    linkage = new TIntermAggregate;

    // set all precision defaults to EpqNone, which is correct for all desktop types
    // and for ES types that don't have defaults (thus getting an error on use)
    for (int type = 0; type < EbtNumTypes; ++type)
        defaultPrecision[type] = EpqNone;

    for (int type = 0; type < maxSamplerIndex; ++type)
        defaultSamplerPrecision[type] = EpqNone;

    // replace with real defaults for those that have them
    if (profile == EEsProfile) {
        TSampler sampler;
        sampler.set(EbtFloat, Esd2D);
        defaultSamplerPrecision[computeSamplerTypeIndex(sampler)] = EpqLow;
        sampler.set(EbtFloat, EsdCube);
        defaultSamplerPrecision[computeSamplerTypeIndex(sampler)] = EpqLow;
        sampler.set(EbtFloat, Esd2D);
        sampler.external = true;
        defaultSamplerPrecision[computeSamplerTypeIndex(sampler)] = EpqLow;

        switch (language) {
        case EShLangFragment:
            defaultPrecision[EbtInt] = EpqMedium;
            defaultPrecision[EbtUint] = EpqMedium;
            defaultPrecision[EbtSampler] = EpqLow;
            break;
        default:
            defaultPrecision[EbtInt] = EpqHigh;
            defaultPrecision[EbtUint] = EpqHigh;
            defaultPrecision[EbtFloat] = EpqHigh;
            defaultPrecision[EbtSampler] = EpqLow;
            break;
        }
    }

    globalUniformDefaults.clear();
    globalUniformDefaults.layoutMatrix = ElmColumnMajor;
    globalUniformDefaults.layoutPacking = ElpShared;

    globalBufferDefaults.clear();
    globalBufferDefaults.layoutMatrix = ElmColumnMajor;
    globalBufferDefaults.layoutPacking = ElpShared;

    globalInputDefaults.clear();

    globalOutputDefaults.clear();

    // "Shaders in the transform 
    // feedback capturing mode have an initial global default of
    //     layout(xfb_buffer = 0) out;"
    if (language == EShLangVertex ||
        language == EShLangTessControl ||
        language == EShLangTessEvaluation ||
        language == EShLangGeometry)
        globalOutputDefaults.layoutXfbBuffer = 0;

    if (language == EShLangGeometry)
        globalOutputDefaults.layoutStream = 0;
}

void TParseContext::setLimits(const TBuiltInResource& r)
{
    resources = r;

    anyIndexLimits = ! limits.generalAttributeMatrixVectorIndexing ||
                     ! limits.generalConstantMatrixVectorIndexing ||
                     ! limits.generalSamplerIndexing ||
                     ! limits.generalUniformIndexing ||
                     ! limits.generalVariableIndexing ||
                     ! limits.generalVaryingIndexing;

    intermediate.setLimits(resources);
}

//
// Parse an array of strings using yyparse, going through the
// preprocessor to tokenize the shader strings, then through
// the GLSL scanner.
//
// Returns true for successful acceptance of the shader, false if any errors.
//
bool TParseContext::parseShaderStrings(TPpContext& ppContext, TInputScanner& input, bool versionWillBeError)
{
    currentScanner = &input;
    ppContext.setInput(input, versionWillBeError);
    yyparse((void*)this);
    finalErrorCheck();

    return numErrors == 0;
}

// This is called from bison when it has a parse (syntax) error
void TParseContext::parserError(const char* s)
{
    if (afterEOF) {
        if (tokensBeforeEOF == 1)
            error(getCurrentLoc(), "", "pre-mature EOF", s, "");
    } else
        error(getCurrentLoc(), "", "", s, "");
}

void TParseContext::handlePragma(TSourceLoc loc, const TVector<TString>& tokens)
{
    if (tokens.size() == 0)
        return;

    if (tokens[0].compare("optimize") == 0) {
        if (tokens.size() != 4) {
            error(loc, "optimize pragma syntax is incorrect", "#pragma", "");
            return;
        }

        if (tokens[1].compare("(") != 0) {
            error(loc, "\"(\" expected after 'optimize' keyword", "#pragma", "");
            return;
        }

        if (tokens[2].compare("on") == 0)
            contextPragma.optimize = true;
        else if (tokens[2].compare("off") == 0)
            contextPragma.optimize = false;
        else {
            error(loc, "\"on\" or \"off\" expected after '(' for 'optimize' pragma", "#pragma", "");
            return;
        }

        if (tokens[3].compare(")") != 0) {
            error(loc, "\")\" expected to end 'optimize' pragma", "#pragma", "");
            return;
        }
    } else if (tokens[0].compare("debug") == 0) {
        if (tokens.size() != 4) {
            error(loc, "debug pragma syntax is incorrect", "#pragma", "");
            return;
        }

        if (tokens[1].compare("(") != 0) {
            error(loc, "\"(\" expected after 'debug' keyword", "#pragma", "");
            return;
        }

        if (tokens[2].compare("on") == 0)
            contextPragma.debug = true;
        else if (tokens[2].compare("off") == 0)
            contextPragma.debug = false;
        else {
            error(loc, "\"on\" or \"off\" expected after '(' for 'debug' pragma", "#pragma", "");
            return;
        }

        if (tokens[3].compare(")") != 0) {
            error(loc, "\")\" expected to end 'debug' pragma", "#pragma", "");
            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////
//
// Sub- vector and matrix fields
//
////////////////////////////////////////////////////////////////////////

//
// Look at a '.' field selector string and change it into offsets
// for a vector or scalar
//
// Returns true if there is no error.
//
bool TParseContext::parseVectorFields(TSourceLoc loc, const TString& compString, int vecSize, TVectorFields& fields)
{
    fields.num = (int) compString.size();
    if (fields.num > 4) {
        error(loc, "illegal vector field selection", compString.c_str(), "");
        return false;
    }

    enum {
        exyzw,
        ergba,
        estpq,
    } fieldSet[4];

    for (int i = 0; i < fields.num; ++i) {
        switch (compString[i])  {
        case 'x':
            fields.offsets[i] = 0;
            fieldSet[i] = exyzw;
            break;
        case 'r':
            fields.offsets[i] = 0;
            fieldSet[i] = ergba;
            break;
        case 's':
            fields.offsets[i] = 0;
            fieldSet[i] = estpq;
            break;
        case 'y':
            fields.offsets[i] = 1;
            fieldSet[i] = exyzw;
            break;
        case 'g':
            fields.offsets[i] = 1;
            fieldSet[i] = ergba;
            break;
        case 't':
            fields.offsets[i] = 1;
            fieldSet[i] = estpq;
            break;
        case 'z':
            fields.offsets[i] = 2;
            fieldSet[i] = exyzw;
            break;
        case 'b':
            fields.offsets[i] = 2;
            fieldSet[i] = ergba;
            break;
        case 'p':
            fields.offsets[i] = 2;
            fieldSet[i] = estpq;
            break;

        case 'w':
            fields.offsets[i] = 3;
            fieldSet[i] = exyzw;
            break;
        case 'a':
            fields.offsets[i] = 3;
            fieldSet[i] = ergba;
            break;
        case 'q':
            fields.offsets[i] = 3;
            fieldSet[i] = estpq;
            break;
        default:
            error(loc, "illegal vector field selection", compString.c_str(), "");
            return false;
        }
    }

    for (int i = 0; i < fields.num; ++i) {
        if (fields.offsets[i] >= vecSize) {
            error(loc, "vector field selection out of range",  compString.c_str(), "");
            return false;
        }

        if (i > 0) {
            if (fieldSet[i] != fieldSet[i-1]) {
                error(loc, "illegal - vector component fields not from the same set", compString.c_str(), "");
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////
//
// Errors
//
////////////////////////////////////////////////////////////////////////

//
// Used to output syntax, parsing, and semantic errors.
//
void C_DECL TParseContext::error(TSourceLoc loc, const char* szReason, const char* szToken,
                                 const char* szExtraInfoFormat, ...)
{
    const int maxSize = GlslangMaxTokenLength + 200;
    char szExtraInfo[maxSize];
    va_list marker;

    va_start(marker, szExtraInfoFormat);

    safe_vsprintf(szExtraInfo, maxSize, szExtraInfoFormat, marker);

    infoSink.info.prefix(EPrefixError);
    infoSink.info.location(loc);
    infoSink.info << "'" << szToken <<  "' : " << szReason << " " << szExtraInfo << "\n";

    va_end(marker);

    ++numErrors;
}

void C_DECL TParseContext::warn(TSourceLoc loc, const char* szReason, const char* szToken,
                                 const char* szExtraInfoFormat, ...)
{
    if (messages & EShMsgSuppressWarnings)
        return;

    const int maxSize = GlslangMaxTokenLength + 200;
    char szExtraInfo[maxSize];
    va_list marker;

    va_start(marker, szExtraInfoFormat);

    safe_vsprintf(szExtraInfo, maxSize, szExtraInfoFormat, marker);

    infoSink.info.prefix(EPrefixWarning);
    infoSink.info.location(loc);
    infoSink.info << "'" << szToken <<  "' : " << szReason << " " << szExtraInfo << "\n";

    va_end(marker);
}

//
// Handle seeing a variable identifier in the grammar.
//
TIntermTyped* TParseContext::handleVariable(TSourceLoc loc, TSymbol* symbol, TString* string)
{
    TIntermTyped* node = 0;
    bool noteAccess = false;

    // Error check for function requiring specific extensions present.
    if (symbol && symbol->getNumExtensions())
        requireExtensions(loc, symbol->getNumExtensions(), symbol->getExtensions(), symbol->getName().c_str());

    const TAnonMember* anon = symbol ? symbol->getAsAnonMember() : 0;
    if (anon) {
        // it was a member of an anonymous container, have to insert its dereference
        const TVariable* variable = anon->getAnonContainer().getAsVariable();
        TIntermTyped* container = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), loc);
        TConstUnionArray unionArray(1);
        unionArray[0].setUConst(anon->getMemberNumber());
        TIntermTyped* constNode = intermediate.addConstantUnion(unionArray, TType(EbtUint, EvqConst), loc);

        node = intermediate.addIndex(EOpIndexDirectStruct, container, constNode, loc);
        node->setType(*(*variable->getType().getStruct())[anon->getMemberNumber()].type);
        if (node->getBasicType() == EbtVoid)
            error(loc, "member of nameless block was not redeclared", string->c_str(), "");
        if (variable->getType().getQualifier().isIo())
            noteAccess = true;

        // TODO: does this create any accidental type sharing with the built-in level?
    } else {
        // The symbol table search was done in the lexical phase, but
        // if this is a new symbol, it wouldn't have found it.
        TVariable* variable = symbol ? symbol->getAsVariable() : 0;
        if (symbol && ! variable)
            error(loc, "variable name expected", string->c_str(), "");

        if (! variable)
            variable = new TVariable(string, TType(EbtVoid));

        if (variable->getType().getQualifier().storage == EvqConst)
            node = intermediate.addConstantUnion(variable->getConstArray(), variable->getType(), loc);
        else {
            TType* type;
            if (variable->isReadOnly()) {
                type = new TType;
                // break type sharing with built-ins; only costs if there are arrays or structures
                type->deepCopy(variable->getType());
            } else
                type = &variable->getWritableType();
            node = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), *type, loc);
            if (type->getQualifier().isIo())
                noteAccess = true;
        }
    }

    if (noteAccess)
        intermediate.addIoAccessed(*string);

    return node;
}

//
// Handle seeing a base[index] dereference in the grammar.
//
TIntermTyped* TParseContext::handleBracketDereference(TSourceLoc loc, TIntermTyped* base, TIntermTyped* index)
{
    TIntermTyped* result = 0;

    int indexValue = 0;
    if (index->getQualifier().storage == EvqConst) {
        indexValue = index->getAsConstantUnion()->getConstArray()[0].getIConst();
        checkIndex(loc, base->getType(), indexValue);
    }

    variableCheck(base);
    if (! base->isArray() && ! base->isMatrix() && ! base->isVector()) {
        if (base->getAsSymbolNode())
            error(loc, " left of '[' is not of type array, matrix, or vector ", base->getAsSymbolNode()->getName().c_str(), "");
        else
            error(loc, " left of '[' is not of type array, matrix, or vector ", "expression", "");
    } else if (base->getType().getQualifier().storage == EvqConst && index->getQualifier().storage == EvqConst)
        return intermediate.foldDereference(base, indexValue, loc);
    else {
        // at least one of base and index is variable...

        if (base->getAsSymbolNode() && isIoResizeArray(base->getType()))
            handleIoResizeArrayAccess(loc, base);

        if (index->getQualifier().storage == EvqConst) {
            if (base->isArray() && base->getType().getArraySize() == 0)
                updateMaxArraySize(loc, base, indexValue);
            result = intermediate.addIndex(EOpIndexDirect, base, index, loc);
        } else {
            if (base->isArray() && base->getType().getArraySize() == 0) {
                if (base->getAsSymbolNode() && isIoResizeArray(base->getType()))
                    error(loc, "", "[", "array must be sized by a redeclaration or layout qualifier before being indexed with a variable");
                else
                    error(loc, "", "[", "array must be redeclared with a size before being indexed with a variable");
            }
            if (base->getBasicType() == EbtBlock)
                requireProfile(base->getLoc(), ~EEsProfile, "variable indexing block array");
            else if (language == EShLangFragment && base->getQualifier().isPipeOutput())
                requireProfile(base->getLoc(), ~EEsProfile, "variable indexing fragment shader ouput array");
            else if (base->getBasicType() == EbtSampler && version >= 130) {
                const char* explanation = "variable indexing sampler array";
                requireProfile(base->getLoc(), ECoreProfile | ECompatibilityProfile, explanation);
                profileRequires(base->getLoc(), ECoreProfile | ECompatibilityProfile, 400, 0, explanation);
            }

            result = intermediate.addIndex(EOpIndexIndirect, base, index, loc);
        }
    }

    if (result == 0) {
        // Insert dummy error-recovery result
        TConstUnionArray unionArray(1);
        unionArray[0].setDConst(0.0);
        result = intermediate.addConstantUnion(unionArray, TType(EbtFloat, EvqConst), loc);
    } else {
        // Insert valid dereferenced result
        TType newType(base->getType(), 0);  // dereferenced type
        if (base->getType().getQualifier().storage == EvqConst && index->getQualifier().storage == EvqConst)
            newType.getQualifier().storage = EvqConst;
        else
            newType.getQualifier().storage = EvqTemporary;
        result->setType(newType);

        if (anyIndexLimits)
            handleIndexLimits(loc, base, index);
    }

    return result;
}

void TParseContext::checkIndex(TSourceLoc loc, const TType& type, int& index)
{
    if (index < 0) {
        error(loc, "", "[", "index out of range '%d'", index);
        index = 0;
    } else if (type.isArray()) {
        if (type.getArraySize() != 0 && index >= type.getArraySize()) {
            error(loc, "", "[", "array index out of range '%d'", index);
            index = type.getArraySize() - 1;
        }
    } else if (type.isVector()) {
        if (index >= type.getVectorSize()) {
            error(loc, "", "[", "vector index out of range '%d'", index);
            index = type.getVectorSize() - 1;
        }
    } else if (type.isMatrix()) {
        if (index >= type.getMatrixCols()) {
            error(loc, "", "[", "matrix index out of range '%d'", index);
            index = type.getMatrixCols() - 1;
        }
    }           
}

// for ES 2.0 (version 100) limitations for almost all index operations except vertex-shader uniforms
void TParseContext::handleIndexLimits(TSourceLoc loc, TIntermTyped* base, TIntermTyped* index)
{
    if ((! limits.generalSamplerIndexing && base->getBasicType() == EbtSampler) ||
        (! limits.generalUniformIndexing && base->getQualifier().isUniform() && language != EShLangVertex) ||
        (! limits.generalAttributeMatrixVectorIndexing && base->getQualifier().isPipeInput() && language == EShLangVertex && (base->getType().isMatrix() || base->getType().isVector())) ||
        (! limits.generalConstantMatrixVectorIndexing && base->getAsConstantUnion()) ||
        (! limits.generalVariableIndexing && ! base->getType().getQualifier().isUniform() &&
                                             ! base->getType().getQualifier().isPipeInput() &&
                                             ! base->getType().getQualifier().isPipeOutput() &&
                                               base->getType().getQualifier().storage != EvqConst) ||
        (! limits.generalVaryingIndexing && (base->getType().getQualifier().isPipeInput() ||
                                                base->getType().getQualifier().isPipeOutput()))) {
        // it's too early to know what the inductive variables are, save it for post processing
        needsIndexLimitationChecking.push_back(index);
    }
}

// Return true if this is a geometry shader input array or tessellation control output array.
bool TParseContext::isIoResizeArray(const TType& type) const
{
    return type.isArray() &&
           ((language == EShLangGeometry    && type.getQualifier().storage == EvqVaryingIn) ||
            (language == EShLangTessControl && type.getQualifier().storage == EvqVaryingOut && ! type.getQualifier().patch));
}

// If an array is not isIoResizeArray() but is an io array, make sure it has the right size
void TParseContext::fixIoArraySize(TSourceLoc loc, TType& type)
{
    if (! type.isArray() || type.getQualifier().patch || symbolTable.atBuiltInLevel())
        return;

    assert(! isIoResizeArray(type));

    if (type.getQualifier().storage != EvqVaryingIn || type.getQualifier().patch)
        return;

    if (language == EShLangTessControl || language == EShLangTessEvaluation) {
        if (type.getArraySize() != resources.maxPatchVertices) {
            if (type.getArraySize() != 0)
                error(loc, "tessellation input array size must be gl_MaxPatchVertices or unsized", "[]", "");
            type.changeArraySize(resources.maxPatchVertices);
        }
    }
}

// Issue any errors if the non-array object is missing arrayness WRT
// shader I/O that has array requirements.
// All arrayness checking is handled in array paths, this is for 
void TParseContext::ioArrayCheck(TSourceLoc loc, const TType& type, const TString& identifier)
{
    if (! type.isArray() && ! symbolTable.atBuiltInLevel()) {
        if ((language == EShLangGeometry       &&  type.getQualifier().storage == EvqVaryingIn) ||
            (language == EShLangTessControl    && (type.getQualifier().storage == EvqVaryingOut || type.getQualifier().storage == EvqVaryingIn) && ! type.getQualifier().patch) ||
            (language == EShLangTessEvaluation &&  type.getQualifier().storage == EvqVaryingIn && ! type.getQualifier().patch))
            error(loc, "type must be an array:", type.getStorageQualifierString(), identifier.c_str());
    }
}

// Handle a dereference of a geometry shader input array or tessellation control output array.
// See ioArrayNodeResizeList comment in ParseHelper.h.
//
void TParseContext::handleIoResizeArrayAccess(TSourceLoc loc, TIntermTyped* base)
{
    TIntermSymbol* symbol = base->getAsSymbolNode();
    assert(symbol);
    ioArrayNodeResizeList.push_back(symbol);
    if (symbol && builtInName(symbol->getName())) {
        // make sure we have a user-modifiable copy of this built-in input array
        TSymbol* arry = symbolTable.find(symbol->getName());
        if (arry->isReadOnly()) {
            arry = symbolTable.copyUp(arry);

            // fix array size, if already implicitly size
            if (arry->getType().getArraySize() == 0) {
                int newSize = getIoArrayImplicitSize();
                if (newSize) {
                    arry->getWritableType().changeArraySize(newSize);
                    symbol->getWritableType().changeArraySize(newSize);
                }
            }

            ioArraySymbolResizeList.push_back(arry);

            // Save it in the AST for linker use.
            intermediate.addSymbolLinkageNode(linkage, *arry);
        }
    }
}

// If there has been an input primitive declaration (geometry shader) or an output
// number of vertices declaration(tessellation shader), make sure all input array types
// match it in size.  Types come either from nodes in the AST or symbols in the 
// symbol table.
//
// Types without an array size will be given one.
// Types already having a size that is wrong will get an error.
//
void TParseContext::checkIoArraysConsistency(TSourceLoc loc, bool tailOnly)
{
    int requiredSize = getIoArrayImplicitSize();
    if (requiredSize == 0)
        return;

    const char* feature;
    if (language == EShLangGeometry)
        feature = TQualifier::getGeometryString(intermediate.getInputPrimitive());
    else if (language == EShLangTessControl)
        feature = "vertices";

    if (tailOnly) {
        checkIoArrayConsistency(loc, requiredSize, feature, ioArraySymbolResizeList.back()->getWritableType(), ioArraySymbolResizeList.back()->getName());
        return;
    }

    for (size_t i = 0; i < ioArrayNodeResizeList.size(); ++i)
        checkIoArrayConsistency(loc, requiredSize, feature, ioArrayNodeResizeList[i]->getWritableType(), ioArrayNodeResizeList[i]->getName());

    for (size_t i = 0; i < ioArraySymbolResizeList.size(); ++i)
        checkIoArrayConsistency(loc, requiredSize, feature, ioArraySymbolResizeList[i]->getWritableType(), ioArraySymbolResizeList[i]->getName());
}

int TParseContext::getIoArrayImplicitSize() const
{
    if (language == EShLangGeometry)
        return TQualifier::mapGeometryToSize(intermediate.getInputPrimitive());
    else if (language == EShLangTessControl)
        return intermediate.getVertices();
    else
        return 0;
}

void TParseContext::checkIoArrayConsistency(TSourceLoc loc, int requiredSize, const char* feature, TType& type, const TString& name)
{
    if (type.getArraySize() == 0)
        type.changeArraySize(requiredSize);
    else if (type.getArraySize() != requiredSize) {
        if (language == EShLangGeometry)
            error(loc, "inconsistent input primitive for array size of", feature, name.c_str());
        else if (language == EShLangTessControl)
            error(loc, "inconsistent output number of vertices for array size of", feature, name.c_str());
        else
            assert(0);
    }
}

//
// Handle seeing a base.field dereference in the grammar.
//
TIntermTyped* TParseContext::handleDotDereference(TSourceLoc loc, TIntermTyped* base, TString& field)
{
    TIntermTyped* result = base;

    variableCheck(base);
    if (base->isArray()) {
        //
        // It can only be a method (e.g., length), which can't be resolved until
        // we later see the function calling syntax.  Save away the name for now.
        //

        if (field == "length") {
            profileRequires(loc, ENoProfile, 120, GL_3DL_array_objects, ".length");
            profileRequires(loc, EEsProfile, 300, 0, ".length");
            result = intermediate.addMethod(base, TType(EbtInt), &field, loc);
        } else
            error(loc, "only the length method is supported for array", field.c_str(), "");
    } else if (base->isVector() || base->isScalar()) {
        if (base->isScalar()) {
            const char* dotFeature = "scalar swizzle";
            requireProfile(loc, ~EEsProfile, dotFeature);
            profileRequires(loc, ~EEsProfile, 420, GL_ARB_shading_language_420pack, dotFeature);
        }

        TVectorFields fields;
        if (! parseVectorFields(loc, field, base->getVectorSize(), fields)) {
            fields.num = 1;
            fields.offsets[0] = 0;
        }

        if (base->isScalar()) {
            if (fields.num == 1)
                return result;
            else {
                TType type(base->getBasicType(), EvqTemporary, fields.num);
                return addConstructor(loc, base, type, mapTypeToConstructorOp(type));
            }
        }

        if (base->getType().getQualifier().storage == EvqConst)
            result = intermediate.foldSwizzle(base, fields, loc);
        else {
            if (fields.num == 1) {
                TConstUnionArray unionArray(1);
                unionArray[0].setIConst(fields.offsets[0]);
                TIntermTyped* index = intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), loc);
                result = intermediate.addIndex(EOpIndexDirect, base, index, loc);
                result->setType(TType(base->getBasicType(), EvqTemporary, base->getType().getQualifier().precision));
            } else {
                TString vectorString = field;
                TIntermTyped* index = intermediate.addSwizzle(fields, loc);
                result = intermediate.addIndex(EOpVectorSwizzle, base, index, loc);
                result->setType(TType(base->getBasicType(), EvqTemporary, base->getType().getQualifier().precision, (int) vectorString.size()));
            }
        }
    } else if (base->isMatrix())
        error(loc, "field selection not allowed on matrix", ".", "");
    else if (base->getBasicType() == EbtStruct || base->getBasicType() == EbtBlock) {
        TTypeList* fields = base->getType().getStruct();
        bool fieldFound = false;
        unsigned int member;
        for (member = 0; member < fields->size(); ++member) {
            if ((*fields)[member].type->getFieldName() == field) {
                fieldFound = true;
                break;
            }
        }
        if (fieldFound) {
            if (base->getType().getQualifier().storage == EvqConst)
                result = intermediate.foldDereference(base, member, loc);
            else {
                TConstUnionArray unionArray(1);
                unionArray[0].setIConst(member);
                TIntermTyped* index = intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), loc);
                result = intermediate.addIndex(EOpIndexDirectStruct, base, index, loc);
                result->setType(*(*fields)[member].type);
            }
        } else
            error(loc, " no such field in structure", field.c_str(), "");
    } else
        error(loc, " dot operator does not operater on this type:", field.c_str(), base->getType().getCompleteString().c_str());

    return result;
}

//
// Handle seeing a function declarator in the grammar.  This is the precursor
// to recognizing a function prototype or function definition.
//
TFunction* TParseContext::handleFunctionDeclarator(TSourceLoc loc, TFunction& function, bool prototype)
{
    // ES can't declare prototypes inside functions
    if (! symbolTable.atGlobalLevel())
        requireProfile(loc, ~EEsProfile, "local function declaration");

    //
    // Multiple declarations of the same function name are allowed.
    //
    // If this is a definition, the definition production code will check for redefinitions
    // (we don't know at this point if it's a definition or not).
    //
    // Redeclarations (full signature match) are allowed.  But, return types and parameter qualifiers must also match.
    //  - except ES 100, which only allows a single prototype
    //
    // ES 100 does not allow redefining, but does allow overloading of built-in functions.
    // ES 300 does not allow redefining or overloading of built-in functions.
    //
    bool builtIn;
    TSymbol* symbol = symbolTable.find(function.getMangledName(), &builtIn);
    if (symbol && symbol->getAsFunction() && builtIn)
        requireProfile(loc, ~EEsProfile, "redefinition of built-in function");
    const TFunction* prevDec = symbol ? symbol->getAsFunction() : 0;
    if (prevDec) {
        if (prevDec->isPrototyped() && prototype)
            profileRequires(loc, EEsProfile, 300, 0, "multiple prototypes for same function");
        if (prevDec->getType() != function.getType())
            error(loc, "overloaded functions must have the same return type", function.getType().getBasicTypeString().c_str(), "");
        for (int i = 0; i < prevDec->getParamCount(); ++i) {
            if ((*prevDec)[i].type->getQualifier().storage != function[i].type->getQualifier().storage)
                error(loc, "overloaded functions must have the same parameter storage qualifiers for argument", function[i].type->getStorageQualifierString(), "%d", i+1);

            if ((*prevDec)[i].type->getQualifier().precision != function[i].type->getQualifier().precision)
                error(loc, "overloaded functions must have the same parameter precision qualifiers for argument", function[i].type->getPrecisionQualifierString(), "%d", i+1);
        }
    }

    arrayObjectCheck(loc, function.getType(), "array in function return type");

    if (prototype) {
        // All built-in functions are defined, even though they don't have a body.
        // Count their prototype as a definition instead.
        if (symbolTable.atBuiltInLevel())
            function.setDefined();
        else {
            if (prevDec && ! builtIn)                
                symbol->getAsFunction()->setPrototyped();  // need a writable one, but like having prevDec as a const
            function.setPrototyped();
        }
    }

    // This insert won't actually insert it if it's a duplicate signature, but it will still check for
    // other forms of name collisions.
    if (! symbolTable.insert(function))
        error(loc, "function name is redeclaration of existing name", function.getName().c_str(), "");

    //
    // If this is a redeclaration, it could also be a definition,
    // in which case, we need to use the parameter names from this one, and not the one that's
    // being redeclared.  So, pass back this declaration, not the one in the symbol table.
    //
    return &function;
}

//
// Handle seeing the function prototype in front of a function definition in the grammar.  
// The body is handled after this function returns.
//
TIntermAggregate* TParseContext::handleFunctionDefinition(TSourceLoc loc, TFunction& function)
{
    currentCaller = function.getMangledName();
    TSymbol* symbol = symbolTable.find(function.getMangledName());
    TFunction* prevDec = symbol ? symbol->getAsFunction() : 0;

    if (! prevDec)
        error(loc, "can't find function", function.getName().c_str(), "");
    // Note:  'prevDec' could be 'function' if this is the first time we've seen function
    // as it would have just been put in the symbol table.  Otherwise, we're looking up
    // an earlier occurance.

    if (prevDec && prevDec->isDefined()) {
        // Then this function already has a body.
        error(loc, "function already has a body", function.getName().c_str(), "");
    }
    if (prevDec && ! prevDec->isDefined()) {
        prevDec->setDefined();

        // Remember the return type for later checking for RETURN statements.
        currentFunctionType = &(prevDec->getType());
    } else
        currentFunctionType = new TType(EbtVoid);
    functionReturnsValue = false;

    //
    // Raise error message if main function takes any parameters or returns anything other than void
    //
    if (function.getName() == "main") {
        if (function.getParamCount() > 0)
            error(loc, "function cannot take any parameter(s)", function.getName().c_str(), "");
        if (function.getType().getBasicType() != EbtVoid)
            error(loc, "", function.getType().getBasicTypeString().c_str(), "main function cannot return a value");
        intermediate.addMainCount();
    }

    //
    // New symbol table scope for body of function plus its arguments
    //
    symbolTable.push();

    //
    // Insert parameters into the symbol table.
    // If the parameter has no name, it's not an error, just don't insert it
    // (could be used for unused args).
    //
    // Also, accumulate the list of parameters into the HIL, so lower level code
    // knows where to find parameters.
    //
    TIntermAggregate* paramNodes = new TIntermAggregate;
    for (int i = 0; i < function.getParamCount(); i++) {
        TParameter& param = function[i];
        if (param.name != 0) {
            TVariable *variable = new TVariable(param.name, *param.type);

            // Insert the parameters with name in the symbol table.
            if (! symbolTable.insert(*variable))
                error(loc, "redefinition", variable->getName().c_str(), "");
            else {
                // Transfer ownership of name pointer to symbol table.
                param.name = 0;

                // Add the parameter to the HIL
                paramNodes = intermediate.growAggregate(paramNodes,
                                                        intermediate.addSymbol(variable->getUniqueId(),
                                                                               variable->getName(),
                                                                               variable->getType(), loc),
                                                        loc);
            }
        } else
            paramNodes = intermediate.growAggregate(paramNodes, intermediate.addSymbol(0, "", *param.type, loc), loc);
    }
    intermediate.setAggregateOperator(paramNodes, EOpParameters, TType(EbtVoid), loc);
    loopNestingLevel = 0;
    controlFlowNestingLevel = 0;

    return paramNodes;
}

//
// Handle seeing function call syntax in the grammar, which could be any of
//  - .length() method
//  - constructor
//  - a call to a built-in function mapped to an operator
//  - a call to a built-in function that will remain a function call (e.g., texturing)
//  - user function
//  - subroutine call (not implemented yet)
//
TIntermTyped* TParseContext::handleFunctionCall(TSourceLoc loc, TFunction* fnCall, TIntermNode* intermNode)
{
    TIntermTyped* result = 0;

    TOperator op = fnCall->getBuiltInOp();
    if (op == EOpArrayLength)
        result = handleLengthMethod(loc, fnCall, intermNode);
    else if (op != EOpNull) {
        //
        // Then this should be a constructor.
        // Don't go through the symbol table for constructors.
        // Their parameters will be verified algorithmically.
        //
        TType type(EbtVoid);  // use this to get the type back
        if (! constructorError(loc, intermNode, *fnCall, op, type)) {
            //
            // It's a constructor, of type 'type'.
            //
            result = addConstructor(loc, intermNode, type, op);
            if (result == 0)
                error(loc, "cannot construct with these arguments", type.getCompleteString().c_str(), "");
        }
    } else {
        //
        // Find it in the symbol table.
        //
        const TFunction* fnCandidate;
        bool builtIn;
        fnCandidate = findFunction(loc, *fnCall, builtIn);
        if (fnCandidate) {
            // Error check for function requiring specific extensions present.
            if (builtIn && fnCandidate->getNumExtensions())
                requireExtensions(loc, fnCandidate->getNumExtensions(), fnCandidate->getExtensions(), fnCandidate->getName().c_str());

            //
            // A declared function.  But, it might still map to a built-in
            // operation.
            //
            op = fnCandidate->getBuiltInOp();
            if (builtIn && op != EOpNull) {
                // A function call mapped to a built-in operation.
                result = intermediate.addBuiltInFunctionCall(loc, op, fnCandidate->getParamCount() == 1, intermNode, fnCandidate->getType());
                if (result == 0)  {
                    error(intermNode->getLoc(), " wrong operand type", "Internal Error",
                                        "built in unary operator function.  Type: %s",
                                        static_cast<TIntermTyped*>(intermNode)->getCompleteString().c_str());
                }
            } else {
                // This is a function call not mapped to built-in operation
                result = intermediate.setAggregateOperator(intermNode, EOpFunctionCall, fnCandidate->getType(), loc);
                result->getAsAggregate()->setName(fnCandidate->getMangledName());

                // this is how we know whether the given function is a built-in function or a user-defined function
                // if builtIn == false, it's a userDefined -> could be an overloaded built-in function also
                // if builtIn == true, it's definitely a built-in function with EOpNull
                if (! builtIn) {
                    result->getAsAggregate()->setUserDefined();
                    intermediate.addToCallGraph(infoSink, currentCaller, fnCandidate->getMangledName());
                }

                // Make sure storage qualifications work for these arguments.
                TStorageQualifier qual;
                TQualifierList& qualifierList = result->getAsAggregate()->getQualifierList();
                for (int i = 0; i < fnCandidate->getParamCount(); ++i) {
                    qual = (*fnCandidate)[i].type->getQualifier().storage;
                    if (qual == EvqOut || qual == EvqInOut) {
                        if (lValueErrorCheck(result->getLoc(), "assign", result->getAsAggregate()->getSequence()[i]->getAsTyped()))
                            error(intermNode->getLoc(), "Constant value cannot be passed for 'out' or 'inout' parameters.", "Error", "");
                    }
                    qualifierList.push_back(qual);
                }

                if (builtIn)
                    nonOpBuiltInCheck(loc, *fnCandidate, *result->getAsAggregate());
            }
        }
    }

    // generic error recovery
    // TODO: simplification: localize all the error recoveries that look like this, and taking type into account to reduce cascades
    if (result == 0) {
        TConstUnionArray unionArray(1);
        unionArray[0].setDConst(0.0);
        result = intermediate.addConstantUnion(unionArray, TType(EbtFloat, EvqConst), loc);
    }

    return result;
}

// Do all processing handling object.length().
// Return resulting tree node.
TIntermTyped* TParseContext::handleLengthMethod(TSourceLoc loc, TFunction* fnCall, TIntermNode* intermNode)
{
    int length = 0;

    if (fnCall->getParamCount() > 0)
        error(loc, "method does not accept any arguments", fnCall->getName().c_str(), "");
    if (intermNode->getAsTyped() == 0 || ! intermNode->getAsTyped()->getType().isArray())
        error(loc, "", fnCall->getName().c_str(), "can only be applied to an array");
    else if (intermNode->getAsTyped()->getType().getArraySize() == 0) {
        bool implicitlySized = false;
        if (intermNode->getAsSymbolNode() && isIoResizeArray(intermNode->getAsTyped()->getType())) {
            // We could be between a layout declaration that gives a built-in io array implicit size and 
            // a user redeclaration of that array, meaning we have to substitute its implicit size here 
            // without actually redeclaring the array.  (It is an error to use a member before the
            // redeclaration, but not an error to use the array name itself.)
            const TString& name = intermNode->getAsSymbolNode()->getName();
            if (name == "gl_in" || name == "gl_out")
                length = getIoArrayImplicitSize();
        }
        if (length == 0) {
            if (intermNode->getAsSymbolNode() && isIoResizeArray(intermNode->getAsTyped()->getType()))
                error(loc, "", fnCall->getName().c_str(), "array must first be sized by a redeclaration or layout qualifier");
            else
                error(loc, "", fnCall->getName().c_str(), "array must be declared with a size before using this method");
        }
    } else
        length = intermNode->getAsTyped()->getType().getArraySize();

    if (length == 0)
        length = 1;
    TConstUnionArray unionArray(1);
    unionArray[0].setIConst(length);

    return intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), loc);
}
//
// Do additional checking of built-in function calls that were not mapped
// to built-in operations (e.g., texturing functions).
//
// Assumes there has been a semantically correct match to a built-in function.
//
void TParseContext::nonOpBuiltInCheck(TSourceLoc loc, const TFunction& fnCandidate, TIntermAggregate& callNode)
{
    // built-in texturing functions get their return value precision from the precision of the sampler
    if (fnCandidate.getType().getQualifier().precision == EpqNone &&
        fnCandidate.getParamCount() > 0 && fnCandidate[0].type->getBasicType() == EbtSampler)
        callNode.getQualifier().precision = callNode.getAsAggregate()->getSequence()[0]->getAsTyped()->getQualifier().precision;

    if (fnCandidate.getName().compare(0, 7, "texture") == 0) {
        if (fnCandidate.getName().compare(0, 13, "textureGather") == 0) {
            TString featureString = fnCandidate.getName() + "(...)";
            const char* feature = featureString.c_str();
            requireProfile(loc, ~EEsProfile, feature);

            int compArg = -1;  // track which argument, if any, is the constant component argument
            if (fnCandidate.getName().compare("textureGatherOffset") == 0) {
                // GL_ARB_texture_gather is good enough for 2D non-shadow textures with no component argument
                if (fnCandidate[0].type->getSampler().dim == Esd2D && ! fnCandidate[0].type->getSampler().shadow && fnCandidate.getParamCount() == 3)
                    profileRequires(loc, ~EEsProfile, 400, GL_ARB_texture_gather, feature);
                else
                    profileRequires(loc, ~EEsProfile, 400, GL_ARB_gpu_shader5, feature);
                if (! fnCandidate[0].type->getSampler().shadow)
                    compArg = 3;
            } else if (fnCandidate.getName().compare("textureGatherOffsets") == 0) {
                profileRequires(loc, ~EEsProfile, 400, GL_ARB_gpu_shader5, feature);
                if (! fnCandidate[0].type->getSampler().shadow)
                    compArg = 3;
                // check for constant offsets
                int offsetArg = fnCandidate[0].type->getSampler().shadow ? 3 : 2;
                if (! callNode.getSequence()[offsetArg]->getAsConstantUnion())
                    error(loc, "must be a compile-time constant:", feature, "offsets argument");
            } else if (fnCandidate.getName().compare("textureGather") == 0) {
                // More than two arguments needs gpu_shader5, and rectangular or shadow needs gpu_shader5,
                // otherwise, need GL_ARB_texture_gather.
                if (fnCandidate.getParamCount() > 2 || fnCandidate[0].type->getSampler().dim == EsdRect || fnCandidate[0].type->getSampler().shadow) {
                    profileRequires(loc, ~EEsProfile, 400, GL_ARB_gpu_shader5, feature);
                    if (! fnCandidate[0].type->getSampler().shadow)
                        compArg = 2;
                } else
                    profileRequires(loc, ~EEsProfile, 400, GL_ARB_texture_gather, feature);
            }

            if (compArg > 0 && compArg < fnCandidate.getParamCount()) {
                if (callNode.getSequence()[compArg]->getAsConstantUnion()) {
                    int value = callNode.getSequence()[compArg]->getAsConstantUnion()->getConstArray()[0].getIConst();
                    if (value < 0 || value > 3)
                        error(loc, "must be 0, 1, 2, or 3:", feature, "component argument");
                } else
                    error(loc, "must be a compile-time constant:", feature, "component argument");
            }
        } else {
            // this is only for functions not starting "textureGather"...
            if (fnCandidate.getName().find("Offset") != TString::npos) {

                // Handle texture-offset limits checking
                int arg = -1;
                if (fnCandidate.getName().compare("textureOffset") == 0)
                    arg = 2;
                else if (fnCandidate.getName().compare("texelFetchOffset") == 0)
                    arg = 3;
                else if (fnCandidate.getName().compare("textureProjOffset") == 0)
                    arg = 2;
                else if (fnCandidate.getName().compare("textureLodOffset") == 0)
                    arg = 3;
                else if (fnCandidate.getName().compare("textureProjLodOffset") == 0)
                    arg = 3;
                else if (fnCandidate.getName().compare("textureGradOffset") == 0)
                    arg = 4;
                else if (fnCandidate.getName().compare("textureProjGradOffset") == 0)
                    arg = 4;

                if (arg > 0) {
                    if (! callNode.getSequence()[arg]->getAsConstantUnion())
                        error(loc, "argument must be compile-time constant", "texel offset", "");
                    else {
                        const TType& type = callNode.getSequence()[arg]->getAsTyped()->getType();
                        for (int c = 0; c < type.getVectorSize(); ++c) {
                            int offset = callNode.getSequence()[arg]->getAsConstantUnion()->getConstArray()[c].getIConst();
                            if (offset > resources.maxProgramTexelOffset || offset < resources.minProgramTexelOffset)
                                error(loc, "value is out of range:", "texel offset", "[gl_MinProgramTexelOffset, gl_MaxProgramTexelOffset]");
                        }
                    }
                }
            }
        }
    }
}

//
// Handle seeing a built-in-type constructor call in the grammar.
//
TFunction* TParseContext::handleConstructorCall(TSourceLoc loc, TPublicType& publicType)
{
    publicType.qualifier.precision = EpqNone;
    TType type(publicType);

    if (type.isArray()) {
        profileRequires(loc, ENoProfile, 120, GL_3DL_array_objects, "arrayed constructor");
        profileRequires(loc, EEsProfile, 300, 0, "arrayed constructor");
    }

    TOperator op = mapTypeToConstructorOp(type);

    if (op == EOpNull) {
        error(loc, "cannot construct this type", TType::getBasicString(publicType.basicType), "");
        op = EOpConstructFloat;
        publicType.basicType = EbtFloat;
        TType errorType(publicType);
        type.shallowCopy(errorType);
    }

    TString empty("");

    return new TFunction(&empty, type, op);
}

//
// Given a type, find what operation would construct it.
//
TOperator TParseContext::mapTypeToConstructorOp(const TType& type)
{
    if (type.isStruct())
        return EOpConstructStruct;

    TOperator op;
    switch (type.getBasicType()) {
    case EbtFloat:
        if (type.isMatrix()) {
            switch (type.getMatrixCols()) {
            case 2:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructMat2x2; break;
                case 3: op = EOpConstructMat2x3; break;
                case 4: op = EOpConstructMat2x4; break;
                default: break; // some compilers want this
                }
                break;
            case 3:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructMat3x2; break;
                case 3: op = EOpConstructMat3x3; break;
                case 4: op = EOpConstructMat3x4; break;
                default: break; // some compilers want this
                }
                break;
            case 4:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructMat4x2; break;
                case 3: op = EOpConstructMat4x3; break;
                case 4: op = EOpConstructMat4x4; break;
                default: break; // some compilers want this
                }
                break;
            default: break; // some compilers want this
            }
        } else {
            switch(type.getVectorSize()) {
            case 1: op = EOpConstructFloat; break;
            case 2: op = EOpConstructVec2;  break;
            case 3: op = EOpConstructVec3;  break;
            case 4: op = EOpConstructVec4;  break;
            default: break; // some compilers want this
            }
        }
        break;
    case EbtDouble:
        if (type.getMatrixCols()) {
            switch (type.getMatrixCols()) {
            case 2:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructDMat2x2; break;
                case 3: op = EOpConstructDMat2x3; break;
                case 4: op = EOpConstructDMat2x4; break;
                default: break; // some compilers want this
                }
                break;
            case 3:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructDMat3x2; break;
                case 3: op = EOpConstructDMat3x3; break;
                case 4: op = EOpConstructDMat3x4; break;
                default: break; // some compilers want this
                }
                break;
            case 4:
                switch (type.getMatrixRows()) {
                case 2: op = EOpConstructDMat4x2; break;
                case 3: op = EOpConstructDMat4x3; break;
                case 4: op = EOpConstructDMat4x4; break;
                default: break; // some compilers want this
                }
                break;
            }
        } else {
            switch(type.getVectorSize()) {
            case 1: op = EOpConstructDouble; break;
            case 2: op = EOpConstructDVec2;  break;
            case 3: op = EOpConstructDVec3;  break;
            case 4: op = EOpConstructDVec4;  break;
            default: break; // some compilers want this
            }
        }
        break;
    case EbtInt:
        switch(type.getVectorSize()) {
        case 1: op = EOpConstructInt;   break;
        case 2: op = EOpConstructIVec2; break;
        case 3: op = EOpConstructIVec3; break;
        case 4: op = EOpConstructIVec4; break;
        default: break; // some compilers want this
        }
        break;
    case EbtUint:
        switch(type.getVectorSize()) {
        case 1: op = EOpConstructUint;  break;
        case 2: op = EOpConstructUVec2; break;
        case 3: op = EOpConstructUVec3; break;
        case 4: op = EOpConstructUVec4; break;
        default: break; // some compilers want this
        }
        break;
    case EbtBool:
        switch(type.getVectorSize()) {
        case 1:  op = EOpConstructBool;  break;
        case 2:  op = EOpConstructBVec2; break;
        case 3:  op = EOpConstructBVec3; break;
        case 4:  op = EOpConstructBVec4; break;
        default: break; // some compilers want this
        }
        break;
    default:
        op = EOpNull;
        break;
    }

    return op;
}

//
// Same error message for all places assignments don't work.
//
void TParseContext::assignError(TSourceLoc loc, const char* op, TString left, TString right)
{
    error(loc, "", op, "cannot convert from '%s' to '%s'",
          right.c_str(), left.c_str());
}

//
// Same error message for all places unary operations don't work.
//
void TParseContext::unaryOpError(TSourceLoc loc, const char* op, TString operand)
{
   error(loc, " wrong operand type", op,
          "no operation '%s' exists that takes an operand of type %s (or there is no acceptable conversion)",
          op, operand.c_str());
}

//
// Same error message for all binary operations don't work.
//
void TParseContext::binaryOpError(TSourceLoc loc, const char* op, TString left, TString right)
{
    error(loc, " wrong operand types:", op,
            "no operation '%s' exists that takes a left-hand operand of type '%s' and "
            "a right operand of type '%s' (or there is no acceptable conversion)",
            op, left.c_str(), right.c_str());
}

//
// A basic type of EbtVoid is a key that the name string was seen in the source, but
// it was not found as a variable in the symbol table.  If so, give the error
// message and insert a dummy variable in the symbol table to prevent future errors.
//
void TParseContext::variableCheck(TIntermTyped*& nodePtr)
{
    TIntermSymbol* symbol = nodePtr->getAsSymbolNode();
    if (! symbol)
        return;

    if (symbol->getType().getBasicType() == EbtVoid) {
        error(symbol->getLoc(), "undeclared identifier", symbol->getName().c_str(), "");

        // Add to symbol table to prevent future error messages on the same name

        TVariable* fakeVariable = new TVariable(&symbol->getName(), TType(EbtFloat));
        symbolTable.insert(*fakeVariable);

        // substitute a symbol node for this new variable
        nodePtr = intermediate.addSymbol(fakeVariable->getUniqueId(),
                                         fakeVariable->getName(),
                                         fakeVariable->getType(), symbol->getLoc());
    } else {
        switch (symbol->getQualifier().storage) {
        case EvqPointCoord:
            profileRequires(symbol->getLoc(), ENoProfile, 120, 0, "gl_PointCoord");
            break;
        default: break; // some compilers want this
        }
    }
}

//
// Both test and if necessary, spit out an error, to see if the node is really
// an l-value that can be operated on this way.
//
// Returns true if the was an error.
//
bool TParseContext::lValueErrorCheck(TSourceLoc loc, const char* op, TIntermTyped* node)
{
    TIntermSymbol* symNode = node->getAsSymbolNode();
    TIntermBinary* binaryNode = node->getAsBinaryNode();

    if (binaryNode) {
        bool errorReturn;

        switch(binaryNode->getOp()) {
        case EOpIndexDirect:
        case EOpIndexIndirect:
        case EOpIndexDirectStruct:
            return lValueErrorCheck(loc, op, binaryNode->getLeft());
        case EOpVectorSwizzle:
            errorReturn = lValueErrorCheck(loc, op, binaryNode->getLeft());
            if (!errorReturn) {
                int offset[4] = {0,0,0,0};

                TIntermTyped* rightNode = binaryNode->getRight();
                TIntermAggregate *aggrNode = rightNode->getAsAggregate();

                for (TIntermSequence::iterator p = aggrNode->getSequence().begin();
                                               p != aggrNode->getSequence().end(); p++) {
                    int value = (*p)->getAsTyped()->getAsConstantUnion()->getConstArray()[0].getIConst();
                    offset[value]++;
                    if (offset[value] > 1) {
                        error(loc, " l-value of swizzle cannot have duplicate components", op, "", "");

                        return true;
                    }
                }
            }

            return errorReturn;
        default:
            break;
        }
        error(loc, " l-value required", op, "", "");

        return true;
    }


    const char* symbol = 0;
    if (symNode != 0)
        symbol = symNode->getName().c_str();

    const char* message = 0;
    switch (node->getQualifier().storage) {
    case EvqConst:          message = "can't modify a const";        break;
    case EvqConstReadOnly:  message = "can't modify a const";        break;
    case EvqVaryingIn:      message = "can't modify shader input";   break;
    case EvqUniform:        message = "can't modify a uniform";      break;
    case EvqInstanceId:     message = "can't modify gl_InstanceID";  break;
    case EvqVertexId:       message = "can't modify gl_VertexID";    break;
    case EvqFace:           message = "can't modify gl_FrontFace";   break;
    case EvqFragCoord:      message = "can't modify gl_FragCoord";   break;
    case EvqPointCoord:     message = "can't modify gl_PointCoord";  break;
    default:

        //
        // Type that can't be written to?
        //
        switch (node->getBasicType()) {
        case EbtSampler:
            message = "can't modify a sampler";
            break;
        case EbtVoid:
            message = "can't modify void";
            break;
        default:
            break;
        }
    }

    if (message == 0 && binaryNode == 0 && symNode == 0) {
        error(loc, " l-value required", op, "", "");

        return true;
    }


    //
    // Everything else is okay, no error.
    //
    if (message == 0)
        return false;

    //
    // If we get here, we have an error and a message.
    //
    if (symNode)
        error(loc, " l-value required", op, "\"%s\" (%s)", symbol, message);
    else
        error(loc, " l-value required", op, "(%s)", message);

    return true;
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// a constant.
//
void TParseContext::constantValueCheck(TIntermTyped* node, const char* token)
{
    if (node->getQualifier().storage != EvqConst)
        error(node->getLoc(), "constant expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// an integer.
//
void TParseContext::integerCheck(const TIntermTyped* node, const char* token)
{
    if ((node->getBasicType() == EbtInt || node->getBasicType() == EbtUint) && node->isScalar())
        return;

    error(node->getLoc(), "scalar integer expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if we are currently
// globally scoped.
//
void TParseContext::globalCheck(TSourceLoc loc, const char* token)
{
    if (! symbolTable.atGlobalLevel())
        error(loc, "not allowed in nested scope", token, "");
}

//
// Reserved errors for GLSL.
//
void TParseContext::reservedErrorCheck(TSourceLoc loc, const TString& identifier)
{
    // "Identifiers starting with "gl_" are reserved for use by OpenGL, and may not be
    // declared in a shader; this results in a compile-time error."
    if (! symbolTable.atBuiltInLevel()) {
        if (builtInName(identifier))
            error(loc, "identifiers starting with \"gl_\" are reserved", identifier.c_str(), "");

        // "In addition, all identifiers containing two consecutive underscores (__) are
        // reserved; using such a name does not itself result in an error, but may result
        // in undefined behavior."
        if (identifier.find("__") != TString::npos)
            warn(loc, "identifiers containing consecutive underscores (\"__\") are reserved", identifier.c_str(), "");
    }
}

//
// Reserved errors for the preprocessor.
//
void TParseContext::reservedPpErrorCheck(TSourceLoc loc, const char* identifier, const char* op)
{
    // "All macro names containing two consecutive underscores ( __ ) are reserved;
    // defining such a name does not itself result in an error, but may result in
    // undefined behavior.  All macro names prefixed with "GL_" ("GL" followed by a
    // single underscore) are also reserved, and defining such a name results in a
    // compile-time error."
    if (strncmp(identifier, "GL_", 3) == 0)
        error(loc, "names beginning with \"GL_\" can't be defined:", op,  identifier);
    else if (strstr(identifier, "__") != 0)
        warn(loc, "names containing consecutive underscores are reserved:", op, identifier);
}

//
// See if this version/profile allows use of the line-continuation character '\'.
//
// Returns true if a line continuation should be done.
//
bool TParseContext::lineContinuationCheck(TSourceLoc loc, bool endOfComment)
{
    const char* message = "line continuation";

    bool lineContinuationAllowed = (profile == EEsProfile && version >= 300) ||
                                   (profile != EEsProfile && version >= 420);

    if (endOfComment) {
        if (lineContinuationAllowed)
            warn(loc, "used at end of comment; the following line is still part of the comment", message, "");
        else
            warn(loc, "used at end of comment, but this version does not provide line continuation", message, "");

        return lineContinuationAllowed;
    }

    if (messages & EShMsgRelaxedErrors) {
        warn(loc, "not allowed in this version", message, "");
        return true;
    } else {
        requireProfile(loc, EEsProfile | ECoreProfile | ECompatibilityProfile, message);
        profileRequires(loc, EEsProfile, 300, 0, message);
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 420, 0, message);
    }

    return lineContinuationAllowed;
}

bool TParseContext::builtInName(const TString& identifier)
{
    return identifier.compare(0, 3, "gl_") == 0;
}

//
// Make sure there is enough data provided to the constructor to build
// something of the type of the constructor.  Also returns the type of
// the constructor.
//
// Returns true if there was an error in construction.
//
bool TParseContext::constructorError(TSourceLoc loc, TIntermNode* node, TFunction& function, TOperator op, TType& type)
{
    type.shallowCopy(function.getType());

    bool constructingMatrix = false;
    switch(op) {
    case EOpConstructMat2x2:
    case EOpConstructMat2x3:
    case EOpConstructMat2x4:
    case EOpConstructMat3x2:
    case EOpConstructMat3x3:
    case EOpConstructMat3x4:
    case EOpConstructMat4x2:
    case EOpConstructMat4x3:
    case EOpConstructMat4x4:
    case EOpConstructDMat2x2:
    case EOpConstructDMat2x3:
    case EOpConstructDMat2x4:
    case EOpConstructDMat3x2:
    case EOpConstructDMat3x3:
    case EOpConstructDMat3x4:
    case EOpConstructDMat4x2:
    case EOpConstructDMat4x3:
    case EOpConstructDMat4x4:
        constructingMatrix = true;
        break;
    default:
        break;
    }

    //
    // Note: It's okay to have too many components available, but not okay to have unused
    // arguments.  'full' will go to true when enough args have been seen.  If we loop
    // again, there is an extra argument, so 'overfull' will become true.
    //

    int size = 0;
    bool constType = true;
    bool full = false;
    bool overFull = false;
    bool matrixInMatrix = false;
    bool arrayArg = false;
    for (int i = 0; i < function.getParamCount(); ++i) {
        size += function[i].type->computeNumComponents();

        if (constructingMatrix && function[i].type->isMatrix())
            matrixInMatrix = true;
        if (full)
            overFull = true;
        if (op != EOpConstructStruct && ! type.isArray() && size >= type.computeNumComponents())
            full = true;
        if (function[i].type->getQualifier().storage != EvqConst)
            constType = false;
        if (function[i].type->isArray())
            arrayArg = true;
    }

    if (constType)
        type.getQualifier().storage = EvqConst;

    if (type.isArray()) {
        if (type.getArraySize() == 0) {
            // auto adapt the constructor type to the number of arguments
            type.changeArraySize(function.getParamCount());
        } else if (type.getArraySize() != function.getParamCount()) {
            error(loc, "array constructor needs one argument per array element", "constructor", "");
            return true;
        }
    }

    if (arrayArg && op != EOpConstructStruct) {
        error(loc, "constructing from a non-dereferenced array", "constructor", "");
        return true;
    }

    if (matrixInMatrix && ! type.isArray()) {
        profileRequires(loc, ENoProfile, 120, 0, "constructing matrix from matrix");
        return false;
    }

    if (overFull) {
        error(loc, "too many arguments", "constructor", "");
        return true;
    }

    if (op == EOpConstructStruct && ! type.isArray() && type.getStruct()->size() != function.getParamCount()) {
        error(loc, "Number of constructor parameters does not match the number of structure fields", "constructor", "");
        return true;
    }

    if ((op != EOpConstructStruct && size != 1 && size < type.computeNumComponents()) ||
        (op == EOpConstructStruct && size < type.computeNumComponents())) {
        error(loc, "not enough data provided for construction", "constructor", "");
        return true;
    }

    TIntermTyped* typed = node->getAsTyped();
    if (typed == 0) {
        error(loc, "constructor argument does not have a type", "constructor", "");
        return true;
    }
    if (op != EOpConstructStruct && typed->getBasicType() == EbtSampler) {
        error(loc, "cannot convert a sampler", "constructor", "");
        return true;
    }
    if (typed->getBasicType() == EbtVoid) {
        error(loc, "cannot convert a void", "constructor", "");
        return true;
    }

    return false;
}

// Checks to see if a void variable has been declared and raise an error message for such a case
//
// returns true in case of an error
//
bool TParseContext::voidErrorCheck(TSourceLoc loc, const TString& identifier, const TBasicType basicType)
{
    if (basicType == EbtVoid) {
        error(loc, "illegal use of type 'void'", identifier.c_str(), "");
        return true;
    }

    return false;
}

// Checks to see if the node (for the expression) contains a scalar boolean expression or not
void TParseContext::boolCheck(TSourceLoc loc, const TIntermTyped* type)
{
    if (type->getBasicType() != EbtBool || type->isArray() || type->isMatrix() || type->isVector())
        error(loc, "boolean expression expected", "", "");
}

// This function checks to see if the node (for the expression) contains a scalar boolean expression or not
void TParseContext::boolCheck(TSourceLoc loc, const TPublicType& pType)
{
    if (pType.basicType != EbtBool || pType.arraySizes || pType.matrixCols > 1 || (pType.vectorSize > 1))
        error(loc, "boolean expression expected", "", "");
}

void TParseContext::samplerCheck(TSourceLoc loc, const TType& type, const TString& identifier)
{
    if (type.getQualifier().storage == EvqUniform)
        return;

    if (type.getBasicType() == EbtStruct && containsSampler(type))
        error(loc, "non-uniform struct contains a sampler or image:", type.getBasicTypeString().c_str(), identifier.c_str());
    else if (type.getBasicType() == EbtSampler && type.getQualifier().storage != EvqUniform)
        error(loc, "sampler/image types can only be used in uniform variables or function parameters:", type.getBasicTypeString().c_str(), identifier.c_str());
}

//
// move from parameter/unknown qualifiers to pipeline in/out qualifiers
//
void TParseContext::pipeInOutFix(TSourceLoc loc, TQualifier& qualifier)
{
    switch (qualifier.storage) {
    case EvqIn:
        profileRequires(loc, ENoProfile, 130, 0, "in for stage inputs");
        profileRequires(loc, EEsProfile, 300, 0, "in for stage inputs");
        qualifier.storage = EvqVaryingIn;
        break;
    case EvqOut:
        profileRequires(loc, ENoProfile, 130, 0, "out for stage outputs");
        profileRequires(loc, EEsProfile, 300, 0, "out for stage outputs");
        qualifier.storage = EvqVaryingOut;
        break;
    case EvqInOut:
        qualifier.storage = EvqVaryingIn;
        error(loc, "cannot use 'inout' at global scope", "", "");
        break;
    default:
        break;
    }
}

void TParseContext::globalQualifierCheck(TSourceLoc loc, const TQualifier& qualifier, const TPublicType& publicType)
{
    if (! symbolTable.atGlobalLevel())
        return;

    if (qualifier.storage != EvqVaryingIn && qualifier.storage != EvqVaryingOut)
        return;

    // now, knowing it is a shader in/out, do all the in/out semantic checks

    if (publicType.basicType == EbtBool) {
        error(loc, "cannot be bool", GetStorageQualifierString(qualifier.storage), "");

        return;
    }

    if (publicType.basicType == EbtInt || publicType.basicType == EbtUint || publicType.basicType == EbtDouble) {
        profileRequires(loc, EEsProfile, 300, 0, "shader input/output");
        if (! qualifier.flat) {
            if (qualifier.storage == EvqVaryingIn && language == EShLangFragment)
                error(loc, "must be qualified as flat", TType::getBasicString(publicType.basicType), GetStorageQualifierString(qualifier.storage));
            else if (qualifier.storage == EvqVaryingOut && language == EShLangVertex && version == 300)
                error(loc, "must be qualified as flat", TType::getBasicString(publicType.basicType), GetStorageQualifierString(qualifier.storage));
        }
    }

    if (qualifier.patch && qualifier.isInterpolation())
        error(loc, "cannot use interpolation qualifiers with patch", "patch", "");

    if (qualifier.storage == EvqVaryingIn) {
        switch (language) {
        case EShLangVertex:
            if (publicType.basicType == EbtStruct) {
                error(loc, "cannot be a structure or array", GetStorageQualifierString(qualifier.storage), "");
                return;
            }
            if (publicType.arraySizes) {
                requireProfile(loc, ~EEsProfile, "vertex input arrays");
                profileRequires(loc, ENoProfile, 150, 0, "vertex input arrays");
            }
            if (qualifier.isAuxiliary() || qualifier.isInterpolation() || qualifier.isMemory() || qualifier.invariant)
                error(loc, "vertex input cannot be further qualified", "", "");
            break;

        case EShLangTessControl:
            if (qualifier.patch)
                error(loc, "can only use on output in tessellation-control shader", "patch", "");
            break;

        case EShLangTessEvaluation:
            break;

        case EShLangGeometry:
            break;

        case EShLangFragment:
            if (publicType.userDef) {
                profileRequires(loc, EEsProfile, 300, 0, "fragment-shader struct input");
                profileRequires(loc, ~EEsProfile, 150, 0, "fragment-shader struct input");
            }
            break;

        case EShLangCompute:
            break;

        default:
            break;
        }
    } else {
        // qualifier.storage == EvqVaryingOut
        switch (language) {
        case EShLangVertex:
            if (publicType.userDef) {
                profileRequires(loc, EEsProfile, 300, 0, "vertex-shader struct output");
                profileRequires(loc, ~EEsProfile, 150, 0, "vertex-shader struct output");
            }
            break;

        case EShLangTessControl:
            break;

        case EShLangTessEvaluation:
            if (qualifier.patch)
                error(loc, "can only use on input in tessellation-evaluation shader", "patch", "");
            break;

        case EShLangGeometry:
            break;

        case EShLangFragment:
            profileRequires(loc, EEsProfile, 300, 0, "fragment shader output");
            if (publicType.basicType == EbtStruct) {
                error(loc, "cannot be a structure", GetStorageQualifierString(qualifier.storage), "");

                return;
            }
            break;

        case EShLangCompute:
            break;

        default:
            break;
        }
    }
}

//
// Merge characteristics of the 'src' qualifier into the 'dst'.
// If there is duplication, issue error messages, unless 'force'
// is specified, which means to just override default settings.
//
// Also, when force is false, it will be assumed that 'src' follows
// 'dst', for the purpose of error checking order for versions
// that require specific orderings of qualifiers.
//
void TParseContext::mergeQualifiers(TSourceLoc loc, TQualifier& dst, const TQualifier& src, bool force)
{
    // Multiple auxiliary qualifiers (mostly done later by 'individual qualifiers')
    if (src.isAuxiliary() && dst.isAuxiliary())
        error(loc, "can only have one auxiliary qualifier (centroid, patch, and sample)", "", "");

    // Multiple interpolation qualifiers (mostly done later by 'individual qualifiers')
    if (src.isInterpolation() && dst.isInterpolation())
        error(loc, "can only have one interpolation qualifier (flat, smooth, noperspective)", "", "");

    // Ordering
    if (! force && version < 420 && ! extensionsTurnedOn(1, &GL_ARB_shading_language_420pack)) {
        // non-function parameters
        if (src.invariant && (dst.isInterpolation() || dst.isAuxiliary() || dst.storage != EvqTemporary || dst.precision != EpqNone))
            error(loc, "invariant qualifier must appear first", "", "");
        else if (src.isInterpolation() && (dst.isAuxiliary() || dst.storage != EvqTemporary || dst.precision != EpqNone))
            error(loc, "interpolation qualifiers must appear before storage and precision qualifiers", "", "");
        else if (src.isAuxiliary() && (dst.storage != EvqTemporary || dst.precision != EpqNone))
            error(loc, "Auxiliary qualifiers (centroid, patch, and sample) must appear before storage and precision qualifiers", "", "");
        else if (src.storage != EvqTemporary && (dst.precision != EpqNone))
            error(loc, "precision qualifier must appear as last qualifier", "", "");

        // function parameters
        if (src.storage == EvqConst && (dst.storage == EvqIn || dst.storage == EvqOut))
            error(loc, "in/out must appear before const", "", "");
    }

    // Storage qualification
    if (dst.storage == EvqTemporary || dst.storage == EvqGlobal)
        dst.storage = src.storage;
    else if ((dst.storage == EvqIn  && src.storage == EvqOut) ||
             (dst.storage == EvqOut && src.storage == EvqIn))
        dst.storage = EvqInOut;
    else if ((dst.storage == EvqIn    && src.storage == EvqConst) ||
             (dst.storage == EvqConst && src.storage == EvqIn))
        dst.storage = EvqConstReadOnly;
    else if (src.storage != EvqTemporary)
        error(loc, "too many storage qualifiers", GetStorageQualifierString(src.storage), "");

    // Precision qualifiers
    if (! force && src.precision != EpqNone && dst.precision != EpqNone)
        error(loc, "only one precision qualifier allowed", GetPrecisionQualifierString(src.precision), "");
    if (dst.precision == EpqNone || (force && src.precision != EpqNone))
        dst.precision = src.precision;

    // Layout qualifiers
    mergeObjectLayoutQualifiers(loc, dst, src, false);

    // individual qualifiers
    bool repeated = false;
    #define MERGE_SINGLETON(field) repeated |= dst.field && src.field; dst.field |= src.field;
    MERGE_SINGLETON(invariant);
    MERGE_SINGLETON(centroid);
    MERGE_SINGLETON(smooth);
    MERGE_SINGLETON(flat);
    MERGE_SINGLETON(nopersp);
    MERGE_SINGLETON(patch);
    MERGE_SINGLETON(sample);
    MERGE_SINGLETON(shared);
    MERGE_SINGLETON(coherent);
    MERGE_SINGLETON(volatil);
    MERGE_SINGLETON(restrict);
    MERGE_SINGLETON(readonly);
    MERGE_SINGLETON(writeonly);

    if (repeated)
        error(loc, "replicated qualifiers", "", "");
}

void TParseContext::setDefaultPrecision(TSourceLoc loc, TPublicType& publicType, TPrecisionQualifier qualifier)
{
    TBasicType basicType = publicType.basicType;

    if (basicType == EbtSampler) {
        defaultSamplerPrecision[computeSamplerTypeIndex(publicType.sampler)] = qualifier;

        return;  // all is well
    }

    if (basicType == EbtInt || basicType == EbtFloat) {
        if (publicType.isScalar()) {
            defaultPrecision[basicType] = qualifier;
            if (basicType == EbtInt)
                defaultPrecision[EbtUint] = qualifier;

            return;  // all is well
        }
    }

    error(loc, "cannot apply precision statement to this type; use 'float', 'int' or a sampler type", TType::getBasicString(basicType), "");
}

// used to flatten the sampler type space into a single dimension
// correlates with the declaration of defaultSamplerPrecision[]
int TParseContext::computeSamplerTypeIndex(TSampler& sampler)
{
    int arrayIndex   = sampler.arrayed   ? 1 : 0;
    int shadowIndex   = sampler.shadow   ? 1 : 0;
    int externalIndex = sampler.external ? 1 : 0;

    return EsdNumDims * (EbtNumTypes * (2 * (2 * arrayIndex + shadowIndex) + externalIndex) + sampler.type) + sampler.dim;
}

TPrecisionQualifier TParseContext::getDefaultPrecision(TPublicType& publicType)
{
    if (publicType.basicType == EbtSampler)
        return defaultSamplerPrecision[computeSamplerTypeIndex(publicType.sampler)];
    else
        return defaultPrecision[publicType.basicType];
}

void TParseContext::precisionQualifierCheck(TSourceLoc loc, TPublicType& publicType)
{
    // Built-in symbols are allowed some ambiguous precisions, to be pinned down
    // later by context.
    if (profile != EEsProfile || parsingBuiltins)
        return;

    if (publicType.basicType == EbtFloat || publicType.basicType == EbtUint || publicType.basicType == EbtInt || publicType.basicType == EbtSampler) {
        if (publicType.qualifier.precision == EpqNone) {
            if (messages & EShMsgRelaxedErrors)
                warn(loc, "type requires declaration of default precision qualifier", TType::getBasicString(publicType.basicType), "substituting 'mediump'");
            else
                error(loc, "type requires declaration of default precision qualifier", TType::getBasicString(publicType.basicType), "");
            publicType.qualifier.precision = EpqMedium;
            defaultPrecision[publicType.basicType] = EpqMedium;
        }
    } else if (publicType.qualifier.precision != EpqNone)
        error(loc, "type cannot have precision qualifier", TType::getBasicString(publicType.basicType), "");
}

void TParseContext::parameterSamplerCheck(TSourceLoc loc, TStorageQualifier qualifier, const TType& type)
{
    if ((qualifier == EvqOut || qualifier == EvqInOut) && type.getBasicType() != EbtStruct && type.getBasicType() == EbtSampler)
        error(loc, "samplers cannot be output parameters", type.getBasicTypeString().c_str(), "");
}

bool TParseContext::containsSampler(const TType& type)
{
    if (type.getBasicType() == EbtSampler)
        return true;

    if (type.getBasicType() == EbtStruct) {
        TTypeList& structure = *type.getStruct();
        for (unsigned int i = 0; i < structure.size(); ++i) {
            if (containsSampler(*structure[i].type))
                return true;
        }
    }

    return false;
}

//
// Do size checking for an array type's size.
//
void TParseContext::arraySizeCheck(TSourceLoc loc, TIntermTyped* expr, int& size)
{
    TIntermConstantUnion* constant = expr->getAsConstantUnion();
    if (constant == 0 || (constant->getBasicType() != EbtInt && constant->getBasicType() != EbtUint)) {
        error(loc, "array size must be a constant integer expression", "", "");
        size = 1;

        return;
    }

    size = constant->getConstArray()[0].getIConst();

    if (size <= 0) {
        error(loc, "array size must be a positive integer", "", "");
        size = 1;

        return;
    }
}

//
// See if this qualifier can be an array.
//
// Returns true if there is an error.
//
bool TParseContext::arrayQualifierError(TSourceLoc loc, const TQualifier& qualifier)
{
    if (qualifier.storage == EvqConst) {
        profileRequires(loc, ENoProfile, 120, GL_3DL_array_objects, "const array");
        profileRequires(loc, EEsProfile, 300, 0, "const array");
    }

    if (qualifier.storage == EvqVaryingIn && language == EShLangVertex) {
        requireProfile(loc, ~EEsProfile, "vertex input arrays");
        profileRequires(loc, ENoProfile, 150, 0, "vertex input arrays");
    }

    return false;
}

//
// Require array to have size
//
void TParseContext::arraySizeRequiredCheck(TSourceLoc loc, int size)
{
    if (size == 0) {
        error(loc, "array size required", "", "");
        size = 1;
    }
}

void TParseContext::arrayDimError(TSourceLoc loc)
{
    requireProfile(loc, ECoreProfile | ECompatibilityProfile, "arrays of arrays");
    profileRequires(loc, ECoreProfile | ECompatibilityProfile, 430, 0, "arrays of arrays");
}

void TParseContext::arrayDimCheck(TSourceLoc loc, TArraySizes* sizes1, TArraySizes* sizes2)
{
    if ((sizes1 && sizes2) ||
        (sizes1 && sizes1->isArrayOfArrays()) ||
        (sizes2 && sizes2->isArrayOfArrays()))
        arrayDimError(loc);
}

void TParseContext::arrayDimCheck(TSourceLoc loc, const TType* type, TArraySizes* sizes2)
{
    if ((type && type->isArray() && sizes2) ||
        (sizes2 && sizes2->isArrayOfArrays()))
        arrayDimError(loc);
}

//
// Do all the semantic checking for declaring an array, with and
// without a size, and make the right changes to the symbol table.
//
// size == 0 means no specified size.
//
void TParseContext::declareArray(TSourceLoc loc, TString& identifier, const TType& type, TSymbol*& symbol, bool& newDeclaration)
{
    if (! symbol) {
        bool currentScope;
        symbol = symbolTable.find(identifier, 0, &currentScope);
        if (symbol == 0 || ! currentScope) {
            //
            // Successfully process a new definition.
            // (Redeclarations have to take place at the same scope; otherwise they are hiding declarations)
            //
            symbol = new TVariable(&identifier, type);
            symbolTable.insert(*symbol);
            newDeclaration = true;

            if (! symbolTable.atBuiltInLevel()) {
                if (isIoResizeArray(type)) {
                    ioArraySymbolResizeList.push_back(symbol);
                    checkIoArraysConsistency(loc, true);
                } else
                    fixIoArraySize(loc, symbol->getWritableType());
            }

            return;
        }
        if (symbol->getAsAnonMember()) {
            error(loc, "cannot redeclare a user-block member array", identifier.c_str(), "");
            symbol = 0;
            return;
        }
    }

    //
    // Process a redeclaration.
    //

    if (! symbol) {
        error(loc, "array variable name expected", identifier.c_str(), "");
        return;
    }

    TType& newType = symbol->getWritableType();

    if (! newType.isArray()) {
        error(loc, "redeclaring non-array as array", identifier.c_str(), "");
        return;
    }
    if (newType.getArraySize() > 0) {
        // be more leniant for input arrays to geometry shaders and tessellation control outputs, where the redeclaration is the same size
        if (! (isIoResizeArray(type) && newType.getArraySize() == type.getArraySize()))
            error(loc, "redeclaration of array with size", identifier.c_str(), "");
        return;
    }

    if (! newType.sameElementType(type)) {
        error(loc, "redeclaration of array with a different type", identifier.c_str(), "");
        return;
    }

    arrayLimitCheck(loc, identifier, type.getArraySize());

    newType.shareArraySizes(type);

    if (isIoResizeArray(type))
        checkIoArraysConsistency(loc);
}

void TParseContext::updateMaxArraySize(TSourceLoc loc, TIntermNode *node, int index)
{
    // maybe there is nothing to do...
    TIntermTyped* typedNode = node->getAsTyped();
    if (typedNode->getType().getMaxArraySize() > index)
        return;

    // something to do...

    // TODO: 1.50 linker: unsized block member array: 'node' could be an expression for a dereference
    TIntermSymbol* symbolNode = node->getAsSymbolNode();
    if (! symbolNode)
        return;

    TSymbol* symbol = symbolTable.find(symbolNode->getName());
    assert(symbol);
    if (symbol == 0)
        return;

    if (symbol->getAsFunction()) {
        error(loc, "array variable name expected", symbolNode->getName().c_str(), "");
        return;
    }

    // For read-only built-ins, add a new variable for holding the maximum array size of an implicitly-sized shared array.
    // TODO: desktop linker: unsized arrays: is this new array type shared with the node?
    if (symbol->isReadOnly()) {
        symbol = symbolTable.copyUp(symbol);
        
        if (isIoResizeArray(symbol->getType()))
            ioArraySymbolResizeList.push_back(symbol);

        // Save it in the AST for linker use.
        intermediate.addSymbolLinkageNode(linkage, *symbol);
    }

    symbol->getWritableType().setMaxArraySize(index + 1);
}

//
// Enforce non-initializer type/qualifier rules.
//
void TParseContext::nonInitConstCheck(TSourceLoc loc, TString& identifier, TType& type)
{
    //
    // Make the qualifier make sense, given that there is an initializer.
    //
    if (type.getQualifier().storage == EvqConst ||
        type.getQualifier().storage == EvqConstReadOnly) {
        type.getQualifier().storage = EvqTemporary;
        error(loc, "variables with qualifier 'const' must be initialized", identifier.c_str(), "");
    }
}

//
// See if the identifier is a built-in symbol that can be redeclared, and if so,
// copy the symbol table's read-only built-in variable to the current
// global level, where it can be modified based on the passed in type.
//
// Returns 0 if no redeclaration took place; meaning a normal declaration still
// needs to occur for it, not necessarily an error.
//
// Returns a redeclared and type-modified variable if a redeclarated occurred.
//
TSymbol* TParseContext::redeclareBuiltinVariable(TSourceLoc loc, const TString& identifier, const TQualifier& qualifier, const TShaderQualifiers& publicType, bool& newDeclaration)
{
    if (profile == EEsProfile || ! builtInName(identifier) || symbolTable.atBuiltInLevel() || ! symbolTable.atGlobalLevel())
        return 0;

    // Potentially redeclaring a built-in variable...

    if ((identifier == "gl_FragDepth"           && version >= 420) ||
        (identifier == "gl_FragCoord"           && version >= 150) ||
        (identifier == "gl_ClipDistance"        && version >= 130) ||
        (identifier == "gl_FrontColor"          && version >= 130) ||
        (identifier == "gl_BackColor"           && version >= 130) ||
        (identifier == "gl_FrontSecondaryColor" && version >= 130) ||
        (identifier == "gl_BackSecondaryColor"  && version >= 130) ||
        (identifier == "gl_SecondaryColor"      && version >= 130) ||
        (identifier == "gl_Color"               && version >= 130 && language == EShLangFragment) ||
         identifier == "gl_TexCoord") {

        // Find the existing symbol, if any.
        bool builtIn;
        TSymbol* symbol = symbolTable.find(identifier, &builtIn);

        // If the symbol was not found, this must be a version/profile/stage
        // that doesn't have it.
        if (! symbol)
            return 0;

        // If it wasn't at a built-in level, then it's already been redeclared;
        // that is, this is a redeclaration of a redeclaration; reuse that initial
        // redeclaration.  Otherwise, make the new one.
        if (builtIn) {
            // Copy the symbol up to make a writable version
            newDeclaration = true;
            symbol = symbolTable.copyUp(symbol);

            if (isIoResizeArray(symbol->getType()))
                ioArraySymbolResizeList.push_back(symbol);

            // Save it in the AST for linker use.
            intermediate.addSymbolLinkageNode(linkage, *symbol);
        }

        // Now, modify the type of the copy, as per the type of the current redeclaration.

        TQualifier& symbolQualifier = symbol->getWritableType().getQualifier();
        if (identifier == "gl_FrontColor"          ||
            identifier == "gl_BackColor"           ||
            identifier == "gl_FrontSecondaryColor" ||
            identifier == "gl_BackSecondaryColor"  ||
            identifier == "gl_SecondaryColor"      ||
            identifier == "gl_Color") {
            symbolQualifier.flat = qualifier.flat;
            symbolQualifier.smooth = qualifier.smooth;
            symbolQualifier.nopersp = qualifier.nopersp;
            if (qualifier.hasLayout())
                error(loc, "cannot apply layout qualifier to", "redeclaration", symbol->getName().c_str());
            if (qualifier.isMemory() || qualifier.isAuxiliary() || symbol->getType().getQualifier().storage != qualifier.storage)
                error(loc, "cannot change storage, memory, or auxiliary qualification of", "redeclaration", symbol->getName().c_str());
        } else if (identifier == "gl_TexCoord" ||
                   identifier == "gl_ClipDistance") {
            if (qualifier.hasLayout() || qualifier.isMemory() || qualifier.isAuxiliary() ||
                qualifier.nopersp != symbolQualifier.nopersp || qualifier.flat != symbolQualifier.flat ||
                symbolQualifier.storage != qualifier.storage)
                error(loc, "cannot change qualification of", "redeclaration", symbol->getName().c_str());
        } else if (identifier == "gl_FragCoord") {
            if (intermediate.inIoAccessed("gl_FragCoord"))
                error(loc, "cannot redeclare after use", "gl_FragCoord", "");
            if (qualifier.nopersp != symbolQualifier.nopersp || qualifier.flat != symbolQualifier.flat ||
                qualifier.isMemory() || qualifier.isAuxiliary())
                error(loc, "can only change layout qualification of", "redeclaration", symbol->getName().c_str());
            if (identifier == "gl_FragCoord" && qualifier.storage != EvqVaryingIn)
                error(loc, "cannot change input storage qualification of", "redeclaration", symbol->getName().c_str());
            if (! builtIn && (publicType.pixelCenterInteger != intermediate.getPixelCenterInteger() || 
                              publicType.originUpperLeft != intermediate.getOriginUpperLeft()))
                error(loc, "cannot redeclare with different qualification:", "redeclaration", symbol->getName().c_str());
            if (publicType.pixelCenterInteger)
                intermediate.setPixelCenterInteger();
            if (publicType.originUpperLeft)
                intermediate.setOriginUpperLeft();
        } else if (identifier == "gl_FragDepth") {
            if (qualifier.nopersp != symbolQualifier.nopersp || qualifier.flat != symbolQualifier.flat ||
                qualifier.isMemory() || qualifier.isAuxiliary())
                error(loc, "can only change layout qualification of", "redeclaration", symbol->getName().c_str());
            if (qualifier.storage != EvqVaryingOut)
                error(loc, "cannot change output storage qualification of", "redeclaration", symbol->getName().c_str());
            // TODO 4.2: gl_FragDepth redeclaration
        }        
        // TODO: semantics quality: separate smooth from nothing declared, then use IsInterpolation for several tests above

        return symbol;
    }

    return 0;
}

//
// Either redeclare the requested block, or give an error message why it can't be done.
//
void TParseContext::redeclareBuiltinBlock(TSourceLoc loc, TTypeList& newTypeList, const TString& blockName, const TString* instanceName, TArraySizes* arraySizes)
{
    const char* feature = "built-in block redeclaration";
    requireProfile(loc, ~EEsProfile, feature);
    profileRequires(loc, ~EEsProfile, 410, GL_ARB_separate_shader_objects, feature);

    if (blockName != "gl_PerVertex" && blockName != "gl_PerFragment") {
        error(loc, "cannot redeclare block: ", "block declaration", blockName.c_str());
        return;
    }

    // Redeclaring a built-in block...

    if (instanceName && ! builtInName(*instanceName)) {
        error(loc, "cannot redeclare a built-in block with a user name", instanceName->c_str(), "");
        return;
    }

    // Blocks with instance names are easy to find, lookup the instance name,
    // Anonymous blocks need to be found via a member.
    bool builtIn;
    TSymbol* block;
    if (instanceName)
        block = symbolTable.find(*instanceName, &builtIn);
    else
        block = symbolTable.find(newTypeList.front().type->getFieldName(), &builtIn);

    // If the block was not found, this must be a version/profile/stage
    // that doesn't have it, or the instance name is wrong.
    const char* errorName = instanceName ? instanceName->c_str() : newTypeList.front().type->getFieldName().c_str();
    if (! block) {
        error(loc, "no declaration found for redeclaration", errorName, "");
        return;
    }
    // Built-in blocks cannot be redeclared more than once, which if happened,
    // we'd be finding the already redeclared one here, rather than the built in.
    if (! builtIn) {
        error(loc, "can only redeclare a built-in block once, and before any use", blockName.c_str(), "");
        return;
    }

    // Copy the block to make a writable version, to insert into the block table after editing.
    block = symbolTable.copyUpDeferredInsert(block);

    if (block->getType().getBasicType() != EbtBlock) {
        error(loc, "cannot redeclare a non block as a block", errorName, "");
        return;
    }

    // Edit and error check the container against the redeclaration
    //  - remove unused members
    //  - ensure remaining qualifiers/types match
    TType& type = block->getWritableType();
    TTypeList::iterator member = type.getStruct()->begin();
    size_t numOriginalMembersFound = 0;
    while (member != type.getStruct()->end()) {
        // look for match
        bool found = false;
        TTypeList::iterator newMember;
        TSourceLoc memberLoc;
        for (newMember = newTypeList.begin(); newMember != newTypeList.end(); ++newMember) {
            if (member->type->getFieldName() == newMember->type->getFieldName()) {
                found = true;
                memberLoc = newMember->loc;
                break;
            }
        }

        if (found) {
            ++numOriginalMembersFound;
            // - ensure match between redeclared members' types
            // - check for things that can't be changed
            // - update things that can be changed
            TType& oldType = *member->type;
            const TType& newType = *newMember->type;
            if (! newType.sameElementType(oldType))
                error(memberLoc, "cannot redeclare block member with a different type", member->type->getFieldName().c_str(), "");
            if (oldType.isArray() != newType.isArray())
                error(memberLoc, "cannot change arrayness of redeclared block member", member->type->getFieldName().c_str(), "");
            else if (! oldType.sameArrayness(newType) && oldType.getArraySize() > 0)
                error(memberLoc, "cannot change array size of redeclared block member", member->type->getFieldName().c_str(), "");
            else if (newType.isArray())
                arrayLimitCheck(loc, member->type->getFieldName(), newType.getArraySize());
            if (newType.getQualifier().isMemory())
                error(memberLoc, "cannot add memory qualifier to redeclared block member", member->type->getFieldName().c_str(), "");
            if (newType.getQualifier().hasLayout())
                error(memberLoc, "cannot add layout to redeclared block member", member->type->getFieldName().c_str(), "");
            if (newType.getQualifier().patch)
                error(memberLoc, "cannot add patch to redeclared block member", member->type->getFieldName().c_str(), "");
            oldType.getQualifier().centroid = newType.getQualifier().centroid;
            oldType.getQualifier().sample = newType.getQualifier().sample;
            oldType.getQualifier().invariant = newType.getQualifier().invariant;
            oldType.getQualifier().smooth = newType.getQualifier().smooth;
            oldType.getQualifier().flat = newType.getQualifier().flat;
            oldType.getQualifier().nopersp = newType.getQualifier().nopersp;

            // go to next member
            ++member;
        } else {    
            // Use EbtVoid to tag missing members of anonymous blocks that have been redeclared,
            // to hide the original (shared) declaration.
            // (Instance-named blocks can just have the member removed.)
            if (instanceName)
                member = type.getStruct()->erase(member);
            else {
                member->type->setElementType(EbtVoid, 1, 0, 0, 0);
                ++member;
            }
        }
    }

    if (numOriginalMembersFound < newTypeList.size())
        error(loc, "block redeclaration has extra members", blockName.c_str(), "");
    if (type.isArray() != (arraySizes != 0))
        error(loc, "cannot change arrayness of redeclared block", blockName.c_str(), "");
    else if (type.isArray()) {
        if (type.getArraySize() > 0 && arraySizes->getSize() == 0)
            error(loc, "block already declared with size, can't redeclare as unsized", blockName.c_str(), "");
        else if (type.getArraySize() > 0 && type.getArraySize() != arraySizes->getSize())
            error(loc, "cannot change array size of redeclared block", blockName.c_str(), "");
        else if (type.getArraySize() == 0 && arraySizes->getSize() > 0)
            type.changeArraySize(arraySizes->getSize());
    }

    symbolTable.insert(*block);

    // Check for general layout qualifier errors
    layoutObjectCheck(loc, *block);

    // Tracking for implicit sizing of array
    if (isIoResizeArray(block->getType())) {
        ioArraySymbolResizeList.push_back(block);
        checkIoArraysConsistency(loc, true);
    } else if (block->getType().isArray())
        fixIoArraySize(loc, block->getWritableType());

    // Save it in the AST for linker use.
    intermediate.addSymbolLinkageNode(linkage, *block);
}

void TParseContext::paramCheckFix(TSourceLoc loc, const TStorageQualifier& qualifier, TType& type)
{
    switch (qualifier) {
    case EvqConst:
    case EvqConstReadOnly:
        type.getQualifier().storage = EvqConstReadOnly;
        break;
    case EvqIn:
    case EvqOut:
    case EvqInOut:
        type.getQualifier().storage = qualifier;
        break;
    case EvqTemporary:
        type.getQualifier().storage = EvqIn;
        break;
    default:
        type.getQualifier().storage = EvqIn;
        error(loc, "storage qualifier not allowed on function parameter", GetStorageQualifierString(qualifier), "");
        break;
    }
}

void TParseContext::paramCheckFix(TSourceLoc loc, const TQualifier& qualifier, TType& type)
{
    if (qualifier.isAuxiliary() ||
        qualifier.isInterpolation())
        error(loc, "cannot use auxiliary or interpolation qualifiers on a function parameter", "", "");
    if (qualifier.hasLayout())
        error(loc, "cannot use layout qualifiers on a function parameter", "", "");
    if (qualifier.invariant)
        error(loc, "cannot use invariant qualifier on a function parameter", "", "");    

    paramCheckFix(loc, qualifier.storage, type);
}

void TParseContext::nestedBlockCheck(TSourceLoc loc)
{
    if (structNestingLevel > 0)
        error(loc, "cannot nest a block definition inside a structure or block", "", "");
    ++structNestingLevel;
}

void TParseContext::nestedStructCheck(TSourceLoc loc)
{
    if (structNestingLevel > 0)
        error(loc, "cannot nest a structure definition inside a structure or block", "", "");
    ++structNestingLevel;
}

void TParseContext::arrayObjectCheck(TSourceLoc loc, const TType& type, const char* op)
{
    // Some versions don't allow comparing arrays or structures containing arrays
    if (type.containsArray()) {
        profileRequires(loc, ENoProfile, 120, GL_3DL_array_objects, op);
        profileRequires(loc, EEsProfile, 300, 0, op);
    }
}

void TParseContext::opaqueCheck(TSourceLoc loc, const TType& type, const char* op)
{
    if (containsSampler(type))
        error(loc, "can't use with samplers or structs containing samplers", op, "");
}

void TParseContext::structTypeCheck(TSourceLoc loc, TPublicType& publicType)
{
    TTypeList& typeList = *publicType.userDef->getStruct();

    // fix and check for member storage qualifiers and types that don't belong within a structure
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();        
        TSourceLoc memberLoc = typeList[member].loc;
        if (memberQualifier.isAuxiliary() ||
            memberQualifier.isInterpolation() ||
            (memberQualifier.storage != EvqTemporary && memberQualifier.storage != EvqGlobal))
            error(memberLoc, "cannot use storage or interpolation qualifiers on structure members", typeList[member].type->getFieldName().c_str(), "");
        if (memberQualifier.isMemory())
            error(memberLoc, "cannot use memory qualifiers on structure members", typeList[member].type->getFieldName().c_str(), "");
        if (memberQualifier.hasLayout()) {
            error(memberLoc, "cannot use layout qualifiers on structure members", typeList[member].type->getFieldName().c_str(), "");
            memberQualifier.clearLayout();
        }
        if (memberQualifier.invariant)
            error(memberLoc, "cannot use invariant qualifier on structure members", typeList[member].type->getFieldName().c_str(), "");
    }
}

//
// See if this loop satisfies the limitations for ES 2.0 (version 100) for loops in Appendex A:
//
// "The loop index has type int or float.
//
// "The for statement has the form:
//     for ( init-declaration ; condition ; expression )
//     init-declaration has the form: type-specifier identifier = constant-expression
//     condition has the form:  loop-index relational_operator constant-expression
//         where relational_operator is one of: > >= < <= == or !=
//     expression [sic] has one of the following forms:
//         loop-index++
//         loop-index--
//         loop-index += constant-expression
//         loop-index -= constant-expression
//
// The body is handled in an AST traversal.
//
void TParseContext::inductiveLoopCheck(TSourceLoc loc, TIntermNode* init, TIntermLoop* loop)
{
    // loop index init must exist and be a declaration, which shows up in the AST as an aggregate of size 1 of the declaration
    bool badInit = false;
    if (! init || ! init->getAsAggregate() || ! init->getAsAggregate()->getSequence().size() == 1)
        badInit = true;
    TIntermBinary* binaryInit;
    if (! badInit) {
        // get the declaration assignment
        binaryInit = init->getAsAggregate()->getSequence()[0]->getAsBinaryNode();
        if (! binaryInit)
            badInit = true;
    }
    if (badInit) {
        error(loc, "inductive-loop init-declaration requires the form \"type-specifier loop-index = constant-expression\"", "limitations", "");
        return;
    }

    // loop index must be type int or float
    if (! binaryInit->getType().isScalar() || (binaryInit->getBasicType() != EbtInt && binaryInit->getBasicType() != EbtFloat)) {
        error(loc, "inductive loop requires a scalar 'int' or 'float' loop index", "limitations", "");
        return;
    }

    // init is the form "loop-index = constant"
    if (binaryInit->getOp() != EOpAssign || ! binaryInit->getLeft()->getAsSymbolNode() || ! binaryInit->getRight()->getAsConstantUnion()) {
        error(loc, "inductive-loop init-declaration requires the form \"type-specifier loop-index = constant-expression\"", "limitations", "");
        return;
    }

    // get the unique id of the loop index
    int loopIndex = binaryInit->getLeft()->getAsSymbolNode()->getId();
    inductiveLoopIds.insert(loopIndex);

    // condition's form must be "loop-index relational-operator constant-expression"
    bool badCond = ! loop->getTest();
    if (! badCond) {
        TIntermBinary* binaryCond = loop->getTest()->getAsBinaryNode();
        badCond = ! binaryCond;
        if (! badCond) {
            switch (binaryCond->getOp()) {
            case EOpGreaterThan:
            case EOpGreaterThanEqual:
            case EOpLessThan:
            case EOpLessThanEqual:
            case EOpEqual:
            case EOpNotEqual:
                break;
            default:
                badCond = true;
            }
        }
        if (binaryCond && (! binaryCond->getLeft()->getAsSymbolNode() ||
                           binaryCond->getLeft()->getAsSymbolNode()->getId() != loopIndex ||
                           ! binaryCond->getRight()->getAsConstantUnion()))
            badCond = true;
    }
    if (badCond) {
        error(loc, "inductive-loop condition requires the form \"loop-index <comparison-op> constant-expression\"", "limitations", "");
        return;
    }

    // loop-index++
    // loop-index--
    // loop-index += constant-expression
    // loop-index -= constant-expression
    bool badTerminal = ! loop->getTerminal();
    if (! badTerminal) {
        TIntermUnary* unaryTerminal = loop->getTerminal()->getAsUnaryNode();
        TIntermBinary* binaryTerminal = loop->getTerminal()->getAsBinaryNode();
        if (unaryTerminal || binaryTerminal) {
            switch(loop->getTerminal()->getAsOperator()->getOp()) {
            case EOpPostDecrement:
            case EOpPostIncrement:
            case EOpAddAssign:
            case EOpSubAssign:
                break;
            default:
                badTerminal = true;
            }
        } else
            badTerminal = true;
        if (binaryTerminal && (! binaryTerminal->getLeft()->getAsSymbolNode() ||
                               binaryTerminal->getLeft()->getAsSymbolNode()->getId() != loopIndex ||
                               ! binaryTerminal->getRight()->getAsConstantUnion()))
            badTerminal = true;
        if (unaryTerminal && (! unaryTerminal->getOperand()->getAsSymbolNode() ||
                              unaryTerminal->getOperand()->getAsSymbolNode()->getId() != loopIndex))
            badTerminal = true;
    }
    if (badTerminal) {
        error(loc, "inductive-loop termination requires the form \"loop-index++, loop-index--, loop-index += constant-expression, or loop-index -= constant-expression\"", "limitations", "");
        return;
    }

    // the body
    inductiveLoopBodyCheck(loop->getBody(), loopIndex, symbolTable);
}

// Do limit checks against for all built-in arrays.
void TParseContext::arrayLimitCheck(TSourceLoc loc, const TString& identifier, int size)
{
    if (identifier.compare("gl_TexCoord") == 0)
        limitCheck(loc, size, "gl_MaxTextureCoords", "gl_TexCoord array size");
    else if (identifier.compare("gl_ClipDistance") == 0)
        limitCheck(loc, size, "gl_MaxClipDistances", "gl_ClipDistance array size");
}

// See if the provide value is less than the symbol indicated by limit,
// which should be a constant in the symbol table.
void TParseContext::limitCheck(TSourceLoc loc, int value, const char* limit, const char* feature)
{
    TSymbol* symbol = symbolTable.find(limit);
    assert(symbol->getAsVariable());
    const TConstUnionArray& constArray = symbol->getAsVariable()->getConstArray();
    assert(! constArray.empty());
    if (value >= constArray[0].getIConst())
        error(loc, "must be less than", feature, "%s (%d)", limit, constArray[0].getIConst());
}

//
// Do any additional error checking, etc., once we know the parsing is done.
//
void TParseContext::finalErrorCheck()
{
    // Check on array indexes for ES 2.0 (version 100) limitations.
    for (size_t i = 0; i < needsIndexLimitationChecking.size(); ++i)
        constantIndexExpressionCheck(needsIndexLimitationChecking[i]);
}

//
// Layout qualifier stuff.
//

// Put the id's layout qualification into the public type.  This is before we know any
// type information for error checking.
void TParseContext::setLayoutQualifier(TSourceLoc loc, TPublicType& publicType, TString& id)
{
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    if (id == TQualifier::getLayoutMatrixString(ElmColumnMajor)) {
        publicType.qualifier.layoutMatrix = ElmColumnMajor;
        return;
    }
    if (id == TQualifier::getLayoutMatrixString(ElmRowMajor)) {
        publicType.qualifier.layoutMatrix = ElmRowMajor;
        return;
    }
    if (id == TQualifier::getLayoutPackingString(ElpPacked)) {
        publicType.qualifier.layoutPacking = ElpPacked;
        return;
    }
    if (id == TQualifier::getLayoutPackingString(ElpShared)) {
        publicType.qualifier.layoutPacking = ElpShared;
        return;
    }
    if (id == TQualifier::getLayoutPackingString(ElpStd140)) {
        publicType.qualifier.layoutPacking = ElpStd140;
        return;
    }
    if (id == TQualifier::getLayoutPackingString(ElpStd430)) {
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, "std430");
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 430, 0, "std430");
        publicType.qualifier.layoutPacking = ElpStd430;
        return;
    }
    if (language == EShLangGeometry || language == EShLangTessEvaluation) {
        if (id == TQualifier::getGeometryString(ElgTriangles)) {
            publicType.shaderQualifiers.geometry = ElgTriangles;
            return;
        }
        if (language == EShLangGeometry) {
            if (id == TQualifier::getGeometryString(ElgPoints)) {
                publicType.shaderQualifiers.geometry = ElgPoints;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLineStrip)) {
                publicType.shaderQualifiers.geometry = ElgLineStrip;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLines)) {
                publicType.shaderQualifiers.geometry = ElgLines;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLinesAdjacency)) {
                publicType.shaderQualifiers.geometry = ElgLinesAdjacency;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgTrianglesAdjacency)) {
                publicType.shaderQualifiers.geometry = ElgTrianglesAdjacency;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgTriangleStrip)) {
                publicType.shaderQualifiers.geometry = ElgTriangleStrip;
                return;
            }
        } else {
            assert(language == EShLangTessEvaluation);

            // input primitive
            if (id == TQualifier::getGeometryString(ElgTriangles)) {
                publicType.shaderQualifiers.geometry = ElgTriangles;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgQuads)) {
                publicType.shaderQualifiers.geometry = ElgQuads;
                return;
            }
            if (id == TQualifier::getGeometryString(ElgIsolines)) {
                publicType.shaderQualifiers.geometry = ElgIsolines;
                return;
            }

            // vertex spacing
            if (id == TQualifier::getVertexSpacingString(EvsEqual)) {
                publicType.shaderQualifiers.spacing = EvsEqual;
                return;
            }
            if (id == TQualifier::getVertexSpacingString(EvsFractionalEven)) {
                publicType.shaderQualifiers.spacing = EvsFractionalEven;
                return;
            }
            if (id == TQualifier::getVertexSpacingString(EvsFractionalOdd)) {
                publicType.shaderQualifiers.spacing = EvsFractionalOdd;
                return;
            }

            // triangle order
            if (id == TQualifier::getVertexOrderString(EvoCw)) {
                publicType.shaderQualifiers.order = EvoCw;
                return;
            }
            if (id == TQualifier::getVertexOrderString(EvoCcw)) {
                publicType.shaderQualifiers.order = EvoCcw;
                return;
            }

            // point mode
            if (id == "point_mode") {
                publicType.shaderQualifiers.pointMode = true;
                return;
            }
        }
    }
    if (language == EShLangFragment) {
        if (id == "origin_upper_left") {
            requireProfile(loc, ECoreProfile | ECompatibilityProfile, "origin_upper_left");
            publicType.shaderQualifiers.originUpperLeft = true;
            return;
        }
        if (id == "pixel_center_integer") {
            requireProfile(loc, ECoreProfile | ECompatibilityProfile, "pixel_center_integer");
            publicType.shaderQualifiers.pixelCenterInteger = true;
            return;
        }
    }
    error(loc, "unrecognized layout identifier, or qualifier requires assignemnt (e.g., binding = 4)", id.c_str(), "");
}

// Put the id's layout qualifier value into the public type.  This is before we know any
// type information for error checking.
void TParseContext::setLayoutQualifier(TSourceLoc loc, TPublicType& publicType, TString& id, const TIntermTyped* node)
{
    const char* feature = "layout-id value";
    const char* nonLiteralFeature = "non-literal layout-id value";

    integerCheck(node, feature);
    const TIntermConstantUnion* constUnion = node->getAsConstantUnion();
    int value;
    if (constUnion) {
        value = constUnion->getConstArray()[0].getIConst();
        if (! constUnion->isLiteral()) {
            requireProfile(loc, ECoreProfile | ECompatibilityProfile, nonLiteralFeature);
            profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, nonLiteralFeature);
        }
    } else {
        // grammar should have give out the error message
        value = 0;
    }

    if (value < 0) {
        error(loc, "cannot be negative", feature, "");
        return;
    }

    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    
    if (id == "offset") {
        const char* feature = "uniform buffer-member offset";
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, feature);
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, feature);
        publicType.qualifier.layoutOffset = value;
        return;
    } else if (id == "align") {
        const char* feature = "uniform buffer-member align";
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, feature);
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, feature);
        // "The specified alignment must be a power of 2, or a compile-time error results."
        if (! IsPow2(value))
            error(loc, "must be a power of 2", "align", "");
        else
            publicType.qualifier.layoutAlign = value;
        return;
    } else if (id == "location") {
        profileRequires(loc, EEsProfile, 300, 0, "location");
        profileRequires(loc, ~EEsProfile, 330, GL_ARB_separate_shader_objects, "location");
        if ((unsigned int)value >= TQualifier::layoutLocationEnd)
            error(loc, "location is too large", id.c_str(), "");
        else
            publicType.qualifier.layoutLocation = value;
        return;
    } else if (id == "binding") {
        requireProfile(loc, ~EEsProfile, "binding");
        profileRequires(loc, ~EEsProfile, 420, GL_ARB_shading_language_420pack, "binding");
        if ((unsigned int)value >= TQualifier::layoutBindingEnd)
            error(loc, "binding is too large", id.c_str(), "");
        else
            publicType.qualifier.layoutBinding = value;
        return;
    } else if (id == "component") {
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, "component");
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, "component");
        if ((unsigned)value >= TQualifier::layoutComponentEnd)
            error(loc, "component is too large", id.c_str(), "");
        else
            publicType.qualifier.layoutComponent = value;
        return;
    } else if (id.compare(0, 4, "xfb_") == 0) {
        // "Any shader making any static use (after preprocessing) of any of these 
        // *xfb_* qualifiers will cause the shader to be in a transform feedback 
        // capturing mode and hence responsible for describing the transform feedback 
        // setup."
        intermediate.setXfbMode();
        const char* feature = "transform feedback qualifier";
        requireStage(loc, (EShLanguageMask)(EShLangVertexMask | EShLangGeometryMask | EShLangTessControlMask | EShLangTessEvaluationMask), feature);
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, feature);
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, feature);
        if (id == "xfb_buffer") {
            // "It is a compile-time error to specify an *xfb_buffer* that is greater than
            // the implementation-dependent constant gl_MaxTransformFeedbackBuffers."
            if (value >= resources.maxTransformFeedbackBuffers)
                error(loc, "buffer is too large:", id.c_str(), "gl_MaxTransformFeedbackBuffers is %d", resources.maxTransformFeedbackBuffers);                
            if (value >= TQualifier::layoutXfbBufferEnd)
                error(loc, "buffer is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbBufferEnd-1);
            else
                publicType.qualifier.layoutXfbBuffer = value;
            return;
        } else if (id == "xfb_offset") {
            if (value >= TQualifier::layoutXfbOffsetEnd)
                error(loc, "offset is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbOffsetEnd-1);
            else
                publicType.qualifier.layoutXfbOffset = value;
            return;
        } else if (id == "xfb_stride") {
            // "The resulting stride (implicit or explicit), when divided by 4, must be less than or equal to the 
            // implementation-dependent constant gl_MaxTransformFeedbackInterleavedComponents."
            if (value > 4 * resources.maxTransformFeedbackInterleavedComponents)
                error(loc, "1/4 stride is too large:", id.c_str(), "gl_MaxTransformFeedbackInterleavedComponents is %d", resources.maxTransformFeedbackInterleavedComponents);
            else if (value >= TQualifier::layoutXfbStrideEnd)
                error(loc, "stride is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbStrideEnd-1);
            if (value < TQualifier::layoutXfbStrideEnd)
                publicType.qualifier.layoutXfbStride = value;
            return;
        }
    }

    switch (language) {
    case EShLangVertex:
        break;

    case EShLangTessControl:
        if (id == "vertices") {
            publicType.shaderQualifiers.vertices = value;
            return;
        }
        break;

    case EShLangTessEvaluation:
        break;

    case EShLangGeometry:
        if (id == "invocations") {
            profileRequires(loc, ECompatibilityProfile | ECoreProfile, 400, 0, "invocations");
            publicType.shaderQualifiers.invocations = value;
            return;
        }
        if (id == "max_vertices") {
            publicType.shaderQualifiers.vertices = value;
            if (value > resources.maxGeometryOutputVertices)
                error(loc, "too large, must be less than gl_MaxGeometryOutputVertices", "max_vertices", "");
            return;
        }
        if (id == "stream") {
            publicType.qualifier.layoutStream = value;
            return;
        }
        break;

    case EShLangFragment:
        break;

    case EShLangCompute:
        break;

    default:
        break;
    }

    error(loc, "there is no such layout identifier for this stage taking an assigned value", id.c_str(), "");
}

// Merge any layout qualifier information from src into dst, leaving everything else in dst alone
//
// "More than one layout qualifier may appear in a single declaration.
// Additionally, the same layout-qualifier-name can occur multiple times 
// within a layout qualifier or across multiple layout qualifiers in the 
// same declaration. When the same layout-qualifier-name occurs 
// multiple times, in a single declaration, the last occurrence overrides 
// the former occurrence(s).  Further, if such a layout-qualifier-name 
// will effect subsequent declarations or other observable behavior, it 
// is only the last occurrence that will have any effect, behaving as if 
// the earlier occurrence(s) within the declaration are not present.  
// This is also true for overriding layout-qualifier-names, where one 
// overrides the other (e.g., row_major vs. column_major); only the last 
// occurrence has any effect."    
//
void TParseContext::mergeObjectLayoutQualifiers(TSourceLoc loc, TQualifier& dst, const TQualifier& src, bool inheritOnly)
{
    if (src.hasMatrix())
        dst.layoutMatrix = src.layoutMatrix;
    if (src.hasPacking())
        dst.layoutPacking = src.layoutPacking;

    if (src.hasStream())
        dst.layoutStream = src.layoutStream;

    if (src.hasXfbBuffer())
        dst.layoutXfbBuffer = src.layoutXfbBuffer;

    if (src.hasAlign())
        dst.layoutAlign = src.layoutAlign;

    if (! inheritOnly) {
        if (src.layoutLocation != TQualifier::layoutLocationEnd)
            dst.layoutLocation = src.layoutLocation;
        if (src.layoutComponent != TQualifier::layoutComponentEnd)
            dst.layoutComponent = src.layoutComponent;
        
        if (src.hasOffset())
            dst.layoutOffset = src.layoutOffset;

        if (src.layoutBinding != TQualifier::layoutBindingEnd)
            dst.layoutBinding = src.layoutBinding;

        if (src.hasXfbStride())
            dst.layoutXfbStride = src.layoutXfbStride;
        if (src.hasXfbOffset())
            dst.layoutXfbOffset = src.layoutXfbOffset;
    }
}

// Do error layout error checking given a full variable/block declaration.
void TParseContext::layoutObjectCheck(TSourceLoc loc, const TSymbol& symbol)
{
    const TType& type = symbol.getType();
    const TQualifier& qualifier = type.getQualifier();

    // first, cross check WRT to just the type
    layoutTypeCheck(loc, type);

    // now, any remaining error checking based on the object itself

    if (qualifier.hasLocation()) {
        switch (qualifier.storage) {
        case EvqUniform:
        case EvqBuffer:
            if (symbol.getAsVariable() == 0)
                error(loc, "can only be used on variable declaration", "location", "");
            break;
        default:
            break;
        }
    }

    // Check packing and matrix 
    if (qualifier.hasUniformLayout()) {
        switch (qualifier.storage) {
        case EvqBuffer:
        case EvqUniform:
            if (type.getBasicType() != EbtBlock) {
                if (qualifier.hasMatrix())
                    error(loc, "cannot specify matrix layout on a variable declaration", "layout", "");
                if (qualifier.hasPacking())
                    error(loc, "cannot specify packing on a variable declaration", "layout", "");
                // "The offset qualifier can only be used on block members of blocks..."
                if (qualifier.hasOffset())
                    error(loc, "cannot specify on a variable declaration", "offset", "");
                // "The align qualifier can only be used on blocks or block members..."
                if (qualifier.hasAlign())
                    error(loc, "cannot specify on a variable declaration", "align", "");
            }
            break;
        default:
            // these were already filtered by layoutTypeCheck() (or its callees)
            break;
        }
    }
}

// Do error layout error checking with respect to a type.
void TParseContext::layoutTypeCheck(TSourceLoc loc, const TType& type)
{
    const TQualifier& qualifier = type.getQualifier();

    // first, intra layout qualifier-only error checking
    layoutQualifierCheck(loc, qualifier);

    // now, error checking combining type and qualifier

    if (qualifier.hasLocation()) {
        if (qualifier.layoutComponent != TQualifier::layoutComponentEnd) {
            // "It is a compile-time error if this sequence of components gets larger than 3."
            if (qualifier.layoutComponent + type.getVectorSize() > 4)
                error(loc, "type overflows the available 4 components", "component", "");

            // "It is a compile-time error to apply the component qualifier to a matrix, a structure, a block, or an array containing any of these."
            if (type.isMatrix() || type.getBasicType() == EbtBlock || type.getBasicType() == EbtStruct)
                error(loc, "cannot apply to a matrix, structure, or block", "component", "");
        }

        switch (qualifier.storage) {
        case EvqVaryingIn:
        case EvqVaryingOut:
            if (type.getBasicType() == EbtBlock)
                profileRequires(loc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, "location qualifier on in/out block");
            break;
        case EvqUniform:
        case EvqBuffer:
            break;
        default:
            error(loc, "can only appy to uniform, buffer, in, or out storage qualifiers", "location", "");
            break;
        }

        bool typeCollision;
        int repeated = intermediate.addUsedLocation(qualifier, type, typeCollision);
        if (repeated >= 0 && ! typeCollision)
            error(loc, "overlapping use of location", "location", "%d", repeated);
        // "fragment-shader outputs ... if two variables are placed within the same
        // location, they must have the same underlying type (floating-point or integer)"
        if (typeCollision && language == EShLangFragment && qualifier.isPipeOutput())
            error(loc, "fragment outputs sharing the same location must be the same basic type", "location", "%d", repeated);
    }

    if (qualifier.hasXfbOffset() && qualifier.hasXfbBuffer()) {
        int repeated = intermediate.addXfbBufferOffset(type);
        if (repeated >= 0)
            error(loc, "overlapping offsets at", "xfb_offset", "offset %d in buffer %d", repeated, qualifier.layoutXfbBuffer);

        // "The offset must be a multiple of the size of the first component of the first 
        // qualified variable or block member, or a compile-time error results. Further, if applied to an aggregate 
        // containing a double, the offset must also be a multiple of 8..."
        if (type.containsBasicType(EbtDouble) && ! IsMultipleOfPow2(qualifier.layoutXfbOffset, 8))
            error(loc, "type contains double; xfb_offset must be a multiple of 8", "xfb_offset", "");
        else if (! IsMultipleOfPow2(qualifier.layoutXfbOffset, 4))
            error(loc, "must be a multiple of size of first component", "xfb_offset", "");
    }

    if (qualifier.hasXfbStride() && qualifier.hasXfbBuffer()) {
        if (! intermediate.setXfbBufferStride(qualifier.layoutXfbBuffer, qualifier.layoutXfbStride))
            error(loc, "all stride settings must match for xfb buffer", "xfb_stride", "%d", qualifier.layoutXfbBuffer);
    }

    if (qualifier.hasBinding()) {
        // Binding checking, from the spec:
        //
        // "If the binding point for any uniform or shader storage block instance is less than zero, or greater than or
        // equal to the implementation-dependent maximum number of uniform buffer bindings, a compile-time
        // error will occur. When the binding identifier is used with a uniform or shader storage block instanced as
        // an array of size N, all elements of the array from binding through binding + N – 1 must be within this
        // range."
        //
        if (type.getBasicType() != EbtSampler && type.getBasicType() != EbtBlock)
            error(loc, "requires block, or sampler/image, or atomic-counter type", "binding", "");
            // TODO: 4.2 functionality: atomic counter: include in test above
        if (type.getBasicType() == EbtSampler) {
            int lastBinding = qualifier.layoutBinding;
            if (type.isArray())
                lastBinding += type.getArraySize();
            if (lastBinding >= resources.maxCombinedTextureImageUnits)
                error(loc, "sampler binding not less than gl_MaxCombinedTextureImageUnits", "binding", type.isArray() ? "(using array)" : "");
        }
    }

    // "The offset qualifier can only be used on block members of blocks..."                
    if (qualifier.hasOffset()) {
        if (type.getBasicType() == EbtBlock)
            error(loc, "only applies to block members, not blocks", "offset", "");        
    }
}

// Do layout error checking that can be done within a qualifier proper, not needing to know
// if there are blocks, atomic counters, variables, etc.
void TParseContext::layoutQualifierCheck(TSourceLoc loc, const TQualifier& qualifier)
{
    // "It is a compile-time error to use *component* without also specifying the location qualifier (order does not matter)."
    if (qualifier.layoutComponent != TQualifier::layoutComponentEnd && qualifier.layoutLocation == TQualifier::layoutLocationEnd)
        error(loc, "must specify 'location' to use 'component'", "component", "");

    if (qualifier.hasLocation()) {

        // "As with input layout qualifiers, all shaders except compute shaders 
        // allow *location* layout qualifiers on output variable declarations, 
        // output block declarations, and output block member declarations."

        switch (qualifier.storage) {
        case EvqVaryingIn:
        {
            const char* feature = "location qualifier on input";
            if (profile == EEsProfile)
                requireStage(loc, EShLangVertex, feature);
            requireStage(loc, (EShLanguageMask)~EShLangComputeMask, feature);
            if (language == EShLangVertex)
                profileRequires(loc, ~EEsProfile, 330, GL_ARB_separate_shader_objects, feature);
            else
                profileRequires(loc, ~EEsProfile, 410, GL_ARB_separate_shader_objects, feature);
            break;
        }
        case EvqVaryingOut:
        {
            const char* feature = "location qualifier on output";
            if (profile == EEsProfile)
                requireStage(loc, EShLangFragment, feature);
            requireStage(loc, (EShLanguageMask)~EShLangComputeMask, feature);
            if (language == EShLangFragment)
                profileRequires(loc, ~EEsProfile, 330, GL_ARB_separate_shader_objects, feature);
            else
                profileRequires(loc, ~EEsProfile, 410, GL_ARB_separate_shader_objects, feature);
            break;
        }
        case EvqUniform:
        case EvqBuffer:
        {
            const char* feature = "location qualifier on uniform or buffer";
            requireProfile(loc, ECoreProfile | ECompatibilityProfile, feature);
            profileRequires(loc, ECoreProfile | ECompatibilityProfile, 430, 0, feature);
            break;
        }
        default:
            break;
        }
    }

    if (qualifier.hasBinding()) {
        if (qualifier.storage != EvqUniform && qualifier.storage != EvqBuffer)
            error(loc, "requires uniform or buffer storage qualifier", "binding", "");
    }
    if (qualifier.hasStream()) {
        if (qualifier.storage != EvqVaryingOut)
            error(loc, "can only be used on an output", "stream", "");
    }
    if (qualifier.hasXfb()) {
        if (qualifier.storage != EvqVaryingOut)
            error(loc, "can only be used on an output", "xfb layout qualifier", "");
    }
    if (qualifier.hasUniformLayout()) {
        if (! (qualifier.storage == EvqUniform || qualifier.storage == EvqBuffer)) {
            if (qualifier.hasMatrix() || qualifier.hasPacking())
                error(loc, "matrix or packing qualifiers can only be used on a uniform or buffer", "layout", "");
            if (qualifier.hasOffset() || qualifier.hasAlign())
                error(loc, "offset/align can only be used on a uniform or buffer", "layout", "");
        }
    }
}

// For places that can't have shader-level layout qualifiers
void TParseContext::checkNoShaderLayouts(TSourceLoc loc, const TShaderQualifiers& shaderQualifiers)
{
    const char* message = "can only apply to a standalone qualifier";

    if (shaderQualifiers.geometry != ElgNone)
        error(loc, message, TQualifier::getGeometryString(shaderQualifiers.geometry), "");
    if (shaderQualifiers.invocations > 0)
        error(loc, message, "invocations", "");
    if (shaderQualifiers.vertices > 0) {
        if (language == EShLangGeometry)
            error(loc, message, "max_vertices", "");
        else if (language == EShLangTessControl)
            error(loc, message, "vertices", "");
        else
            assert(0);
    }
}

//
// Look up a function name in the symbol table, and make sure it is a function.
//
// Return the function symbol if found, otherwise 0.
//
const TFunction* TParseContext::findFunction(TSourceLoc loc, const TFunction& call, bool& builtIn)
{
    const TFunction* function = 0;

    if (symbolTable.isFunctionNameVariable(call.getName())) {
        error(loc, "can't use function syntax on variable", call.getName().c_str(), "");
        return 0;
    }

    if (profile == EEsProfile || version < 120)
        function = findFunctionExact(loc, call, builtIn);
    else if (version < 400)
        function = findFunction120(loc, call, builtIn);
    else
        function = findFunction400(loc, call, builtIn);

    return function;
}

// Function finding algorithm for ES and desktop 110.
const TFunction* TParseContext::findFunctionExact(TSourceLoc loc, const TFunction& call, bool& builtIn)
{
    const TFunction* function = 0;

    TSymbol* symbol = symbolTable.find(call.getMangledName(), &builtIn);
    if (symbol == 0) {
        error(loc, "no matching overloaded function found", call.getName().c_str(), "");

        return 0;
    }

    return symbol->getAsFunction();
}

// Function finding algorithm for desktop versions 120 through 330.
const TFunction* TParseContext::findFunction120(TSourceLoc loc, const TFunction& call, bool& builtIn)
{
    // first, look for an exact match
    TSymbol* symbol = symbolTable.find(call.getMangledName(), &builtIn);
    if (symbol)
        return symbol->getAsFunction();

    // exact match not found, look through a list of overloaded functions of the same name

    // "If no exact match is found, then [implicit conversions] will be applied to find a match. Mismatched types
    // on input parameters (in or inout or default) must have a conversion from the calling argument type to the
    // formal parameter type. Mismatched types on output parameters (out or inout) must have a conversion
    // from the formal parameter type to the calling argument type.  When argument conversions are used to find
    // a match, it is a semantic error if there are multiple ways to apply these conversions to make the call match
    // more than one function."

    const TFunction* candidate = 0;
    TVector<TFunction*> candidateList;
    symbolTable.findFunctionNameList(call.getMangledName(), candidateList, builtIn);

    int numPossibleMatches = 0;
    for (TVector<TFunction*>::const_iterator it = candidateList.begin(); it != candidateList.end(); ++it) {
        const TFunction& function = *(*it);

        // to even be a potential match, number of arguments has to match
        if (call.getParamCount() != function.getParamCount())
            continue;

        bool possibleMatch = true;
        for (int i = 0; i < function.getParamCount(); ++i) {
            // same types is easy
            if (*function[i].type == *call[i].type)
                continue;

            // We have a mismatch in type, see if it is implicitly convertible

            if (function[i].type->isArray() || call[i].type->isArray() ||
                ! function[i].type->sameElementShape(*call[i].type))
                possibleMatch = false;
            else {
                // do direction-specific checks for conversion of basic type
                TStorageQualifier qualifier = function[i].type->getQualifier().storage;
                if (qualifier == EvqIn || qualifier == EvqInOut) {
                    if (! intermediate.canImplicitlyPromote(call[i].type->getBasicType(), function[i].type->getBasicType()))
                        possibleMatch = false;
                }
                if (qualifier == EvqOut || qualifier == EvqInOut) {
                    if (! intermediate.canImplicitlyPromote(function[i].type->getBasicType(), call[i].type->getBasicType()))
                        possibleMatch = false;
                }
            }
            if (! possibleMatch)
                break;
        }
        if (possibleMatch) {
            if (candidate) {
                // our second match, meaning ambiguity
                error(loc, "ambiguous function signature match: multiple signatures match under implicit type conversion", call.getName().c_str(), "");
            } else
                candidate = &function;
        }
    }

    if (candidate == 0)
        error(loc, "no matching overloaded function found", call.getName().c_str(), "");

    return candidate;
}

// Function finding algorithm for desktop version 400 and above.
const TFunction* TParseContext::findFunction400(TSourceLoc loc, const TFunction& call, bool& builtIn)
{
    // TODO: 4.00 functionality: findFunction400()
    return findFunction120(loc, call, builtIn);
}

//
// Do everything necessary to handle a variable (non-block) declaration.
// Either redeclaring a variable, or making a new one, updating the symbol
// table, and all error checking.
//
// Returns a subtree node that computes an initializer, if needed.
// Returns 0 if there is no code to execute for initialization.
//
TIntermNode* TParseContext::declareVariable(TSourceLoc loc, TString& identifier, const TPublicType& publicType, TArraySizes* arraySizes, TIntermTyped* initializer)
{
    TType type(publicType);

    if (voidErrorCheck(loc, identifier, type.getBasicType()))
        return 0;

    if (! initializer)
        nonInitConstCheck(loc, identifier, type);

    invariantCheck(loc, type, identifier);
    samplerCheck(loc, type, identifier);

    if (identifier != "gl_FragCoord" && (publicType.shaderQualifiers.originUpperLeft || publicType.shaderQualifiers.pixelCenterInteger))
        error(loc, "can only apply origin_upper_left and pixel_center_origin to gl_FragCoord", "layout qualifier", "");

    // Check for redeclaration of built-ins and/or attempting to declare a reserved name
    bool newDeclaration = false;    // true if a new entry gets added to the symbol table
    TSymbol* symbol = redeclareBuiltinVariable(loc, identifier, type.getQualifier(), publicType.shaderQualifiers, newDeclaration);
    if (! symbol)
        reservedErrorCheck(loc, identifier);

    inheritGlobalDefaults(type.getQualifier());

    // Declare the variable
    if (arraySizes || type.isArray()) {
        // Arrayness is potentially coming both from the type and from the 
        // variable: "int[] a[];" or just one or the other.
        // For now, arrays of arrays aren't supported, so it's just one or the
        // other.  Move it to the type, so all arrayness is part of the type.
        arrayDimCheck(loc, &type, arraySizes);
        if (arraySizes)
            type.setArraySizes(arraySizes);

        // for ES, if size isn't coming from an initializer, it has to be explicitly declared now
        if (profile == EEsProfile && ! initializer)
            arraySizeRequiredCheck(loc, type.getArraySize());

        if (! arrayQualifierError(loc, type.getQualifier()))
            declareArray(loc, identifier, type, symbol, newDeclaration);

        if (initializer) {
            profileRequires(loc, ENoProfile, 120, GL_3DL_array_objects, "initializer");
            profileRequires(loc, EEsProfile, 300, 0, "initializer");
        }
    } else {
        // non-array case
        if (! symbol)
            symbol = declareNonArray(loc, identifier, type, newDeclaration);
        else if (type != symbol->getType())
            error(loc, "cannot change the type of", "redeclaration", symbol->getName().c_str());
    }

    if (! symbol)
        return 0;

    // Deal with initializer
    TIntermNode* initNode = 0;
    if (symbol && initializer) {
        TVariable* variable = symbol->getAsVariable();
        if (! variable) {
            error(loc, "initializer requires a variable, not a member", identifier.c_str(), "");
            return 0;
        }
        initNode = executeInitializer(loc, identifier, initializer, variable);
    }

    // look for errors/adjustments in layout qualifier use
    layoutObjectCheck(loc, *symbol);

    // see if it's a linker-level object to track
    if (newDeclaration && symbolTable.atGlobalLevel())
        intermediate.addSymbolLinkageNode(linkage, *symbol);

    return initNode;
}

// Pick up global defaults from the provide global defaults into dst.
void TParseContext::inheritGlobalDefaults(TQualifier& dst) const
{
    if (dst.storage == EvqVaryingOut) {
        if (! dst.hasStream() && language == EShLangGeometry)
            dst.layoutStream = globalOutputDefaults.layoutStream;
        if (! dst.hasXfbBuffer())
            dst.layoutXfbBuffer = globalOutputDefaults.layoutXfbBuffer;
    }
}

//
// Declare a non-array variable, the main point being there is no redeclaration
// for resizing allowed.
//
// Return the successfully declared variable.
//
TVariable* TParseContext::declareNonArray(TSourceLoc loc, TString& identifier, TType& type, bool& newDeclaration)
{
    // make a new variable
    TVariable* variable = new TVariable(&identifier, type);

    ioArrayCheck(loc, type, identifier);
    // add variable to symbol table
    if (! symbolTable.insert(*variable)) {
        error(loc, "redefinition", variable->getName().c_str(), "");
        return 0;
    } else {
        newDeclaration = true;
        return variable;
    }
}

//
// Handle all types of initializers from the grammar.
//
// Returning 0 just means there is no code to execute to handle the
// initializer, which will, for example, be the case for constant initalizers.
//
TIntermNode* TParseContext::executeInitializer(TSourceLoc loc, TString& identifier,
                                               TIntermTyped* initializer, TVariable* variable)
{
    //
    // Identifier must be of type constant, a global, or a temporary, and
    // starting at version 120, desktop allows uniforms to have initializers.
    //
    TStorageQualifier qualifier = variable->getType().getQualifier().storage;
    if (! (qualifier == EvqTemporary || qualifier == EvqGlobal || qualifier == EvqConst ||
           (qualifier == EvqUniform && profile != EEsProfile && version >= 120))) {
        error(loc, " cannot initialize this type of qualifier ", variable->getType().getStorageQualifierString(), "");
        return 0;
    }
    arrayObjectCheck(loc, variable->getType(), "array initializer");

    //
    // If the initializer was from braces { ... }, we convert the whole subtree to a
    // constructor-style subtree, allowing the rest of the code to operate
    // identically for both kinds of initializers.
    //
    initializer = convertInitializerList(loc, variable->getType(), initializer);
    if (! initializer) {
        // error recovery; don't leave const without constant values
        if (qualifier == EvqConst)
            variable->getWritableType().getQualifier().storage = EvqTemporary;
        return 0;
    }

    // Fix arrayness if variable is unsized, getting size from the initializer
    if (initializer->getType().isArray() && initializer->getType().getArraySize() > 0 &&
        variable->getType().isArray() && variable->getType().getArraySize() == 0)
        variable->getWritableType().changeArraySize(initializer->getType().getArraySize());

    // Uniform and global consts require a constant initializer
    if (qualifier == EvqUniform && initializer->getType().getQualifier().storage != EvqConst) {
        error(loc, "uniform initializers must be constant", "=", "'%s'", variable->getType().getCompleteString().c_str());
        variable->getWritableType().getQualifier().storage = EvqTemporary;
        return 0;
    }
    if (qualifier == EvqConst && symbolTable.atGlobalLevel() && initializer->getType().getQualifier().storage != EvqConst) {
        error(loc, "global const initializers must be constant", "=", "'%s'", variable->getType().getCompleteString().c_str());
        variable->getWritableType().getQualifier().storage = EvqTemporary;
        return 0;
    }

    // Const variables require a constant initializer, depending on version
    if (qualifier == EvqConst) {
        if (initializer->getType().getQualifier().storage != EvqConst) {
            const char* initFeature = "non-constant initializer";
            requireProfile(loc, ~EEsProfile, initFeature);
            profileRequires(loc, ~EEsProfile, 420, GL_ARB_shading_language_420pack, initFeature);
            variable->getWritableType().getQualifier().storage = EvqConstReadOnly;
            qualifier = EvqConstReadOnly;
        }
    }

    if (qualifier == EvqConst || qualifier == EvqUniform) {
        // Compile-time tagging of the variable with it's constant value...

        initializer = intermediate.addConversion(EOpAssign, variable->getType(), initializer);
        if (! initializer || ! initializer->getAsConstantUnion() || variable->getType() != initializer->getType()) {
            error(loc, "non-matching or non-convertible constant type for const initializer",
                  variable->getType().getStorageQualifierString(), "");
            variable->getWritableType().getQualifier().storage = EvqTemporary;
            return 0;
        }

        variable->setConstArray(initializer->getAsConstantUnion()->getConstArray());
    } else {
        // normal assigning of a value to a variable...
        TIntermSymbol* intermSymbol = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), loc);
        TIntermNode* initNode = intermediate.addAssign(EOpAssign, intermSymbol, initializer, loc);
        if (! initNode)
            assignError(loc, "=", intermSymbol->getCompleteString(), initializer->getCompleteString());

        return initNode;
    }

    return 0;
}

//
// Reprocess any initalizer-list { ... } parts of the initializer.
// Need to heirarchically assign correct types and implicit
// conversions. Will do this mimicking the same process used for
// creating a constructor-style initializer, ensuring we get the
// same form.
//
TIntermTyped* TParseContext::convertInitializerList(TSourceLoc loc, const TType& type, TIntermTyped* initializer)
{
    // Will operate recursively.  Once a subtree is found that is constructor style,
    // everything below it is already good: Only the "top part" of the initializer
    // can be an initializer list, where "top part" can extend for several (or all) levels.

    // see if we have bottomed out in the tree within the initializer-list part
    TIntermAggregate* initList = initializer->getAsAggregate();
    if (! initList || initList->getOp() != EOpNull)
        return initializer;

    // Of the initializer-list set of nodes, need to process bottom up,
    // so recurse deep, then process on the way up.

    // Go down the tree here...
    if (type.isArray()) {
        // The type's array might be unsized, which could be okay, so base sizes on the size of the aggregate.
        // Later on, initializer execution code will deal with array size logic.
        TType arrayType;
        arrayType.shallowCopy(type);
        arrayType.setArraySizes(type);
        arrayType.changeArraySize((int)initList->getSequence().size());
        TType elementType(arrayType, 0); // dereferenced type
        for (size_t i = 0; i < initList->getSequence().size(); ++i) {
            initList->getSequence()[i] = convertInitializerList(loc, elementType, initList->getSequence()[i]->getAsTyped());
            if (initList->getSequence()[i] == 0)
                return 0;
        }

        return addConstructor(loc, initList, arrayType, mapTypeToConstructorOp(arrayType));
    } else if (type.isStruct()) {
        if (type.getStruct()->size() != initList->getSequence().size()) {
            error(loc, "wrong number of structure members", "initializer list", "");
            return 0;
        }
        for (size_t i = 0; i < type.getStruct()->size(); ++i) {
            initList->getSequence()[i] = convertInitializerList(loc, *(*type.getStruct())[i].type, initList->getSequence()[i]->getAsTyped());
            if (initList->getSequence()[i] == 0)
                return 0;
        }
    } else if (type.isMatrix()) {
        if (type.getMatrixCols() != initList->getSequence().size()) {
            error(loc, "wrong number of matrix columns:", "initializer list", type.getCompleteString().c_str());
            return 0;
        }
        TType vectorType(type, 0); // dereferenced type
        for (int i = 0; i < type.getMatrixCols(); ++i) {
            initList->getSequence()[i] = convertInitializerList(loc, vectorType, initList->getSequence()[i]->getAsTyped());
            if (initList->getSequence()[i] == 0)
                return 0;
        }
    } else if (type.isVector()) {
        if (type.getVectorSize() != initList->getSequence().size()) {
            error(loc, "wrong vector size (or rows in a matrix column):", "initializer list", type.getCompleteString().c_str());
            return 0;
        }
    } else {
        error(loc, "unexpected initializer-list type:", "initializer list", type.getCompleteString().c_str());
        return 0;
    }

    // now that the subtree is processed, process this node
    return addConstructor(loc, initList, type, mapTypeToConstructorOp(type));
}

//
// Test for the correctness of the parameters passed to various constructor functions
// and also convert them to the right data type, if allowed and required.
//
// Returns 0 for an error or the constructed node (aggregate or typed) for no error.
//
TIntermTyped* TParseContext::addConstructor(TSourceLoc loc, TIntermNode* node, const TType& type, TOperator op)
{
    if (node == 0)
        return 0;

    TIntermAggregate* aggrNode = node->getAsAggregate();

    TTypeList::iterator memberTypes;
    if (op == EOpConstructStruct)
        memberTypes = type.getStruct()->begin();

    TType elementType;
    elementType.shallowCopy(type);
    if (type.isArray())
        elementType.dereference();

    bool singleArg;
    if (aggrNode) {
        if (aggrNode->getOp() != EOpNull || aggrNode->getSequence().size() == 1)
            singleArg = true;
        else
            singleArg = false;
    } else
        singleArg = true;

    TIntermTyped *newNode;
    if (singleArg) {
        // If structure constructor or array constructor is being called
        // for only one parameter inside the structure, we need to call constructStruct function once.
        if (type.isArray())
            newNode = constructStruct(node, elementType, 1, node->getLoc());
        else if (op == EOpConstructStruct)
            newNode = constructStruct(node, *(*memberTypes).type, 1, node->getLoc());
        else
            newNode = constructBuiltIn(type, op, node, node->getLoc(), false);

        if (newNode && (type.isArray() || op == EOpConstructStruct))
            newNode = intermediate.setAggregateOperator(newNode, EOpConstructStruct, type, loc);

        return newNode;
    }

    //
    // Handle list of arguments.
    //
    TIntermSequence &sequenceVector = aggrNode->getSequence();    // Stores the information about the parameter to the constructor
    // if the structure constructor contains more than one parameter, then construct
    // each parameter

    int paramCount = 0;  // keeps a track of the constructor parameter number being checked

    // for each parameter to the constructor call, check to see if the right type is passed or convert them
    // to the right type if possible (and allowed).
    // for structure constructors, just check if the right type is passed, no conversion is allowed.

    for (TIntermSequence::iterator p = sequenceVector.begin();
                                   p != sequenceVector.end(); p++, paramCount++) {
        if (type.isArray())
            newNode = constructStruct(*p, elementType, paramCount+1, node->getLoc());
        else if (op == EOpConstructStruct)
            newNode = constructStruct(*p, *(memberTypes[paramCount]).type, paramCount+1, node->getLoc());
        else
            newNode = constructBuiltIn(type, op, *p, node->getLoc(), true);

        if (newNode)
            *p = newNode;
        else
            return 0;
    }

    TIntermTyped* constructor = intermediate.setAggregateOperator(aggrNode, op, type, loc);

    return constructor;
}

// Function for constructor implementation. Calls addUnaryMath with appropriate EOp value
// for the parameter to the constructor (passed to this function). Essentially, it converts
// the parameter types correctly. If a constructor expects an int (like ivec2) and is passed a
// float, then float is converted to int.
//
// Returns 0 for an error or the constructed node.
//
TIntermTyped* TParseContext::constructBuiltIn(const TType& type, TOperator op, TIntermNode* node, TSourceLoc loc, bool subset)
{
    TIntermTyped* newNode;
    TOperator basicOp;

    //
    // First, convert types as needed.
    //
    switch (op) {
    case EOpConstructVec2:
    case EOpConstructVec3:
    case EOpConstructVec4:
    case EOpConstructMat2x2:
    case EOpConstructMat2x3:
    case EOpConstructMat2x4:
    case EOpConstructMat3x2:
    case EOpConstructMat3x3:
    case EOpConstructMat3x4:
    case EOpConstructMat4x2:
    case EOpConstructMat4x3:
    case EOpConstructMat4x4:
    case EOpConstructFloat:
        basicOp = EOpConstructFloat;
        break;

    case EOpConstructDVec2:
    case EOpConstructDVec3:
    case EOpConstructDVec4:
    case EOpConstructDMat2x2:
    case EOpConstructDMat2x3:
    case EOpConstructDMat2x4:
    case EOpConstructDMat3x2:
    case EOpConstructDMat3x3:
    case EOpConstructDMat3x4:
    case EOpConstructDMat4x2:
    case EOpConstructDMat4x3:
    case EOpConstructDMat4x4:
    case EOpConstructDouble:
        basicOp = EOpConstructDouble;
        break;

    case EOpConstructIVec2:
    case EOpConstructIVec3:
    case EOpConstructIVec4:
    case EOpConstructInt:
        basicOp = EOpConstructInt;
        break;

    case EOpConstructUVec2:
    case EOpConstructUVec3:
    case EOpConstructUVec4:
    case EOpConstructUint:
        basicOp = EOpConstructUint;
        break;

    case EOpConstructBVec2:
    case EOpConstructBVec3:
    case EOpConstructBVec4:
    case EOpConstructBool:
        basicOp = EOpConstructBool;
        break;

    default:
        error(loc, "unsupported construction", "", "");

        return 0;
    }
    newNode = intermediate.addUnaryMath(basicOp, node, node->getLoc());
    if (newNode == 0) {
        error(loc, "can't convert", "constructor", "");
        return 0;
    }

    //
    // Now, if there still isn't an operation to do the construction, and we need one, add one.
    //

    // Otherwise, skip out early.
    if (subset || (newNode != node && newNode->getType() == type))
        return newNode;

    // setAggregateOperator will insert a new node for the constructor, as needed.
    return intermediate.setAggregateOperator(newNode, op, type, loc);
}

// This function tests for the type of the parameters to the structures constructors. Raises
// an error message if the expected type does not match the parameter passed to the constructor.
//
// Returns 0 for an error or the input node itself if the expected and the given parameter types match.
//
TIntermTyped* TParseContext::constructStruct(TIntermNode* node, const TType& type, int paramCount, TSourceLoc loc)
{
    TIntermTyped* converted = intermediate.addConversion(EOpConstructStruct, type, node->getAsTyped());
    if (! converted || converted->getType() != type) {
        error(loc, "", "constructor", "cannot convert parameter %d from '%s' to '%s'", paramCount,
              node->getAsTyped()->getType().getCompleteString().c_str(), type.getCompleteString().c_str());

        return 0;
    }

    return converted;
}

//
// Do everything needed to add an interface block.
//
void TParseContext::declareBlock(TSourceLoc loc, TTypeList& typeList, const TString* instanceName, TArraySizes* arraySizes)
{
    if (profile == EEsProfile && arraySizes)
        arraySizeRequiredCheck(loc, arraySizes->getSize());

    switch (currentBlockQualifier.storage) {
    case EvqBuffer:
        requireProfile(loc, ECoreProfile | ECompatibilityProfile, "buffer block");
        profileRequires(loc, ECoreProfile | ECompatibilityProfile, 430, 0, "buffer block");
        break;
    case EvqUniform:
        profileRequires(loc, EEsProfile, 300, 0, "uniform block");
        profileRequires(loc, ENoProfile, 140, 0, "uniform block");
        break;
    case EvqVaryingIn:
        requireProfile(loc, ~EEsProfile, "input block");
        profileRequires(loc, ~EEsProfile, 150, GL_ARB_separate_shader_objects, "input block");
        break;
    case EvqVaryingOut:
        requireProfile(loc, ~EEsProfile, "output block");
        profileRequires(loc, ~EEsProfile, 150, GL_ARB_separate_shader_objects, "output block");
        break;
    default:
        error(loc, "only uniform, buffer, in, or out blocks are supported", blockName->c_str(), "");
        return;
    }

    arrayDimCheck(loc, arraySizes, 0);

    // fix and check for member storage qualifiers and types that don't belong within a block
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        TSourceLoc memberLoc = typeList[member].loc;
        pipeInOutFix(memberLoc, memberQualifier);
        if (memberQualifier.storage != EvqTemporary && memberQualifier.storage != EvqGlobal && memberQualifier.storage != currentBlockQualifier.storage)
            error(memberLoc, "member storage qualifier cannot contradict block storage qualifier", typeList[member].type->getFieldName().c_str(), "");
        memberQualifier.storage = currentBlockQualifier.storage;
        if (currentBlockQualifier.storage == EvqUniform && (memberQualifier.isInterpolation() || memberQualifier.isAuxiliary()))
            error(memberLoc, "member of uniform block cannot have an auxiliary or interpolation qualifier", typeList[member].type->getFieldName().c_str(), "");

        TBasicType basicType = typeList[member].type->getBasicType();
        if (basicType == EbtSampler)
            error(memberLoc, "member of block cannot be a sampler type", typeList[member].type->getFieldName().c_str(), "");
    }

    // This might be a redeclaration of a built-in block.  If so, redeclareBuiltinBlock() will
    // do all the rest.
    if (! symbolTable.atBuiltInLevel() && builtInName(*blockName)) {
        redeclareBuiltinBlock(loc, typeList, *blockName, instanceName, arraySizes);
        return;
    }

    // Not a redeclaration of a built-in; check that all names are user names.
    reservedErrorCheck(loc, *blockName);
    if (instanceName)
        reservedErrorCheck(loc, *instanceName);
    for (unsigned int member = 0; member < typeList.size(); ++member)
        reservedErrorCheck(typeList[member].loc, typeList[member].type->getFieldName());

    // Make default block qualification, and adjust the member qualifications

    TQualifier defaultQualification;
    switch (currentBlockQualifier.storage) {
    case EvqBuffer:     defaultQualification = globalBufferDefaults;     break;
    case EvqUniform:    defaultQualification = globalUniformDefaults;    break;
    case EvqVaryingIn:  defaultQualification = globalInputDefaults;      break;
    case EvqVaryingOut: defaultQualification = globalOutputDefaults;     break;
    default:            defaultQualification.clear();                    break;
    }

    // fix and check for member layout qualifiers

    mergeObjectLayoutQualifiers(loc, defaultQualification, currentBlockQualifier, true);

    // "The offset qualifier can only be used on block members of blocks declared with std140 or std430 layouts."
    // "The align qualifier can only be used on blocks or block members, and only for blocks declared with std140 or std430 layouts."
    if (currentBlockQualifier.hasAlign() || currentBlockQualifier.hasAlign()) {
        if (defaultQualification.layoutPacking != ElpStd140 && defaultQualification.layoutPacking != ElpStd430) {
            error(loc, "can only be used with std140 or std430 layout packing", "offset/align", "");
            defaultQualification.layoutAlign = -1;
        }
    }

    bool memberWithLocation = false;
    bool memberWithoutLocation = false;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        TSourceLoc memberLoc = typeList[member].loc;
        if (memberQualifier.hasStream()) {
            if (defaultQualification.layoutStream != memberQualifier.layoutStream)
                error(memberLoc, "member cannot contradict block", "stream", "");
        }

        // "This includes a block's inheritance of the 
        // current global default buffer, a block member's inheritance of the block's 
        // buffer, and the requirement that any *xfb_buffer* declared on a block 
        // member must match the buffer inherited from the block."
        if (memberQualifier.hasXfbBuffer()) {
            if (defaultQualification.layoutXfbBuffer != memberQualifier.layoutXfbBuffer)
                error(memberLoc, "member cannot contradict block (or what block inherited from global)", "xfb_buffer", "");
        }

        if (memberQualifier.hasPacking())
            error(memberLoc, "member of block cannot have a packing layout qualifier", typeList[member].type->getFieldName().c_str(), "");
        if (memberQualifier.hasLocation()) {
            const char* feature = "location on block member";
            switch (currentBlockQualifier.storage) {
            case EvqVaryingIn:
            case EvqVaryingOut:
                requireProfile(memberLoc, ECoreProfile | ECompatibilityProfile, feature);
                profileRequires(memberLoc, ECoreProfile | ECompatibilityProfile, 440, GL_ARB_enhanced_layouts, feature);
                memberWithLocation = true;
                break;
            default:
                error(memberLoc, "can only use in an in/out block", feature, "");
                break;
            }
        } else
            memberWithoutLocation = true;
        if (memberQualifier.hasAlign()) {
            if (defaultQualification.layoutPacking != ElpStd140 && defaultQualification.layoutPacking != ElpStd430)
                error(memberLoc, "can only be used with std140 or std430 layout packing", "align", "");
        }

        TQualifier newMemberQualification = defaultQualification;
        mergeQualifiers(memberLoc, newMemberQualification, memberQualifier, false);
        memberQualifier = newMemberQualification;
    }

    // Process the members
    fixBlockLocations(loc, currentBlockQualifier, typeList, memberWithLocation, memberWithoutLocation);
    fixBlockXfbOffsets(loc, currentBlockQualifier, typeList);
    fixBlockUniformOffsets(loc, currentBlockQualifier, typeList);
    for (unsigned int member = 0; member < typeList.size(); ++member)
        layoutTypeCheck(typeList[member].loc, *typeList[member].type);

    // reverse merge, so that currentBlockQualifier now has all layout information
    // (can't use defaultQualification directly, it's missing other non-layout-default-class qualifiers)
    mergeObjectLayoutQualifiers(loc, currentBlockQualifier, defaultQualification, true);

    //
    // Build and add the interface block as a new type named 'blockName'
    //

    TType blockType(&typeList, *blockName, currentBlockQualifier);
    if (arraySizes)
        blockType.setArraySizes(arraySizes);
    else
        ioArrayCheck(loc, blockType, instanceName ? *instanceName : *blockName);

    //
    // Don't make a user-defined type out of block name; that will cause an error
    // if the same block name gets reused in a different interface.
    //
    // "Block names have no other use within a shader
    // beyond interface matching; it is a compile-time error to use a block name at global scope for anything
    // other than as a block name (e.g., use of a block name for a global variable name or function name is
    // currently reserved)."
    //
    // Use the symbol table to prevent normal reuse of the block's name, as a variable entry,
    // whose type is EbtBlock, but without all the structure; that will come from the type
    // the instances point to.
    //
    TType blockNameType(EbtBlock, blockType.getQualifier().storage);
    TVariable* blockNameVar = new TVariable(blockName, blockNameType);
    if (! symbolTable.insert(*blockNameVar)) {
        TSymbol* existingName = symbolTable.find(*blockName);
        if (existingName->getType().getBasicType() == EbtBlock) {
            if (existingName->getType().getQualifier().storage == blockType.getQualifier().storage) {
                error(loc, "Cannot reuse block name within the same interface:", blockName->c_str(), blockType.getStorageQualifierString());
                return;
            }
        } else {
            error(loc, "block name cannot redefine a non-block name", blockName->c_str(), "");
            return;
        }
    }

    // Add the variable, as anonymous or named instanceName.
    // Make an anonymous variable if no name was provided.
    if (! instanceName)
        instanceName = NewPoolTString("");

    TVariable& variable = *new TVariable(instanceName, blockType);
    if (! symbolTable.insert(variable)) {
        if (*instanceName == "")
            error(loc, "nameless block contains a member that already has a name at global scope", blockName->c_str(), "");
        else
            error(loc, "block instance name redefinition", variable.getName().c_str(), "");

        return;
    }

    // Check for general layout qualifier errors
    layoutObjectCheck(loc, variable);

    if (isIoResizeArray(blockType)) {
        ioArraySymbolResizeList.push_back(&variable);
        checkIoArraysConsistency(loc, true);
    } else
        fixIoArraySize(loc, variable.getWritableType());

    // Save it in the AST for linker use.
    intermediate.addSymbolLinkageNode(linkage, variable);
}

//
// "For a block, this process applies to the entire block, or until the first member 
// is reached that has a location layout qualifier. When a block member is declared with a location 
// qualifier, its location comes from that qualifier: The member's location qualifier overrides the block-level
// declaration. Subsequent members are again assigned consecutive locations, based on the newest location, 
// until the next member declared with a location qualifier. The values used for locations do not have to be 
// declared in increasing order."
void TParseContext::fixBlockLocations(TSourceLoc loc, TQualifier& qualifier, TTypeList& typeList, bool memberWithLocation, bool memberWithoutLocation)
{
    // "If a block has no block-level location layout qualifier, it is required that either all or none of its members 
    // have a location layout qualifier, or a compile-time error results."
    if (! qualifier.hasLocation() && memberWithLocation && memberWithoutLocation)
        error(loc, "either the block needs a location, or all members need a location, or no members have a location", "location", "");
    else {
        if (memberWithLocation) {
            // remove any block-level location and make it per *every* member
            int nextLocation;  // by the rule above, initial value is not relevant
            if (qualifier.hasLocation()) {
                nextLocation = qualifier.layoutLocation;
                qualifier.layoutLocation = TQualifier::layoutLocationEnd;
                if (qualifier.layoutComponent != TQualifier::layoutComponentEnd) {
                    // "It is a compile-time error to apply the *component* qualifier to a ... block"
                    error(loc, "cannot apply to a block", "component", "");
                }
            }
            for (unsigned int member = 0; member < typeList.size(); ++member) {
                TQualifier& memberQualifier = typeList[member].type->getQualifier();
                TSourceLoc memberLoc = typeList[member].loc;
                if (! memberQualifier.hasLocation()) {
                    if (nextLocation >= TQualifier::layoutLocationEnd)
                        error(memberLoc, "location is too large", "location", "");
                    memberQualifier.layoutLocation = nextLocation;
                    memberQualifier.layoutComponent = 0;
                }
                nextLocation = memberQualifier.layoutLocation + intermediate.computeTypeLocationSize(*typeList[member].type);
            }
        }
    }
}

void TParseContext::fixBlockXfbOffsets(TSourceLoc loc, TQualifier& qualifier, TTypeList& typeList)
{
    // "If a block is qualified with xfb_offset, all its 
    // members are assigned transform feedback buffer offsets. If a block is not qualified with xfb_offset, any 
    // members of that block not qualified with an xfb_offsetwill not be assigned transform feedback buffer 
    // offsets."

    if (! qualifier.hasXfbBuffer() || ! qualifier.hasXfbOffset())
        return;

    int nextOffset = qualifier.layoutXfbOffset;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        bool containsDouble = false;
        int memberSize = intermediate.computeTypeXfbSize(*typeList[member].type, containsDouble);
        // see if we need to auto-assign an offset to this member
        if (! memberQualifier.hasXfbOffset()) {
            // "if applied to an aggregate containing a double, the offset must also be a multiple of 8"
            if (containsDouble)
                RoundToPow2(nextOffset, 8);
            memberQualifier.layoutXfbOffset = nextOffset;
        } else
            nextOffset = memberQualifier.layoutXfbOffset;
        nextOffset += memberSize;
    }

    // The above gave all block members an offset, so we can take it off the block now,
    // which will avoid double counting the offset usage.
    qualifier.layoutXfbOffset = TQualifier::layoutXfbOffsetEnd;
}

// Calculate and save the offset of each block member, using the recursively 
// defined block offset rules and the user-provided offset and align.
//
// Also, compute and save the total size of the block. For the block's size, arrayness 
// is not taken into account, as each element is backed by a separate buffer.
//
void TParseContext::fixBlockUniformOffsets(TSourceLoc loc, TQualifier& qualifier, TTypeList& typeList)
{
    if (qualifier.storage != EvqUniform && qualifier.storage != EvqBuffer)
        return;
    if (qualifier.layoutPacking != ElpStd140 && qualifier.layoutPacking != ElpStd430)
        return;

    int offset = 0;
    int memberSize;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        TSourceLoc memberLoc = typeList[member].loc;

        // "When align is applied to an array, it effects only the start of the array, not the array's internal stride."
        
        int memberAlignment = intermediate.getBaseAlignment(*typeList[member].type, memberSize, qualifier.layoutPacking == ElpStd140);
        if (memberQualifier.hasOffset()) {
            // "The specified offset must be a multiple 
            // of the base alignment of the type of the block member it qualifies, or a compile-time error results."
            if (! IsMultipleOfPow2(memberQualifier.layoutOffset, memberAlignment))
                error(memberLoc, "must be a multiple of the member's alignment", "offset", "");

            // "It is a compile-time error to specify an offset that is smaller than the offset of the previous 
            // member in the block or that lies within the previous member of the block"
            if (memberQualifier.layoutOffset < offset)
                error(memberLoc, "cannot lie in previous members", "offset", "");

            // "The offset qualifier forces the qualified member to start at or after the specified 
            // integral-constant expression, which will be its byte offset from the beginning of the buffer. 
            // "The actual offset of a member is computed as 
            // follows: If offset was declared, start with that offset, otherwise start with the next available offset."
            offset = std::max(offset, memberQualifier.layoutOffset);
        }

        // "The actual alignment of a member will be the greater of the specified align alignment and the standard 
        // (e.g., std140) base alignment for the member's type."
        if (memberQualifier.hasAlign())
            memberAlignment = std::max(memberAlignment, memberQualifier.layoutAlign);

        // "If the resulting offset is not a multiple of the actual alignment,
        // increase it to the first offset that is a multiple of 
        // the actual alignment."
        RoundToPow2(offset, memberAlignment);
        typeList[member].type->getQualifier().layoutOffset = offset;
        offset += memberSize;
    }
}

// For an identifier that is already declared, add more qualification to it.
void TParseContext::addQualifierToExisting(TSourceLoc loc, TQualifier qualifier, const TString& identifier)
{
    TSymbol* symbol = symbolTable.find(identifier);
    if (! symbol) {
        error(loc, "identifier not previously declared", identifier.c_str(), "");
        return;
    }
    if (symbol->getAsFunction()) {
        error(loc, "cannot re-qualify a function name", identifier.c_str(), "");
        return;
    }

    if (qualifier.isAuxiliary() ||
        qualifier.isMemory() ||
        qualifier.isInterpolation() ||
        qualifier.hasLayout() ||
        qualifier.storage != EvqTemporary ||
        qualifier.precision != EpqNone) {
        error(loc, "cannot add storage, auxiliary, memory, interpolation, layout, or precision qualifier to an existing variable", identifier.c_str(), "");
        return;
    }

    // For read-only built-ins, add a new symbol for holding the modified qualifier.
    // This will bring up an entire block, if a block type has to be modified (e.g., gl_Position inside a block)
    if (symbol->isReadOnly())
        symbol = symbolTable.copyUp(symbol);

    if (qualifier.invariant) {
        if (intermediate.inIoAccessed(identifier))
            error(loc, "cannot change qualification after use", "invariant", "");
        symbol->getWritableType().getQualifier().invariant = true;
        invariantCheck(loc, symbol->getType(), identifier);
    } else
        warn(loc, "unknown requalification", "", "");
}

void TParseContext::addQualifierToExisting(TSourceLoc loc, TQualifier qualifier, TIdentifierList& identifiers)
{
    for (unsigned int i = 0; i < identifiers.size(); ++i)
        addQualifierToExisting(loc, qualifier, *identifiers[i]);
}

void TParseContext::invariantCheck(TSourceLoc loc, const TType& type, const TString& identifier)
{
    if (! type.getQualifier().invariant)
        return;

    bool pipeOut = type.getQualifier().isPipeOutput();
    bool pipeIn = type.getQualifier().isPipeInput();
    if (version >= 300 || profile != EEsProfile && version >= 420) {
        if (! pipeOut)
            error(loc, "can only apply to an output:", "invariant", identifier.c_str());
    } else {
        if ((language == EShLangVertex && pipeIn) || (! pipeOut && ! pipeIn))
            error(loc, "can only apply to an output or an input in a non-vertex stage\n", "invariant", "");
    }
}

//
// Updating default qualifier for the case of a declaration with just a qualifier,
// no type, block, or identifier.
//
void TParseContext::updateStandaloneQualifierDefaults(TSourceLoc loc, const TPublicType& publicType)
{
    if (publicType.shaderQualifiers.vertices) {
        assert(language == EShLangTessControl || language == EShLangGeometry);
        const char* id = (language == EShLangTessControl) ? "vertices" : "max_vertices";

        if (publicType.qualifier.storage != EvqVaryingOut)
            error(loc, "can only apply to 'out'", id, "");
        if (! intermediate.setVertices(publicType.shaderQualifiers.vertices))
            error(loc, "cannot change previously set layout value", id, "");
        
        if (language == EShLangTessControl)
            checkIoArraysConsistency(loc);
    }
    if (publicType.shaderQualifiers.invocations) {
        if (publicType.qualifier.storage != EvqVaryingIn)
            error(loc, "can only apply to 'in'", "invocations", "");
        if (! intermediate.setInvocations(publicType.shaderQualifiers.invocations))
            error(loc, "cannot change previously set layout value", "invocations", "");
    }
    if (publicType.shaderQualifiers.geometry != ElgNone) {
        if (publicType.qualifier.storage == EvqVaryingIn) {
            switch (publicType.shaderQualifiers.geometry) {
            case ElgPoints:
            case ElgLines:
            case ElgLinesAdjacency:
            case ElgTriangles:
            case ElgTrianglesAdjacency:
            case ElgQuads:
            case ElgIsolines:
                if (intermediate.setInputPrimitive(publicType.shaderQualifiers.geometry)) {
                    if (language == EShLangGeometry)
                        checkIoArraysConsistency(loc);
                } else
                    error(loc, "cannot change previously set input primitive", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), "");
                break;
            default:
                error(loc, "cannot apply to input", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), "");
            }
        } else if (publicType.qualifier.storage == EvqVaryingOut) {
            switch (publicType.shaderQualifiers.geometry) {
            case ElgPoints:
            case ElgLineStrip:
            case ElgTriangleStrip:
                if (! intermediate.setOutputPrimitive(publicType.shaderQualifiers.geometry))
                    error(loc, "cannot change previously set output primitive", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), "");
                break;
            default:
                error(loc, "cannot apply to 'out'", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), "");
            }
        } else
            error(loc, "cannot apply to:", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), GetStorageQualifierString(publicType.qualifier.storage));
    }
    if (publicType.shaderQualifiers.spacing != EvsNone) {
        if (publicType.qualifier.storage == EvqVaryingIn) {
            if (! intermediate.setVertexSpacing(publicType.shaderQualifiers.spacing))
                error(loc, "cannot change previously set vertex spacing", TQualifier::getVertexSpacingString(publicType.shaderQualifiers.spacing), "");
        } else
            error(loc, "can only apply to 'in'", TQualifier::getVertexSpacingString(publicType.shaderQualifiers.spacing), "");
    }
    if (publicType.shaderQualifiers.order != EvoNone) {
        if (publicType.qualifier.storage == EvqVaryingIn) {
            if (! intermediate.setVertexOrder(publicType.shaderQualifiers.order))
                error(loc, "cannot change previously set vertex order", TQualifier::getVertexOrderString(publicType.shaderQualifiers.order), "");
        } else
            error(loc, "can only apply to 'in'", TQualifier::getVertexOrderString(publicType.shaderQualifiers.order), "");
    }
    if (publicType.shaderQualifiers.pointMode) {
        if (publicType.qualifier.storage == EvqVaryingIn)
            intermediate.setPointMode();
        else
            error(loc, "can only apply to 'in'", "point_mode", "");
    }

    const TQualifier& qualifier = publicType.qualifier;

    if (qualifier.isAuxiliary() ||
        qualifier.isMemory() ||
        qualifier.isInterpolation() ||
        qualifier.precision != EpqNone)
        error(loc, "cannot use auxiliary, memory, interpolation, or precision qualifier in a default qualifier declaration (declaration with no type)", "qualifier", "");
    // "The offset qualifier can only be used on block members of blocks..."
    // "The align qualifier can only be used on blocks or block members..."
    if (qualifier.hasOffset() ||
        qualifier.hasAlign())
        error(loc, "cannot use offset or align qualifiers in a default qualifier declaration (declaration with no type)", "layout qualifier", "");

    layoutQualifierCheck(loc, qualifier);

    switch (qualifier.storage) {
    case EvqUniform:
        if (qualifier.hasMatrix())
            globalUniformDefaults.layoutMatrix = qualifier.layoutMatrix;
        if (qualifier.hasPacking())
            globalUniformDefaults.layoutPacking = qualifier.layoutPacking;
        break;
    case EvqBuffer:
        if (qualifier.hasMatrix())
            globalBufferDefaults.layoutMatrix = qualifier.layoutMatrix;
        if (qualifier.hasPacking())
            globalBufferDefaults.layoutPacking = qualifier.layoutPacking;
        break;
    case EvqVaryingIn:
        break;
    case EvqVaryingOut:
        if (qualifier.hasStream())
            globalOutputDefaults.layoutStream = qualifier.layoutStream;
        if (qualifier.hasXfbBuffer())
            globalOutputDefaults.layoutXfbBuffer = qualifier.layoutXfbBuffer;
        if (globalOutputDefaults.hasXfbBuffer() && qualifier.hasXfbStride()) {
            if (! intermediate.setXfbBufferStride(globalOutputDefaults.layoutXfbBuffer, qualifier.layoutXfbStride))
                error(loc, "all stride settings must match for xfb buffer", "xfb_stride", "%d", qualifier.layoutXfbBuffer);
        }
        break;
    default:
        error(loc, "default qualifier requires 'uniform', 'buffer', 'in', or 'out' storage qualification", "", "");
        return;
    }

    if (qualifier.hasBinding())
        error(loc, "cannot declare a default, include a type or full declaration", "binding", "");
    if (qualifier.hasLocation())
        error(loc, "cannot declare a default, use a full declaration", "location", "");
    if (qualifier.hasXfbOffset())
        error(loc, "cannot declare a default, use a full declaration", "xfb_offset", "");
}

//
// Take the sequence of statements that has been built up since the last case/default,
// put it on the list of top-level nodes for the current (inner-most) switch statement,
// and follow that by the case/default we are on now.  (See switch topology comment on
// TIntermSwitch.)
//
void TParseContext::wrapupSwitchSubsequence(TIntermAggregate* statements, TIntermNode* branchNode)
{
    TIntermSequence* switchSequence = switchSequenceStack.back();

    if (statements) {
        if (switchSequence->size() == 0)
            error(statements->getLoc(), "cannot have statements before first case/default label", "switch", "");
        statements->setOperator(EOpSequence);
        switchSequence->push_back(statements);
    }
    if (branchNode) {
        // check all previous cases for the same label (or both are 'default')
        for (unsigned int s = 0; s < switchSequence->size(); ++s) {
            TIntermBranch* prevBranch = (*switchSequence)[s]->getAsBranchNode();
            if (prevBranch) {
                TIntermTyped* prevExpression = prevBranch->getExpression();
                TIntermTyped* newExpression = branchNode->getAsBranchNode()->getExpression();
                if (prevExpression == 0 && newExpression == 0)
                    error(branchNode->getLoc(), "duplicate label", "default", "");
                else if (prevExpression != 0 &&
                          newExpression != 0 &&
                         prevExpression->getAsConstantUnion() &&
                          newExpression->getAsConstantUnion() &&
                         prevExpression->getAsConstantUnion()->getConstArray()[0].getIConst() ==
                          newExpression->getAsConstantUnion()->getConstArray()[0].getIConst())
                    error(branchNode->getLoc(), "duplicated value", "case", "");
            }
        }
        switchSequence->push_back(branchNode);
    }
}

//
// Turn the top-level node sequence built up of wrapupSwitchSubsequence9)
// into a switch node.
//
TIntermNode* TParseContext::addSwitch(TSourceLoc loc, TIntermTyped* expression, TIntermAggregate* lastStatements)
{
    profileRequires(loc, EEsProfile, 300, 0, "switch statements");
    profileRequires(loc, ENoProfile, 130, 0, "switch statements");

    wrapupSwitchSubsequence(lastStatements, 0);

    if (expression == 0 ||
        (expression->getBasicType() != EbtInt && expression->getBasicType() != EbtUint) ||
        expression->getType().isArray() || expression->getType().isMatrix() || expression->getType().isVector())
            error(loc, "condition must be a scalar integer expression", "switch", "");

    // If there is nothing to do, drop the switch but still execute the expression
    TIntermSequence* switchSequence = switchSequenceStack.back();
    if (switchSequence->size() == 0)
        return expression;

    if (lastStatements == 0) {
        error(loc, "last case/default label must be followed by statements", "switch", "");

        return expression;
    }

    TIntermAggregate* body = new TIntermAggregate(EOpSequence);
    body->getSequence() = *switchSequenceStack.back();
    body->setLoc(loc);

    TIntermSwitch* switchNode = new TIntermSwitch(expression, body);
    switchNode->setLoc(loc);

    return switchNode;
}

} // end namespace glslang
