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
#include "Include/InitializeParseContext.h"
#include "osinclude.h"
#include <stdarg.h>
#include <algorithm>

TParseContext::TParseContext(TSymbolTable& symt, TIntermediate& interm, int v, EProfile p, EShLanguage L, TInfoSink& is,                             
                             bool fc, EShMessages m) : 
            intermediate(interm), symbolTable(symt), infoSink(is), language(L), treeRoot(0),
            recoveredFromError(false), numErrors(0), lexAfterType(false), loopNestingLevel(0),
            inTypeParen(false),
            version(v), profile(p), forwardCompatible(fc), messages(m),
            contextPragma(true, false)
{
    for (int type = 0; type < EbtNumTypes; ++type)
        defaultPrecision[type] = EpqNone;

    if (profile == EEsProfile) {
        switch (language) {
        case EShLangVertex:
            defaultPrecision[EbtInt] = EpqHigh;
            defaultPrecision[EbtUint] = EpqHigh;
            defaultPrecision[EbtFloat] = EpqHigh;
            defaultPrecision[EbtSampler] = EpqLow;
            // TODO: functionality: need default precisions per sampler type
            break;
        case EShLangFragment:
            defaultPrecision[EbtInt] = EpqMedium;
            defaultPrecision[EbtUint] = EpqMedium;
            defaultPrecision[EbtSampler] = EpqLow;
            // TODO: semantics: give error when using float in frag shader without default precision
            break;
        default:
            error(1, "INTERNAL ERROR", "unexpected language", "");
        }
    }

    defaultGlobalQualification.clear();
    defaultGlobalQualification.layoutMatrix = ElmColumnMajor;
    defaultGlobalQualification.layoutPacking = ElpShared;
    defaultGlobalQualification.layoutSlotLocation = 0;
}

// Get code that is not part of a shared symbol table, specific to this shader
// or needed by CPP (which does not have a shared symbol table).
const char* TParseContext::getPreamble()
{
    if (profile == EEsProfile)
        return "#define GL_ES 1\n";
    else
        return 0;
}

///////////////////////////////////////////////////////////////////////
//
// Sub- vector and matrix fields
//
////////////////////////////////////////////////////////////////////////

//
// Look at a '.' field selector string and change it into offsets
// for a vector.
//
bool TParseContext::parseVectorFields(const TString& compString, int vecSize, TVectorFields& fields, int line)
{
    fields.num = (int) compString.size();
    if (fields.num > 4) {
        error(line, "illegal vector field selection", compString.c_str(), "");
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
            error(line, "illegal vector field selection", compString.c_str(), "");
            return false;
        }
    }

    for (int i = 0; i < fields.num; ++i) {
        if (fields.offsets[i] >= vecSize) {
            error(line, "vector field selection out of range",  compString.c_str(), "");
            return false;
        }

        if (i > 0) {
            if (fieldSet[i] != fieldSet[i-1]) {
                error(line, "illegal - vector component fields not from the same set", compString.c_str(), "");
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
// Track whether errors have occurred.
//
void TParseContext::recover()
{
    recoveredFromError = true;
}

//
// Used by flex/bison to output all syntax and parsing errors.
//
void C_DECL TParseContext::error(TSourceLoc nLine, const char *szReason, const char *szToken, 
                                 const char *szExtraInfoFormat, ...)
{
	const int maxSize = 400;
    char szExtraInfo[maxSize];
    va_list marker;
    
    va_start(marker, szExtraInfoFormat);
    
    safe_vsprintf(szExtraInfo, maxSize, szExtraInfoFormat, marker);
    
    /* VC++ format: file(linenum) : error #: 'token' : extrainfo */
    infoSink.info.prefix(EPrefixError);
    infoSink.info.location(nLine);
    infoSink.info << "'" << szToken <<  "' : " << szReason << " " << szExtraInfo << "\n";
    
    va_end(marker);

    ++numErrors;
}

//
// Same error message for all places assignments don't work.
//
void TParseContext::assignError(int line, const char* op, TString left, TString right)
{
    error(line, "", op, "cannot convert from '%s' to '%s'",
          right.c_str(), left.c_str());
}

//
// Same error message for all places unary operations don't work.
//
void TParseContext::unaryOpError(int line, const char* op, TString operand)
{
   error(line, " wrong operand type", op, 
          "no operation '%s' exists that takes an operand of type %s (or there is no acceptable conversion)",
          op, operand.c_str());
}

//
// Same error message for all binary operations don't work.
//
void TParseContext::binaryOpError(int line, const char* op, TString left, TString right)
{
    error(line, " wrong operand types:", op,
            "no operation '%s' exists that takes a left-hand operand of type '%s' and "
            "a right operand of type '%s' (or there is no acceptable conversion)", 
            op, left.c_str(), right.c_str());
}

//
// A basic type of EbtVoid is a key that the name string was seen in the source, but
// it was not found as a variable in the symbol table.  If so, give the error
// message and insert a dummy variable in the symbol table to prevent future errors.
//
void TParseContext::variableErrorCheck(TIntermTyped*& nodePtr) 
{
    TIntermSymbol* symbol = nodePtr->getAsSymbolNode();
    if (! symbol)
        return;

    if (symbol->getType().getBasicType() == EbtVoid) {
        error(symbol->getLine(), "undeclared identifier", symbol->getSymbol().c_str(), "");
        recover();

        // Add to symbol table to prevent future error messages on the same name
            
        TVariable* fakeVariable = new TVariable(&symbol->getSymbol(), TType(EbtFloat));
        symbolTable.insert(*fakeVariable);

        // substitute a symbol node for this new variable
        nodePtr = intermediate.addSymbol(fakeVariable->getUniqueId(), 
                                         fakeVariable->getName(), 
                                         fakeVariable->getType(), symbol->getLine());
    } else {
        switch (symbol->getQualifier().storage) {
        case EvqPointCoord:
            profileRequires(symbol->getLine(), ENoProfile, 120, 0, "gl_PointCoord");
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
bool TParseContext::lValueErrorCheck(int line, const char* op, TIntermTyped* node)
{
    TIntermSymbol* symNode = node->getAsSymbolNode();
    TIntermBinary* binaryNode = node->getAsBinaryNode();

    if (binaryNode) {
        bool errorReturn;

        switch(binaryNode->getOp()) {
        case EOpIndexDirect:
        case EOpIndexIndirect:
        case EOpIndexDirectStruct:
            return lValueErrorCheck(line, op, binaryNode->getLeft());
        case EOpVectorSwizzle:
            errorReturn = lValueErrorCheck(line, op, binaryNode->getLeft());
            if (!errorReturn) {
                int offset[4] = {0,0,0,0};

                TIntermTyped* rightNode = binaryNode->getRight();
                TIntermAggregate *aggrNode = rightNode->getAsAggregate();
                
                for (TIntermSequence::iterator p = aggrNode->getSequence().begin(); 
                                               p != aggrNode->getSequence().end(); p++) {
                    int value = (*p)->getAsTyped()->getAsConstantUnion()->getUnionArrayPointer()->getIConst();
                    offset[value]++;     
                    if (offset[value] > 1) {
                        error(line, " l-value of swizzle cannot have duplicate components", op, "", "");

                        return true;
                    }
                }
            } 

            return errorReturn;
        default: 
            break;
        }
        error(line, " l-value required", op, "", "");

        return true;
    }


    const char* symbol = 0;
    if (symNode != 0)
        symbol = symNode->getSymbol().c_str();

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
        error(line, " l-value required", op, "", "");

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
        error(line, " l-value required", op, "\"%s\" (%s)", symbol, message);
    else
        error(line, " l-value required", op, "(%s)", message);

    return true;
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// a constant.
//
// Returns true if the was an error.
//
bool TParseContext::constErrorCheck(TIntermTyped* node)
{
    if (node->getQualifier().storage == EvqConst)
        return false;

    error(node->getLine(), "constant expression required", "", "");

    return true;
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// an integer.
//
// Returns true if the was an error.
//
bool TParseContext::integerErrorCheck(TIntermTyped* node, const char* token)
{
    if ((node->getBasicType() == EbtInt || node->getBasicType() == EbtUint) && node->getVectorSize() == 1 && ! node->isArray())
        return false;

    error(node->getLine(), "scalar integer expression required", token, "");

    return true;
}

//
// Both test, and if necessary spit out an error, to see if we are currently
// globally scoped.
//
// Returns true if the was an error.
//
bool TParseContext::globalErrorCheck(int line, bool global, const char* token)
{
    if (global)
        return false;

    error(line, "only allowed at global scope", token, "");

    return true;
}

//
// For now, keep it simple:  if it starts "gl_", it's reserved, independent
// of scope.  Except, if the symbol table is at the built-in push-level,
// which is when we are parsing built-ins.
//
// Returns true if there was an error.
//
bool TParseContext::reservedErrorCheck(int line, const TString& identifier)
{
    if (!symbolTable.atBuiltInLevel()) {
        if (identifier.substr(0, 3) == TString("gl_")) {
            error(line, "reserved built-in name", "gl_", "");
            return true;
        }
        if (identifier.find("__") != TString::npos) {
            //error(line, "Two consecutive underscores are reserved for future use.", identifier.c_str(), "", "");
            //return true;
            // TODO: semantics: make this an error
            infoSink.info.message(EPrefixWarning, "Two consecutive underscores are reserved for future use.", line);
            return false;
        }
    }

    return false;
}

//
// Make sure there is enough data provided to the constructor to build
// something of the type of the constructor.  Also returns the type of
// the constructor.
//
// Returns true if there was an error in construction.
//
bool TParseContext::constructorErrorCheck(int line, TIntermNode* node, TFunction& function, TOperator op, TType* type)
{
    *type = function.getReturnType();

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
        size += function[i].type->getObjectSize();
        
        if (constructingMatrix && function[i].type->isMatrix())
            matrixInMatrix = true;
        if (full)
            overFull = true;
        if (op != EOpConstructStruct && !type->isArray() && size >= type->getObjectSize())
            full = true;
        if (function[i].type->getQualifier().storage != EvqConst)
            constType = false;
        if (function[i].type->isArray())
            arrayArg = true;
    }
    
    if (constType)
        type->getQualifier().storage = EvqConst;

    if (type->isArray()) {
        if (type->getArraySize() == 0) {
            // auto adapt the constructor type to the number of arguments
            type->changeArraySize(function.getParamCount());
        } else if (type->getArraySize() != function.getParamCount()) {
            error(line, "array constructor needs one argument per array element", "constructor", "");
            return true;
        }
    }

    if (arrayArg && op != EOpConstructStruct) {
        error(line, "constructing from a non-dereferenced array", "constructor", "");
        return true;
    }

    if (matrixInMatrix && !type->isArray()) {
        profileRequires(line, ENoProfile, 120, 0, "constructing matrix from matrix");
        return false;
    }

    if (overFull) {
        error(line, "too many arguments", "constructor", "");
        return true;
    }
    
    if (op == EOpConstructStruct && !type->isArray() && type->getStruct()->size() != function.getParamCount()) {
        error(line, "Number of constructor parameters does not match the number of structure fields", "constructor", "");
        return true;
    }

    if ((op != EOpConstructStruct && size != 1 && size < type->getObjectSize()) ||
        (op == EOpConstructStruct && size < type->getObjectSize())) {
        error(line, "not enough data provided for construction", "constructor", "");
        return true;
    }

    TIntermTyped* typed = node->getAsTyped();
    if (typed == 0) {
        error(line, "constructor argument does not have a type", "constructor", "");
        return true;
    }
    if (op != EOpConstructStruct && typed->getBasicType() == EbtSampler) {
        error(line, "cannot convert a sampler", "constructor", "");
        return true;
    }
    if (typed->getBasicType() == EbtVoid) {
        error(line, "cannot convert a void", "constructor", "");
        return true;
    }

    return false;
}

// This function checks to see if a void variable has been declared and raise an error message for such a case
//
// returns true in case of an error
//
bool TParseContext::voidErrorCheck(int line, const TString& identifier, const TPublicType& pubType)
{
    if (pubType.basicType == EbtVoid) {
        error(line, "illegal use of type 'void'", identifier.c_str(), "");
        return true;
    } 

    return false;
}

// This function checks to see if the node (for the expression) contains a scalar boolean expression or not
//
// returns true in case of an error
//
bool TParseContext::boolErrorCheck(int line, const TIntermTyped* type)
{
    if (type->getBasicType() != EbtBool || type->isArray() || type->isMatrix() || type->isVector()) {
        error(line, "boolean expression expected", "", "");
        return true;
    } 

    return false;
}

// This function checks to see if the node (for the expression) contains a scalar boolean expression or not
//
// returns true in case of an error
//
bool TParseContext::boolErrorCheck(int line, const TPublicType& pType)
{
    if (pType.basicType != EbtBool || pType.arraySizes || pType.matrixCols > 1 || (pType.vectorSize > 1)) {
        error(line, "boolean expression expected", "", "");
        return true;
    } 

    return false;
}

bool TParseContext::samplerErrorCheck(int line, const TPublicType& pType, const char* reason)
{
    if (pType.basicType == EbtStruct) {
        if (containsSampler(*pType.userDef)) {
            error(line, reason, TType::getBasicString(pType.basicType), "(structure cannot contain a sampler or image)");
        
            return true;
        }
        
        return false;
    } else if (pType.basicType == EbtSampler) {
        error(line, reason, TType::getBasicString(pType.basicType), "");

        return true;
    }

    return false;
}

bool TParseContext::globalQualifierFixAndErrorCheck(int line, TQualifier& qualifier, const TPublicType& publicType)
{
    if (! symbolTable.atGlobalLevel())
        return false;

    // First, move from parameter qualifiers to shader in/out qualifiers

    switch (qualifier.storage) {
    case EvqIn:
        profileRequires(line, ENoProfile, 130, 0, "in for stage inputs");
        profileRequires(line, EEsProfile, 300, 0, "in for stage inputs");
        qualifier.storage = EvqVaryingIn;
        break;
    case EvqOut:
        profileRequires(line, ENoProfile, 130, 0, "out for stage outputs");
        profileRequires(line, EEsProfile, 300, 0, "out for stage outputs");
        qualifier.storage = EvqVaryingOut;
        break;
    case EvqVaryingIn:
    case EvqVaryingOut:
        break;
    case EvqInOut:
        qualifier.storage = EvqVaryingIn;
        error(line, "cannot use 'inout' at global scope", "", "");

        return true;
    default:
        break;
    }

    // Do non in/out error checks

    if (qualifier.storage != EvqUniform && samplerErrorCheck(line, publicType, "samplers and images must be uniform"))
        return true;

    if (qualifier.storage != EvqVaryingIn && qualifier.storage != EvqVaryingOut)
        return false;

    // now, knowing it is a shader in/out, do all the in/out semantic checks

    if (publicType.basicType == EbtBool) {
        error(line, "cannot be bool",  getStorageQualifierString(qualifier.storage), "");
        return true;
    }

    if (language == EShLangVertex && qualifier.storage == EvqVaryingIn) {
        if (publicType.basicType == EbtStruct) {
            error(line, "cannot be a structure or array",  getStorageQualifierString(qualifier.storage), "");
            return true;
        }
        if (publicType.arraySizes) {
            requireProfile(line, (EProfileMask)~EEsProfileMask, "vertex input arrays");
            profileRequires(line, ENoProfile, 150, 0, "vertex input arrays");
        }
    }

    if (language == EShLangFragment && qualifier.storage == EvqVaryingOut) {
        profileRequires(line, EEsProfile, 300, 0, "fragment shader output");
        if (publicType.basicType == EbtStruct) {
            error(line, "cannot be a structure",  getStorageQualifierString(qualifier.storage), "");
            return true;
        }
    }

    if (publicType.basicType == EbtInt || publicType.basicType == EbtUint || publicType.basicType == EbtDouble) {
        profileRequires(line, EEsProfile, 300, 0, "shader input/output");
        if (language != EShLangVertex   && qualifier.storage == EvqVaryingIn  && ! qualifier.flat ||
            language != EShLangFragment && qualifier.storage == EvqVaryingOut && ! qualifier.flat) {
            error(line, "must be qualified as 'flat'", getStorageQualifierString(qualifier.storage), TType::getBasicString(publicType.basicType));
         
            return true;
        }
    }

    if (language == EShLangVertex && qualifier.storage == EvqVaryingIn && 
        (qualifier.isAuxillary() || qualifier.isInterpolation() || qualifier.isMemory() || qualifier.invariant)) {
        error(line, "vertex input cannot be further qualified", "", "");

        return true;
    }

    return false;
}

//
// Merge characteristics of the 'src' qualifier into the 'dst'.
// If there is duplication, issue error messages, unless 'force'
// is specified, which means to just override default settings.
// 
// Return true if there was an error.
//
bool TParseContext::mergeQualifiersErrorCheck(int line, TPublicType& dst, const TPublicType& src, bool force)
{
    bool bad = false;

    // Storage qualification
    if (dst.qualifier.storage == EvqTemporary || dst.qualifier.storage == EvqGlobal)
        dst.qualifier.storage = src.qualifier.storage;
    else if (dst.qualifier.storage == EvqIn  && src.qualifier.storage == EvqOut ||
             dst.qualifier.storage == EvqOut && src.qualifier.storage == EvqIn)
        dst.qualifier.storage = EvqInOut;
    else if (dst.qualifier.storage == EvqIn    && src.qualifier.storage == EvqConst ||
             dst.qualifier.storage == EvqConst && src.qualifier.storage == EvqIn)
        dst.qualifier.storage = EvqConstReadOnly;
    else if (src.qualifier.storage != EvqTemporary) {
        error(line, "too many storage qualifiers", getStorageQualifierString(src.qualifier.storage), "");
        bad = true;
    }

    // Precision qualifiers
    if (! force && src.qualifier.precision != EpqNone && dst.qualifier.precision != EpqNone) {
        error(line, "only one precision qualifier allowed", getPrecisionQualifierString(src.qualifier.precision), "");
        bad = true;
    }
    if (dst.qualifier.precision == EpqNone || force && src.qualifier.precision != EpqNone)
        dst.qualifier.precision = src.qualifier.precision;

    // Layout qualifiers
    mergeLayoutQualifiers(line, dst.qualifier, src.qualifier);

    // other qualifiers
    #define MERGE_SINGLETON(field) bad |= dst.qualifier.field && src.qualifier.field; dst.qualifier.field |= src.qualifier.field;
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

    if (bad)
        error(line, "replicated qualifiers", "", "");

    return bad;
}

void TParseContext::setDefaultPrecision(int line, TPublicType& publicType, TPrecisionQualifier qualifier)
{
    TBasicType basicType = publicType.basicType;

    if (basicType == EbtSampler || basicType == EbtInt || basicType == EbtFloat) {
        if (publicType.isScalar()) {
            defaultPrecision[basicType] = qualifier;
            if (basicType == EbtInt)
                defaultPrecision[EbtUint] = qualifier;
            
            return;  // all is well
        }
    }

    error(line, "cannot apply precision statement to this type; use 'float', 'int' or a sampler type", TType::getBasicString(basicType), "");
    recover();
}

bool TParseContext::parameterSamplerErrorCheck(int line, TStorageQualifier qualifier, const TType& type)
{
    if ((qualifier == EvqOut || qualifier == EvqInOut) && 
             type.getBasicType() != EbtStruct && type.getBasicType() == EbtSampler) {
        error(line, "samplers cannot be output parameters", type.getCompleteTypeString().c_str(), "");
        return true;
    }

    return false;
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

bool TParseContext::insertBuiltInArrayAtGlobalLevel()
{
    TString *name = NewPoolTString("gl_TexCoord");
    TSymbol* symbol = symbolTable.find(*name);
    if (! symbol) {
        // assume it was not added due to version/profile

        return false;
    }
    TVariable* variable = symbol->getAsVariable();

    if (! variable) {
        error(0, "INTERNAL ERROR, variable expected", name->c_str(), "");
        return true;
    }

    TVariable* newVariable = new TVariable(name, variable->getType());

    if (! symbolTable.insert(*newVariable)) {
        delete newVariable;
        error(0, "INTERNAL ERROR inserting new symbol", name->c_str(), "");
        return true;
    }

    return false;
}

//
// Do size checking for an array type's size.
//
// Returns true if there was an error.
//
bool TParseContext::arraySizeErrorCheck(int line, TIntermTyped* expr, int& size)
{
    TIntermConstantUnion* constant = expr->getAsConstantUnion();
    if (constant == 0 || (constant->getBasicType() != EbtInt && constant->getBasicType() != EbtUint)) {
        error(line, "array size must be a constant integer expression", "", "");
        size = 1;
        return true;
    }

    size = constant->getUnionArrayPointer()->getIConst();

    if (size <= 0) {
        error(line, "array size must be a positive integer", "", "");
        size = 1;
        return true;
    }

    return false;
}

//
// See if this qualifier can be an array.
//
// Returns true if there is an error.
//
bool TParseContext::arrayQualifierErrorCheck(int line, const TPublicType& type)
{
    if (type.qualifier.storage == EvqConst)
        profileRequires(line, ENoProfile, 120, "GL_3DL_array_objects", "const array");

    if (type.qualifier.storage == EvqVaryingIn && language == EShLangVertex) {
        requireProfile(line, (EProfileMask)~EEsProfileMask, "vertex input arrays");
        profileRequires(line, ENoProfile, 150, 0, "vertex input arrays");
    }

    return false;
}

//
// Require array to have size
//
// Returns true if there is an error.
//
bool TParseContext::arraySizeRequiredErrorCheck(int line, int& size)
{
    if (size == 0) {
        error(line, "array size required", "", "");
        size = 1;

        return true;
    }

    return false;
}

//
// Do all the semantic checking for declaring an array, with and 
// without a size, and make the right changes to the symbol table.
//
// size == 0 means no specified size.
//
// Returns true if there was an error.
//
bool TParseContext::arrayErrorCheck(int line, TString& identifier, const TPublicType& type, TVariable*& variable)
{
    //
    // Don't check for reserved word use until after we know it's not in the symbol table,
    // because reserved arrays can be redeclared.
    //

    bool builtIn = false; 
    bool sameScope = false;
    TSymbol* symbol = symbolTable.find(identifier, &builtIn, &sameScope);
    if (symbol == 0 || !sameScope) {
        if (reservedErrorCheck(line, identifier))
            return true;
        
        variable = new TVariable(&identifier, TType(type));

        if (! symbolTable.insert(*variable)) {
            delete variable;
            error(line, "INTERNAL ERROR inserting new symbol", identifier.c_str(), "");
            return true;
        }
    } else {
        variable = symbol->getAsVariable();

        if (! variable) {
            error(line, "array variable name expected", identifier.c_str(), "");
            return true;
        }

        if (! variable->getType().isArray()) {
            error(line, "redeclaring non-array as array", identifier.c_str(), "");
            return true;
        }
        if (variable->getType().getArraySize() > 0) {
            error(line, "redeclaration of array with size", identifier.c_str(), "");
            return true;
        }
        
        if (! variable->getType().sameElementType(TType(type))) {
            error(line, "redeclaration of array with a different type", identifier.c_str(), "");
            return true;
        }

        TType* t = variable->getArrayInformationType();
        while (t != 0) {
            if (t->getMaxArraySize() > type.arraySizes->front()) {
                error(line, "higher index value already used for the array", identifier.c_str(), "");
                return true;
            }
            t->setArraySizes(type.arraySizes);
            t = t->getArrayInformationType();
        }

        variable->getType().setArraySizes(type.arraySizes);
    } 

    if (voidErrorCheck(line, identifier, type))
        return true;

    return false;
}

bool TParseContext::arraySetMaxSize(TIntermSymbol *node, TType* type, int size, bool updateFlag, TSourceLoc line)
{
    bool builtIn = false;
    TSymbol* symbol = symbolTable.find(node->getSymbol(), &builtIn);
    if (symbol == 0) {
        error(line, " undeclared identifier", node->getSymbol().c_str(), "");
        return true;
    }

    TVariable* variable = symbol->getAsVariable();
    if (! variable) {
        error(0, "array variable name expected", node->getSymbol().c_str(), "");
        return true;
    }

    type->setArrayInformationType(variable->getArrayInformationType());
    variable->updateArrayInformationType(type);

    // special casing to test index value of gl_TexCoord. If the accessed index is >= gl_MaxTextureCoords
    // its an error
    if (node->getSymbol() == "gl_TexCoord") {
        TSymbol* texCoord = symbolTable.find("gl_MaxTextureCoords", &builtIn);
        if (! texCoord || ! texCoord->getAsVariable()) {
            infoSink.info.message(EPrefixInternalError, "gl_MaxTextureCoords not defined", line);
            return true;
        }

        int texCoordValue = texCoord->getAsVariable()->getConstUnionPointer()[0].getIConst();
        if (texCoordValue <= size) {
            error(line, "", "[", "gl_TexCoord can only have a max array size of up to gl_MaxTextureCoords", "");
            return true;
        }
    }

    // we dont want to update the maxArraySize when this flag is not set, we just want to include this 
    // node type in the chain of node types so that its updated when a higher maxArraySize comes in.
    if (!updateFlag)
        return false;

    size++;
    variable->getType().setMaxArraySize(size);
    type->setMaxArraySize(size);
    TType* tt = type;

    while(tt->getArrayInformationType() != 0) {
        tt = tt->getArrayInformationType();
        tt->setMaxArraySize(size);
    }

    return false;
}

//
// Enforce non-initializer type/qualifier rules.
//
// Returns true if there was an error.
//
bool TParseContext::nonInitConstErrorCheck(int line, TString& identifier, TPublicType& type)
{
    //
    // Make the qualifier make sense.
    //
    if (type.qualifier.storage  == EvqConst) {
        type.qualifier.storage = EvqTemporary;
        error(line, "variables with qualifier 'const' must be initialized", identifier.c_str(), "");
        return true;
    }

    return false;
}

//
// Do semantic checking for a variable declaration that has no initializer,
// and update the symbol table.
//
// Returns true if there was an error.
//
bool TParseContext::nonInitErrorCheck(int line, TString& identifier, TPublicType& type)
{
    if (reservedErrorCheck(line, identifier))
        recover();

    TVariable* variable = new TVariable(&identifier, TType(type));

    if (! symbolTable.insert(*variable)) {
        error(line, "redefinition", variable->getName().c_str(), "");
        delete variable;
        return true;
    }

    if (voidErrorCheck(line, identifier, type))
        return true;

    return false;
}

bool TParseContext::paramErrorCheck(int line, TStorageQualifier qualifier, TType* type)
{
    switch (qualifier) {
    case EvqConst:
    case EvqConstReadOnly:
        type->getQualifier().storage = EvqConstReadOnly;
        return false;
    case EvqIn:
    case EvqOut:
    case EvqInOut:
        type->getQualifier().storage = qualifier;
        return false;
    case EvqTemporary:
        type->getQualifier().storage = EvqIn;
        return false;
    default:
        type->getQualifier().storage = EvqIn;
        error(line, "qualifier not allowed on function parameter", getStorageQualifierString(qualifier), "");
        return true;
    }
}

//
// Layout qualifier stuff.
//

// Put the id's layout qualification into the public type.
void TParseContext::setLayoutQualifier(int line, TPublicType& publicType, TString& id)
{
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    if (id == TQualifier::getLayoutMatrixString(ElmColumnMajor))
        publicType.qualifier.layoutMatrix = ElmColumnMajor;
    else if (id == TQualifier::getLayoutMatrixString(ElmRowMajor))
        publicType.qualifier.layoutMatrix = ElmRowMajor;
    else if (id == TQualifier::getLayoutPackingString(ElpPacked))
        publicType.qualifier.layoutPacking = ElpPacked;
    else if (id == TQualifier::getLayoutPackingString(ElpShared))
        publicType.qualifier.layoutPacking = ElpShared;
    else if (id == TQualifier::getLayoutPackingString(ElpStd140))
        publicType.qualifier.layoutPacking = ElpStd140;
    else if (id == TQualifier::getLayoutPackingString(ElpStd430))
        publicType.qualifier.layoutPacking = ElpStd430;
    else if (id == "location")
        error(line, "requires an integer assignment (e.g., location = 4)", "location", "");
    else if (id == "binding")
        error(line, "requires an integer assignment (e.g., binding = 4)", "binding", "");
    else
        error(line, "unrecognized layout identifier", id.c_str(), "");
}

// Put the id's layout qualifier value into the public type.
void TParseContext::setLayoutQualifier(int line, TPublicType& publicType, TString& id, int value)
{
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    if (id == "location") {
        if ((unsigned int)value >= TQualifier::layoutLocationEnd)
            error(line, "value is too large", id.c_str(), "");
        else
            publicType.qualifier.layoutSlotLocation = value;
    } else if (id == "binding")
        error(line, "not supported", "binding", "");
    else
        error(line, "there is no such layout identifier taking an assigned value", id.c_str(), "");

    // TODO: semantics: error check: make sure locations are non-overlapping across the whole stage
    // TODO: semantics: error check: if more than one fragment output, all must have a location
    // TODO: semantics: error check: output arrays can only be indexed with a constant (es 300)
}

// Merge any layout qualifier information from src into dst, leaving everything else in dst alone
void TParseContext::mergeLayoutQualifiers(int line, TQualifier& dst, const TQualifier& src)
{
    if (src.layoutMatrix != ElmNone)
        dst.layoutMatrix = src.layoutMatrix;

    if (src.layoutPacking != ElpNone)
        dst.layoutPacking = src.layoutPacking;

    if (src.hasLocation())
        dst.layoutSlotLocation = src.layoutSlotLocation;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Non-Errors.
//
/////////////////////////////////////////////////////////////////////////////////

//
// Look up a function name in the symbol table, and make sure it is a function.
//
// Return the function symbol if found, otherwise 0.
//
const TFunction* TParseContext::findFunction(int line, TFunction* call, bool *builtIn)
{
    TSymbol* symbol = symbolTable.find(call->getMangledName(), builtIn);

    if (symbol == 0) {        
        error(line, "no matching overloaded function found", call->getName().c_str(), "");

        return 0;
    }
    
    const TFunction* function = symbol->getAsFunction();
    if (! function) {
        error(line, "function name expected", call->getName().c_str(), "");

        return 0;
    }
    
    return function;
}

//
// Initializers show up in several places in the grammar.  Have one set of
// code to handle them here.
//
bool TParseContext::executeInitializer(TSourceLoc line, TString& identifier, TPublicType& pType, 
                                       TIntermTyped* initializer, TIntermNode*& intermNode, TVariable* variable)
{
    TType type(pType);

    if (variable == 0) {
        if (reservedErrorCheck(line, identifier))
            return true;

        if (voidErrorCheck(line, identifier, pType))
            return true;

        //
        // add variable to symbol table
        //
        variable = new TVariable(&identifier, type);
        if (! symbolTable.insert(*variable)) {
            error(line, "redefinition", variable->getName().c_str(), "");
            return true;
            // don't delete variable, it's used by error recovery, and the pool 
            // pop will take care of the memory
        }
    }

    //
    // identifier must be of type constant, a global, or a temporary
    //
    TStorageQualifier qualifier = variable->getType().getQualifier().storage;
    if ((qualifier != EvqTemporary) && (qualifier != EvqGlobal) && (qualifier != EvqConst)) {
        error(line, " cannot initialize this type of qualifier ", variable->getType().getStorageQualifierString(), "");
        return true;
    }

    // Fix arrayness if variable is unsized, getting size for initializer    
    if (initializer->getType().isArray() && initializer->getType().getArraySize() > 0 && 
                            type.isArray() &&                   type.getArraySize() == 0)
        type.changeArraySize(initializer->getType().getArraySize());

    //
    // test for and propagate constant
    //
    if (qualifier == EvqConst) {
        if (qualifier != initializer->getType().getQualifier().storage) {
            error(line, " assigning non-constant to", "=", "'%s'", variable->getType().getCompleteString().c_str());
            variable->getType().getQualifier().storage = EvqTemporary;
            return true;
        }
        if (type != initializer->getType()) {
            error(line, " non-matching types for const initializer ", 
                variable->getType().getStorageQualifierString(), "");
            variable->getType().getQualifier().storage = EvqTemporary;
            return true;
        }
        if (initializer->getAsConstantUnion()) { 
            constUnion* unionArray = variable->getConstUnionPointer();

            if (type.getObjectSize() == 1 && type.getBasicType() != EbtStruct) {
	            *unionArray = (initializer->getAsConstantUnion()->getUnionArrayPointer())[0];
            } else {
                variable->shareConstPointer(initializer->getAsConstantUnion()->getUnionArrayPointer());
            }
        } else if (initializer->getAsSymbolNode()) {
            TSymbol* symbol = symbolTable.find(initializer->getAsSymbolNode()->getSymbol());
            if (TVariable* tVar = symbol->getAsVariable()) {
                constUnion* constArray = tVar->getConstUnionPointer();
                variable->shareConstPointer(constArray);
            } else {
                error(line, "expected variable", initializer->getAsSymbolNode()->getSymbol().c_str(), "");
                return true;
            }
        } else {
            error(line, " cannot assign to", "=", "'%s'", variable->getType().getCompleteString().c_str());
            variable->getType().getQualifier().storage = EvqTemporary;
            return true;
        }
    }
 
    if (qualifier != EvqConst) {
        TIntermSymbol* intermSymbol = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), line);
        intermNode = intermediate.addAssign(EOpAssign, intermSymbol, initializer, line);
        if (intermNode == 0) {
            assignError(line, "=", intermSymbol->getCompleteString(), initializer->getCompleteString());
            return true;
        }
    } else 
        intermNode = 0;

    return false;
}

// This function is used to test for the correctness of the parameters passed to various constructor functions
// and also convert them to the right datatype if it is allowed and required. 
//
// Returns 0 for an error or the constructed node (aggregate or typed) for no error.
//
TIntermTyped* TParseContext::addConstructor(TIntermNode* node, const TType& type, TOperator op, TFunction* fnCall, TSourceLoc line)
{
    if (node == 0)
        return 0;

    TIntermAggregate* aggrNode = node->getAsAggregate();
    
    TTypeList::iterator memberTypes;
    if (op == EOpConstructStruct)
        memberTypes = type.getStruct()->begin();
    
    TType elementType(type);
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
            newNode = constructStruct(node, elementType, 1, node->getLine());
        else if (op == EOpConstructStruct)
            newNode = constructStruct(node, *(*memberTypes).type, 1, node->getLine());
        else
            newNode = constructBuiltIn(type, op, node, node->getLine(), false);

        if (newNode && (type.isArray() || op == EOpConstructStruct))
            newNode = intermediate.setAggregateOperator(newNode, EOpConstructStruct, type, line);

        return newNode;
    }
    
    //
    // Handle list of arguments.
    //
    TIntermSequence &sequenceVector = aggrNode->getSequence() ;    // Stores the information about the parameter to the constructor
    // if the structure constructor contains more than one parameter, then construct
    // each parameter
    
    int paramCount = 0;  // keeps a track of the constructor parameter number being checked    
    
    // for each parameter to the constructor call, check to see if the right type is passed or convert them 
    // to the right type if possible (and allowed).
    // for structure constructors, just check if the right type is passed, no conversion is allowed.
    
    for (TIntermSequence::iterator p = sequenceVector.begin(); 
                                   p != sequenceVector.end(); p++, paramCount++) {
        if (type.isArray())
            newNode = constructStruct(*p, elementType, paramCount+1, node->getLine());
        else if (op == EOpConstructStruct)
            newNode = constructStruct(*p, *(memberTypes[paramCount]).type, paramCount+1, node->getLine());
        else
            newNode = constructBuiltIn(type, op, *p, node->getLine(), true);
        
        if (newNode) {
            p = sequenceVector.erase(p); 
            p = sequenceVector.insert(p, newNode);
        }
    }

    TIntermTyped* constructor = intermediate.setAggregateOperator(aggrNode, op, type, line);

    return constructor;
}

// Function for constructor implementation. Calls addUnaryMath with appropriate EOp value
// for the parameter to the constructor (passed to this function). Essentially, it converts
// the parameter types correctly. If a constructor expects an int (like ivec2) and is passed a 
// float, then float is converted to int.
//
// Returns 0 for an error or the constructed node.
//
TIntermTyped* TParseContext::constructBuiltIn(const TType& type, TOperator op, TIntermNode* node, TSourceLoc line, bool subset)
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
        error(line, "unsupported construction", "", "");
        recover();

        return 0;
    }
    newNode = intermediate.addUnaryMath(basicOp, node, node->getLine());
    if (newNode == 0) {
        error(line, "can't convert", "constructor", "");
        return 0;
    }

    //
    // Now, if there still isn't an operation to do the construction, and we need one, add one.
    //
    
    // Otherwise, skip out early.
    if (subset || newNode != node && newNode->getType() == type)
        return newNode;

    // setAggregateOperator will insert a new node for the constructor, as needed.
    return intermediate.setAggregateOperator(newNode, op, type, line);
}

// This function tests for the type of the parameters to the structures constructors. Raises
// an error message if the expected type does not match the parameter passed to the constructor.
//
// Returns 0 for an error or the input node itself if the expected and the given parameter types match.
//
TIntermTyped* TParseContext::constructStruct(TIntermNode* node, const TType& type, int paramCount, TSourceLoc line)
{
    TIntermTyped* converted = intermediate.addConversion(EOpConstructStruct, type, node->getAsTyped());
    if (! converted || converted->getType() != type) {
        error(line, "", "constructor", "cannot convert parameter %d from '%s' to '%s'", paramCount,
                node->getAsTyped()->getType().getCompleteTypeString().c_str(), type.getCompleteTypeString().c_str());
        recover();

        return 0;
    }

    return converted;
}

//
// Do everything needed to add an interface block.
//
void TParseContext::addBlock(int line, TPublicType& publicType, const TString& blockName, TTypeList& typeList, const TString* instanceName, TArraySizes arraySizes)
{
    // First, error checks

    if (reservedErrorCheck(line, blockName)) {
        recover();

        return;
    }
    if (instanceName && reservedErrorCheck(line, *instanceName)) {
        recover();

        return;
    }
    if (publicType.basicType != EbtVoid) {
        error(line, "interface blocks cannot be declared with a type", blockName.c_str(), "");
        recover();

        return;
    }
    if (publicType.qualifier.storage == EvqUniform) {
        requireProfile(line, (EProfileMask)(~ENoProfileMask), "uniform block");
        profileRequires(line, EEsProfile, 300, 0, "uniform block");
    } else {
        error(line, "only uniform interface blocks are supported", blockName.c_str(), "");
        recover();

        return;
    }

    // check for qualifiers that don't belong within a block
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier memberQualifier = typeList[member].type->getQualifier();
        if (memberQualifier.storage != EvqTemporary && memberQualifier.storage != EvqGlobal &&
            memberQualifier.storage != publicType.qualifier.storage) {
            error(line, "member storage qualifier cannot contradict block storage qualifier", typeList[member].type->getFieldName().c_str(), "");
            recover();
        }
        if (publicType.qualifier.storage == EvqUniform) {
            if (memberQualifier.isInterpolation() || memberQualifier.isAuxillary()) {
                error(line, "member of uniform block cannot have an auxillary or interpolation qualifier", typeList[member].type->getFieldName().c_str(), "");
                recover();
            }
        }
    }

    // Make default block qualification, and adjust the member qualifications

    TQualifier defaultQualification = defaultGlobalQualification;
    mergeLayoutQualifiers(line, defaultQualification, publicType.qualifier);
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier memberQualification = defaultQualification;
        mergeLayoutQualifiers(line, memberQualification, typeList[member].type->getQualifier());
        typeList[member].type->getQualifier() = memberQualification;
    }

    // Build and add the interface block as a new type named blockName

    TType blockType(&typeList, blockName, publicType.qualifier.storage);
    blockType.getQualifier().layoutPacking = defaultQualification.layoutPacking;
    TVariable* userTypeDef = new TVariable(&blockName, blockType, true);
    if (! symbolTable.insert(*userTypeDef)) {
        error(line, "redefinition", blockName.c_str(), "block name");
        recover();

        return;
    }

    // Add the variable, as anonymous or named instanceName

    // make an anonymous variable if no name was provided
    if (! instanceName)
        instanceName = new TString("");

    TVariable* variable = new TVariable(instanceName, blockType);
    if (! symbolTable.insert(*variable)) {
        if (*instanceName == "")
            error(line, "nameless block contains a member that already has a name at global scope", blockName.c_str(), "");
        else
            error(line, "block instance name redefinition", variable->getName().c_str(), "");
        recover();

        return;
    }
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
        if (switchSequence->size() == 0) {
            error(statements->getLine(), "cannot have statements before first case/default label", "switch", "");
            recover();
        }
        statements->setOperator(EOpSequence);
        switchSequence->push_back(statements);
    }
    if (branchNode)
        switchSequence->push_back(branchNode);

    // TODO: semantics: verify no duplicated case values
}

//
// Turn the top-level node sequence built up of wrapupSwitchSubsequence9)
// into a switch node.
//
TIntermNode* TParseContext::addSwitch(int line, TIntermTyped* expression, TIntermAggregate* lastStatements)
{
    profileRequires(line, EEsProfile, 300, 0, "switch statements");
    profileRequires(line, ENoProfile, 130, 0, "switch statements");

    wrapupSwitchSubsequence(lastStatements, 0);

    if (expression == 0 || 
        expression->getBasicType() != EbtInt && expression->getBasicType() != EbtUint ||
        expression->getType().isArray() || expression->getType().isMatrix() || expression->getType().isVector()) {
            error(line, "condition must be a scalar integer expression", "switch", "");
            recover();
    }

    // If there is nothing to do, drop the switch but still execute the expression
    TIntermSequence* switchSequence = switchSequenceStack.back();
    if (switchSequence->size() == 0)
        return expression;

    if (lastStatements == 0) {
        error(line, "last case/default label must be followed by statements", "switch", "");
        recover();

        return expression;
    }

    TIntermAggregate* body = new TIntermAggregate(EOpSequence);
    body->getSequence() = *switchSequenceStack.back();
    body->setLine(line);

    TIntermSwitch* switchNode = new TIntermSwitch(expression, body);
    switchNode->setLine(line);

    return switchNode;
}

void TParseContext::updateDefaults(int line, const TPublicType& publicType, const TString* id)
{
    bool cantHaveId = false;
    TQualifier qualifier = publicType.qualifier;

    if (qualifier.storage == EvqUniform) {
        if (qualifier.layoutMatrix != ElmNone) {
            cantHaveId = true;
            defaultGlobalQualification.layoutMatrix = qualifier.layoutMatrix;
        }
        if (qualifier.layoutPacking != ElpNone) {
            cantHaveId = true;
            defaultGlobalQualification.layoutPacking = qualifier.layoutPacking;
        }
    } else if (qualifier.storage == EvqVaryingIn) {
        if (qualifier.hasLayout() && language != EShLangVertex) {
            error(line, "can only use location layout qualifier on a vertex input or fragment output", id->c_str(), "");
        }
    } else if (qualifier.storage == EvqVaryingOut) {
        if (qualifier.hasLayout() && language != EShLangFragment) {
            error(line, "can only use location layout qualifier on a vertex input or fragment output", id->c_str(), "");
        }
    }

    if (cantHaveId && id) {
        error(line, "cannot set global layout qualifiers on uniform variable, use just 'uniform' or a block", id->c_str(), "");
        recover();
    }
}

//
// This function returns the tree representation for the vector field(s) being accessed from contant vector.
// If only one component of vector is accessed (v.x or v[0] where v is a contant vector), then a contant node is
// returned, else an aggregate node is returned (for v.xy). The input to this function could either be the symbol
// node or it could be the intermediate tree representation of accessing fields in a constant structure or column of 
// a constant matrix.
//
TIntermTyped* TParseContext::addConstVectorNode(TVectorFields& fields, TIntermTyped* node, TSourceLoc line)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();

    constUnion *unionArray;
    if (tempConstantNode) {
        unionArray = tempConstantNode->getUnionArrayPointer();

        if (!unionArray) {  // this error message should never be raised
            infoSink.info.message(EPrefixInternalError, "constUnion not initialized in addConstVectorNode function", line);
            recover();

            return node;
        }
    } else { // The node has to be either a symbol node or an aggregate node or a tempConstant node, else, its an error
        error(line, "Cannot offset into the vector", "Error", "");
        recover();

        return 0;
    }

    constUnion* constArray = new constUnion[fields.num];

    for (int i = 0; i < fields.num; i++) {
        if (fields.offsets[i] >= node->getType().getObjectSize()) {
            error(line, "", "[", "vector index out of range '%d'", fields.offsets[i]);
            recover();
            fields.offsets[i] = 0;
        }
        
        constArray[i] = unionArray[fields.offsets[i]];

    } 
    typedNode = intermediate.addConstantUnion(constArray, node->getType(), line);
    return typedNode;
}

//
// This function returns the column being accessed from a constant matrix. The values are retrieved from
// the symbol table and parse-tree is built for a vector (each column of a matrix is a vector). The input 
// to the function could either be a symbol node (m[0] where m is a constant matrix)that represents a 
// constant matrix or it could be the tree representation of the constant matrix (s.m1[0] where s is a constant structure)
//
TIntermTyped* TParseContext::addConstMatrixNode(int index, TIntermTyped* node, TSourceLoc line)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();

    if (index >= node->getType().getMatrixCols()) {
        error(line, "", "[", "matrix field selection out of range '%d'", index);
        recover();
        index = 0;
    }

    if (tempConstantNode) {
         constUnion* unionArray = tempConstantNode->getUnionArrayPointer();
         int size = tempConstantNode->getType().getMatrixRows();
         // Note: the type is corrected (dereferenced) by the caller
         typedNode = intermediate.addConstantUnion(&unionArray[size*index], tempConstantNode->getType(), line);
    } else {
        error(line, "Cannot offset into the matrix", "Error", "");
        recover();

        return 0;
    }

    return typedNode;
}


//
// This function returns an element of an array accessed from a constant array. The values are retrieved from
// the symbol table and parse-tree is built for the type of the element. The input 
// to the function could either be a symbol node (a[0] where a is a constant array)that represents a 
// constant array or it could be the tree representation of the constant array (s.a1[0] where s is a constant structure)
//
TIntermTyped* TParseContext::addConstArrayNode(int index, TIntermTyped* node, TSourceLoc line)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();
    int arraySize = node->getType().getArraySize();
    TType arrayElementType(node->getType());
    arrayElementType.dereference();

    if (index >= node->getType().getArraySize() || index < 0) {
        error(line, "", "[", "array index '%d' out of range", index);
        recover();
        index = 0;
    }

    int arrayElementSize = arrayElementType.getObjectSize();

    if (tempConstantNode) {
         constUnion* unionArray = tempConstantNode->getUnionArrayPointer();
         typedNode = intermediate.addConstantUnion(&unionArray[arrayElementSize * index], tempConstantNode->getType(), line);
    } else {
        error(line, "Cannot offset into the array", "Error", "");
        recover();

        return 0;
    }

    return typedNode;
}


//
// This function returns the value of a particular field inside a constant structure from the symbol table. 
// If there is an embedded/nested struct, it appropriately calls addConstStructNested or addConstStructFromAggr
// function and returns the parse-tree with the values of the embedded/nested struct.
//
TIntermTyped* TParseContext::addConstStruct(TString& identifier, TIntermTyped* node, TSourceLoc line)
{
    TTypeList* fields = node->getType().getStruct();
    TIntermTyped *typedNode;
    int instanceSize = 0;
    unsigned int index = 0;
    TIntermConstantUnion *tempConstantNode = node->getAsConstantUnion();

    for ( index = 0; index < fields->size(); ++index) {
        if ((*fields)[index].type->getFieldName() == identifier) {
            break;
        } else {
            instanceSize += (*fields)[index].type->getObjectSize();
        }
    }

    if (tempConstantNode) {
         constUnion* constArray = tempConstantNode->getUnionArrayPointer();

         typedNode = intermediate.addConstantUnion(constArray+instanceSize, tempConstantNode->getType(), line); // type will be changed in the calling function
    } else {
        error(line, "Cannot offset into the structure", "Error", "");
        recover();

        return 0;
    }

    return typedNode;
}

//
// Initialize all supported extensions to disable
//
void TParseContext::initializeExtensionBehavior()
{
    //
    // example code: extensionBehavior["test"] = EBhDisable; // where "test" is the name of 
    // supported extension
    //
    extensionBehavior["GL_ARB_texture_rectangle"] = EBhDisable;
    extensionBehavior["GL_3DL_array_objects"] = EBhDisable;
}

OS_TLSIndex GlobalParseContextIndex = OS_INVALID_TLS_INDEX;

bool InitializeParseContextIndex()
{
    if (GlobalParseContextIndex != OS_INVALID_TLS_INDEX) {
        assert(0 && "InitializeParseContextIndex(): Parse Context already initialised");
        return false;
    }

    //
    // Allocate a TLS index.
    //
    GlobalParseContextIndex = OS_AllocTLSIndex();
    
    if (GlobalParseContextIndex == OS_INVALID_TLS_INDEX) {
        assert(0 && "InitializeParseContextIndex(): Parse Context already initialised");
        return false;
    }

    return true;
}

bool InitializeGlobalParseContext()
{
    if (GlobalParseContextIndex == OS_INVALID_TLS_INDEX) {
        assert(0 && "InitializeGlobalParseContext(): Parse Context index not initialized");
        return false;
    }

    TThreadParseContext *lpParseContext = static_cast<TThreadParseContext *>(OS_GetTLSValue(GlobalParseContextIndex));
    if (lpParseContext != 0) {
        assert(0 && "InitializeParseContextIndex(): Parse Context already initialized");
        return false;
    }

    TThreadParseContext *lpThreadData = new TThreadParseContext();
    if (lpThreadData == 0) {
        assert(0 && "InitializeGlobalParseContext(): Unable to create thread parse context");
        return false;
    }

    lpThreadData->lpGlobalParseContext = 0;
    OS_SetTLSValue(GlobalParseContextIndex, lpThreadData);

    return true;
}

TParseContextPointer& GetGlobalParseContext()
{
    //
    // Minimal error checking for speed
    //

    TThreadParseContext *lpParseContext = static_cast<TThreadParseContext *>(OS_GetTLSValue(GlobalParseContextIndex));

    return lpParseContext->lpGlobalParseContext;
}

bool FreeParseContext()
{
    if (GlobalParseContextIndex == OS_INVALID_TLS_INDEX) {
        assert(0 && "FreeParseContext(): Parse Context index not initialized");
        return false;
    }

    TThreadParseContext *lpParseContext = static_cast<TThreadParseContext *>(OS_GetTLSValue(GlobalParseContextIndex));
    if (lpParseContext)
        delete lpParseContext;

    return true;
}

bool FreeParseContextIndex()
{
    OS_TLSIndex tlsiIndex = GlobalParseContextIndex;

    if (GlobalParseContextIndex == OS_INVALID_TLS_INDEX) {
        assert(0 && "FreeParseContextIndex(): Parse Context index not initialized");
        return false;
    }

    GlobalParseContextIndex = OS_INVALID_TLS_INDEX;

    return OS_FreeTLSIndex(tlsiIndex);
}
