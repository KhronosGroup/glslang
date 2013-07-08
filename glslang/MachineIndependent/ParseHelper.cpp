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
#include "osinclude.h"
#include <stdarg.h>
#include <algorithm>

#include "preprocessor/PpContext.h"

TParseContext::TParseContext(TSymbolTable& symt, TIntermediate& interm, bool pb, int v, EProfile p, EShLanguage L, TInfoSink& is,                             
                             bool fc, EShMessages m) : 
            intermediate(interm), symbolTable(symt), infoSink(is), language(L), treeRoot(0), linkage(0),
            numErrors(0), loopNestingLevel(0),
            structNestingLevel(0), inTypeParen(false), parsingBuiltins(pb),
            version(v), profile(p), forwardCompatible(fc), messages(m),
            contextPragma(true, false), afterEOF(false), tokensBeforeEOF(false)
{
    currentLoc.line = 1;
    currentLoc.string = 0;

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

        switch (language) {
        case EShLangVertex:
            defaultPrecision[EbtInt] = EpqHigh;
            defaultPrecision[EbtUint] = EpqHigh;
            defaultPrecision[EbtFloat] = EpqHigh;
            defaultPrecision[EbtSampler] = EpqLow;
            break;
        case EShLangFragment:
            defaultPrecision[EbtInt] = EpqMedium;
            defaultPrecision[EbtUint] = EpqMedium;
            defaultPrecision[EbtSampler] = EpqLow;
            break;
        default:
            infoSink.info.message(EPrefixError, "unexpected language");
        }
    }

    globalUniformDefaults.clear();
    globalUniformDefaults.layoutMatrix = ElmColumnMajor;
    globalUniformDefaults.layoutPacking = ElpShared;

    globalInputDefaults.clear();
    
    globalOutputDefaults.clear();
}

// Get code that is not part of a shared symbol table, is specific to this shader,
// or needed by CPP (which does not use a shared symbol table).
const char* TParseContext::getPreamble()
{
    if (profile == EEsProfile)
        return "#define GL_ES 1\n";
    else
        return 0;
}

extern int yyparse(void*);

//
// Parse an array of strings using yyparse, going through the
// preprocessor to tokenize the shader strings, then through
// the GLSL scanner.
//
// Returns true for successful acceptance of the shader, false if any errors.
//
bool TParseContext::parseShaderStrings(TPpContext& ppContext, char* strings[], int lengths[], int numStrings)
{
    // empty shaders are okay
    if (! strings || numStrings == 0 || lengths[0] == 0)
        return true;

    for (int i = 0; i < numStrings; ++i) {
        if (! strings[i]) {
            TSourceLoc loc;
            loc.string = i;
            loc.line = 1;
            error(loc, "Null shader source string", "", "");

            return false;
        }
    }

    if (getPreamble())
        ppContext.setPreamble(getPreamble(), strlen(getPreamble()));
    ppContext.setShaderStrings(strings, lengths, numStrings);

    // TODO: desktop PP: a shader containing nothing but white space and comments is valid, even though it has no parse tokens
    int len = 0;
    while (strings[0][len] == ' '  ||
           strings[0][len] == '\t' ||
           strings[0][len] == '\n' ||
           strings[0][len] == '\r') {
        if (++len >= lengths[0])
            return true;
    }

    yyparse((void*)this);

    return numErrors == 0;
}

// This is called from bison when it has a parse (syntax) error
void TParseContext::parserError(const char *s)
{
    if (afterEOF) {
        if (tokensBeforeEOF == 1)
            error(currentLoc, "", "pre-mature EOF", s, "");
    } else
        error(currentLoc, "", "", s, "");
}

void TParseContext::handlePragma(const char **tokens, int numTokens)
{
    if (!strcmp(tokens[0], "optimize")) {
        if (numTokens != 4) {
            error(currentLoc, "optimize pragma syntax is incorrect", "#pragma", "");
            return;
        }

        if (strcmp(tokens[1], "(")) {
            error(currentLoc, "\"(\" expected after 'optimize' keyword", "#pragma", "");
            return;
        }

        if (!strcmp(tokens[2], "on"))
            contextPragma.optimize = true;
        else if (!strcmp(tokens[2], "off"))
            contextPragma.optimize = false;
        else {
            error(currentLoc, "\"on\" or \"off\" expected after '(' for 'optimize' pragma", "#pragma", "");
            return;
        }

        if (strcmp(tokens[3], ")")) {
            error(currentLoc, "\")\" expected to end 'optimize' pragma", "#pragma", "");
            return;
        }
    } else if (!strcmp(tokens[0], "debug")) {
        if (numTokens != 4) {
            error(currentLoc, "debug pragma syntax is incorrect", "#pragma", "");
            return;
        }

        if (strcmp(tokens[1], "(")) {
            error(currentLoc, "\"(\" expected after 'debug' keyword", "#pragma", "");
            return;
        }

        if (!strcmp(tokens[2], "on"))
            contextPragma.debug = true;
        else if (!strcmp(tokens[2], "off"))
            contextPragma.debug = false;
        else {
            error(currentLoc, "\"on\" or \"off\" expected after '(' for 'debug' pragma", "#pragma", "");
            return;
        }

        if (strcmp(tokens[3], ")")) {
            error(currentLoc, "\")\" expected to end 'debug' pragma", "#pragma", "");
            return;
        }
    } else {

#ifdef PRAGMA_TABLE
        //
        // implementation specific pragma
        // use parseContext.contextPragma.pragmaTable to store the information about pragma
        // For now, just ignore the pragma that the implementation cannot recognize
        // An Example of one such implementation for a pragma that has a syntax like
        // #pragma pragmaname(pragmavalue)
        // This implementation stores the current pragmavalue against the pragma name in pragmaTable.
        //
        if (numTokens == 4 && !strcmp(tokens[1], "(") && !strcmp(tokens[3], ")")) {
            TPragmaTable& pragmaTable = parseContext.contextPragma.pragmaTable;
            TPragmaTable::iterator iter;
            iter = pragmaTable.find(TString(tokens[0]));
            if (iter != pragmaTable.end()) {
                iter->second = tokens[2];
            } else {
                pragmaTable[tokens[0]] = tokens[2];
            }
        } else if (numTokens >= 2) {
            TPragmaTable& pragmaTable = parseContext.contextPragma.pragmaTable;
            TPragmaTable::iterator iter;
            iter = pragmaTable.find(TString(tokens[0]));
            if (iter != pragmaTable.end()) {
                iter->second = tokens[1];
            } else {
                pragmaTable[tokens[0]] = tokens[1];
            }
        }
#endif // PRAGMA_TABLE
    }
}

TBehavior TParseContext::getExtensionBehavior(const char* behavior)
{
    if (!strcmp("require", behavior))
        return EBhRequire;
    else if (!strcmp("enable", behavior))
        return EBhEnable;
    else if (!strcmp("disable", behavior))
        return EBhDisable;
    else if (!strcmp("warn", behavior))
        return EBhWarn;
    else {
        error(currentLoc, "behavior not supported", "#extension", behavior);
        return EBhDisable;
    }
}

void TParseContext::updateExtensionBehavior(const char* extName, const char* behavior)
{
    TBehavior behaviorVal = getExtensionBehavior(behavior);
    TMap<TString, TBehavior>:: iterator iter;
    TString msg;

    // special cased for all extension
    if (!strcmp(extName, "all")) {
        if (behaviorVal == EBhRequire || behaviorVal == EBhEnable) {
            error(currentLoc, "extension 'all' cannot have 'require' or 'enable' behavior", "#extension", "");
            return;
        } else {
            for (iter = extensionBehavior.begin(); iter != extensionBehavior.end(); ++iter)
                iter->second = behaviorVal;
        }
    } else {
        iter = extensionBehavior.find(TString(extName));
        if (iter == extensionBehavior.end()) {
            switch (behaviorVal) {
            case EBhRequire:
                error(currentLoc, "extension not supported", "#extension", extName);
                break;
            case EBhEnable:
            case EBhWarn:
            case EBhDisable:
                warn(currentLoc, "extension not supported", "#extension", extName);
                break;
            default:
                assert(0 && "unexpected behaviorVal");
            }

            return;
        } else
            iter->second = behaviorVal;
    }
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
void C_DECL TParseContext::error(TSourceLoc loc, const char *szReason, const char *szToken, 
                                 const char *szExtraInfoFormat, ...)
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

void C_DECL TParseContext::warn(TSourceLoc loc, const char *szReason, const char *szToken, 
                                 const char *szExtraInfoFormat, ...)
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

TIntermTyped* TParseContext::handleVariable(TSourceLoc loc, TSymbol* symbol, TString* string)
{
    TIntermTyped* node = 0;

    TAnonMember* anon = symbol ? symbol->getAsAnonMember() : 0;
    if (anon) {
        // it was a member of an anonymous container, have to insert its dereference
        TVariable* variable = anon->getAnonContainer().getAsVariable();
        TIntermTyped* container = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), loc);
        constUnion* unionArray = new constUnion[1];
        unionArray->setUConst(anon->getMemberNumber());
        TIntermTyped* constNode = intermediate.addConstantUnion(unionArray, TType(EbtUint, EvqConst), loc);

        node = intermediate.addIndex(EOpIndexDirectStruct, container, constNode, loc);
        node->setType(*(*variable->getType().getStruct())[anon->getMemberNumber()].type);
    } else {
        // The symbol table search was done in the lexical phase, but
        // if this is a new symbol, it wouldn't have found it.
        const TVariable* variable = symbol ? symbol->getAsVariable() : 0;
        if (symbol && ! variable)
            error(loc, "variable name expected", string->c_str(), "");

        if (! variable)
            variable = new TVariable(string, TType(EbtVoid));

        // don't delete $1.string, it's used by error recovery, and the pool
        // pop will reclaim the memory

        if (variable->getType().getQualifier().storage == EvqConst ) {
            constUnion* constArray = variable->getConstUnionPointer();
            TType t(variable->getType());
            node = intermediate.addConstantUnion(constArray, t, loc);
        } else
            node = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), loc);
    }

    return node;
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
                    int value = (*p)->getAsTyped()->getAsConstantUnion()->getUnionArrayPointer()->getIConst();
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
void TParseContext::constCheck(TIntermTyped* node, const char* token)
{
    if (node->getQualifier().storage != EvqConst)
        error(node->getLoc(), "constant expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// an integer.
//
void TParseContext::integerCheck(TIntermTyped* node, const char* token)
{
    if ((node->getBasicType() == EbtInt || node->getBasicType() == EbtUint) && node->isScalar() && ! node->isArray())
        return;

    error(node->getLoc(), "scalar integer expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if we are currently
// globally scoped.
//
void TParseContext::globalCheck(TSourceLoc loc, bool global, const char* token)
{
    if (! global)
        error(loc, "only allowed at global scope", token, "");
}

//
// For now, keep it simple:  if it starts "gl_", it's reserved, independent
// of scope.  Except, if the symbol table is at the built-in push-level,
// which is when we are parsing built-ins.
//
bool TParseContext::reservedErrorCheck(TSourceLoc loc, const TString& identifier)
{
    if (!symbolTable.atBuiltInLevel()) {
        if (identifier.substr(0, 3) == TString("gl_")) {
            error(loc, "reserved built-in name", "gl_", "");

            return true;
        }
        if (identifier.find("__") != TString::npos) {
            error(loc, "Two consecutive underscores are reserved for future use.", identifier.c_str(), "", "");

            return true;
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
bool TParseContext::constructorError(TSourceLoc loc, TIntermNode* node, TFunction& function, TOperator op, TType& type)
{
    type = function.getReturnType();

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
        if (op != EOpConstructStruct && ! type.isArray() && size >= type.getObjectSize())
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

    if ((op != EOpConstructStruct && size != 1 && size < type.getObjectSize()) ||
        (op == EOpConstructStruct && size < type.getObjectSize())) {
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

// This function checks to see if a void variable has been declared and raise an error message for such a case
//
// returns true in case of an error
//
bool TParseContext::voidErrorCheck(TSourceLoc loc, const TString& identifier, const TPublicType& pubType)
{
    if (pubType.basicType == EbtVoid) {
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

bool TParseContext::samplerErrorCheck(TSourceLoc loc, const TPublicType& pType, const char* reason)
{
    if (pType.basicType == EbtStruct) {
        if (containsSampler(*pType.userDef)) {
            error(loc, reason, TType::getBasicString(pType.basicType), "(structure cannot contain a sampler or image)");
        
            return true;
        }
        
        return false;
    } else if (pType.basicType == EbtSampler) {
        error(loc, reason, TType::getBasicString(pType.basicType), "");

        return true;
    }

    return false;
}

void TParseContext::globalQualifierFix(TSourceLoc loc, TQualifier& qualifier, const TPublicType& publicType)
{
    if (! symbolTable.atGlobalLevel())
        return;

    // First, move from parameter qualifiers to shader in/out qualifiers

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
    case EvqVaryingIn:
    case EvqVaryingOut:
        break;
    case EvqInOut:
        qualifier.storage = EvqVaryingIn;
        error(loc, "cannot use 'inout' at global scope", "", "");

        return;
    default:
        break;
    }

    // Do non-in/out error checks

    if (qualifier.storage != EvqUniform && samplerErrorCheck(loc, publicType, "samplers and images must be uniform"))
        return;

    if (qualifier.storage != EvqVaryingIn && qualifier.storage != EvqVaryingOut)
        return;

    // now, knowing it is a shader in/out, do all the in/out semantic checks

    if (publicType.basicType == EbtBool) {
        error(loc, "cannot be bool",  getStorageQualifierString(qualifier.storage), "");

        return;
    }

    if (language == EShLangVertex && qualifier.storage == EvqVaryingIn) {
        if (publicType.basicType == EbtStruct) {
            error(loc, "cannot be a structure or array",  getStorageQualifierString(qualifier.storage), "");

            return;
        }
        if (publicType.arraySizes) {
            requireProfile(loc, (EProfileMask)~EEsProfileMask, "vertex input arrays");
            profileRequires(loc, ENoProfile, 150, 0, "vertex input arrays");
        }
    }

    if (language == EShLangFragment && qualifier.storage == EvqVaryingOut) {
        profileRequires(loc, EEsProfile, 300, 0, "fragment shader output");
        if (publicType.basicType == EbtStruct) {
            error(loc, "cannot be a structure",  getStorageQualifierString(qualifier.storage), "");

            return;
        }
    }

    if (publicType.basicType == EbtInt || publicType.basicType == EbtUint || publicType.basicType == EbtDouble) {
        profileRequires(loc, EEsProfile, 300, 0, "shader input/output");
        if (language != EShLangVertex   && qualifier.storage == EvqVaryingIn  && ! qualifier.flat ||
            language != EShLangFragment && qualifier.storage == EvqVaryingOut && ! qualifier.flat) {
            error(loc, "must be qualified as 'flat'", getStorageQualifierString(qualifier.storage), TType::getBasicString(publicType.basicType));
         
            return;
        }
    }

    if (language == EShLangVertex && qualifier.storage == EvqVaryingIn && 
        (qualifier.isAuxiliary() || qualifier.isInterpolation() || qualifier.isMemory() || qualifier.invariant)) {
        error(loc, "vertex input cannot be further qualified", "", "");

        return;
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
    if (! force && version < 420) {
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
    else if (dst.storage == EvqIn  && src.storage == EvqOut ||
             dst.storage == EvqOut && src.storage == EvqIn)
        dst.storage = EvqInOut;
    else if (dst.storage == EvqIn    && src.storage == EvqConst ||
             dst.storage == EvqConst && src.storage == EvqIn)
        dst.storage = EvqConstReadOnly;
    else if (src.storage != EvqTemporary)
        error(loc, "too many storage qualifiers", getStorageQualifierString(src.storage), "");

    // Precision qualifiers
    if (! force && src.precision != EpqNone && dst.precision != EpqNone)
        error(loc, "only one precision qualifier allowed", getPrecisionQualifierString(src.precision), "");
    if (dst.precision == EpqNone || force && src.precision != EpqNone)
        dst.precision = src.precision;

    // Layout qualifiers
    mergeLayoutQualifiers(loc, dst, src);

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
    int arrayIndex = sampler.arrayed ? 1 : 0;
    int shadowIndex = sampler.shadow ? 1 : 0;

    return EsdNumDims * (EbtNumTypes * (2 * arrayIndex + shadowIndex) + sampler.type) + sampler.dim;
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
        error(loc, "samplers cannot be output parameters", type.getCompleteTypeString().c_str(), "");
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
        infoSink.info.message(EPrefixInternalError, "variable expected");
        return true;
    }

    TVariable* newVariable = new TVariable(name, variable->getType());

    if (! symbolTable.insert(*newVariable)) {
        delete newVariable;
        infoSink.info.message(EPrefixInternalError, "inserting new symbol");
        return true;
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

    size = constant->getUnionArrayPointer()->getIConst();

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
bool TParseContext::arrayQualifierError(TSourceLoc loc, const TPublicType& type)
{
    if (type.qualifier.storage == EvqConst)
        profileRequires(loc, ENoProfile, 120, "GL_3DL_array_objects", "const array");

    if (type.qualifier.storage == EvqVaryingIn && language == EShLangVertex) {
        requireProfile(loc, (EProfileMask)~EEsProfileMask, "vertex input arrays");
        profileRequires(loc, ENoProfile, 150, 0, "vertex input arrays");
    }

    return false;
}

//
// Require array to have size
//
void TParseContext::arraySizeRequiredCheck(TSourceLoc loc, int& size)
{
    if (size == 0) {
        error(loc, "array size required", "", "");
        size = 1;
    }
}

void TParseContext::arrayDimError(TSourceLoc loc)
{
    requireProfile(loc, (EProfileMask)(ECoreProfileMask | ECompatibilityProfileMask), "arrays of arrays");
    profileRequires(loc, ECoreProfile, 430, 0, "arrays of arrays");
    profileRequires(loc, ECompatibilityProfile, 430, 0, "arrays of arrays");
}

void TParseContext::arrayDimCheck(TSourceLoc loc, TArraySizes sizes1, TArraySizes sizes2)
{
    if (sizes1 && sizes2 ||
        sizes1 && sizes1->size() > 1 ||
        sizes2 && sizes2->size() > 1)
        arrayDimError(loc);
}

void TParseContext::arrayDimCheck(TSourceLoc loc, const TType* type, TArraySizes sizes2)
{
    if (type && type->isArray() && sizes2 ||
        sizes2 && sizes2->size() > 1)
        arrayDimError(loc);
}

//
// Do all the semantic checking for declaring an array, with and 
// without a size, and make the right changes to the symbol table.
//
// size == 0 means no specified size.
//
void TParseContext::arrayCheck(TSourceLoc loc, TString& identifier, const TPublicType& type, TVariable*& variable)
{
    //
    // Don't check for reserved word use until after we know it's not in the symbol table,
    // because reserved arrays can be redeclared.
    //

    bool sameScope = false;
    TSymbol* symbol = symbolTable.find(identifier, 0, &sameScope);
    if (symbol == 0 || !sameScope) {
        if (reservedErrorCheck(loc, identifier))
            return;
        
        variable = new TVariable(&identifier, TType(type));

        if (! symbolTable.insert(*variable)) {
            delete variable;
            error(loc, "INTERNAL ERROR inserting new symbol", identifier.c_str(), "");

            return;
        }
    } else {
        variable = symbol->getAsVariable();

        if (! variable) {
            error(loc, "array variable name expected", identifier.c_str(), "");
            return;
        }

        if (! variable->getType().isArray()) {
            error(loc, "redeclaring non-array as array", identifier.c_str(), "");
            return;
        }
        if (variable->getType().getArraySize() > 0) {
            error(loc, "redeclaration of array with size", identifier.c_str(), "");
            return;
        }
        
        if (! variable->getType().sameElementType(TType(type))) {
            error(loc, "redeclaration of array with a different type", identifier.c_str(), "");
            return;
        }

        TType* t = variable->getArrayInformationType();
        while (t != 0) {
            if (t->getMaxArraySize() > type.arraySizes->front()) {
                error(loc, "higher index value already used for the array", identifier.c_str(), "");
                return;
            }
            t->setArraySizes(type.arraySizes);
            t = t->getArrayInformationType();
        }

        variable->getType().setArraySizes(type.arraySizes);
    } 

    voidErrorCheck(loc, identifier, type);
}

bool TParseContext::arraySetMaxSize(TIntermSymbol *node, TType* type, int size, bool updateFlag, TSourceLoc loc)
{
    TSymbol* symbol = symbolTable.find(node->getName());
    if (symbol == 0) {
        error(loc, " undeclared identifier", node->getName().c_str(), "");
        return true;
    }

    TVariable* variable = symbol->getAsVariable();
    if (! variable) {
        error(loc, "array variable name expected", node->getName().c_str(), "");
        return true;
    }

    type->setArrayInformationType(variable->getArrayInformationType());
    variable->updateArrayInformationType(type);

    // special casing to test index value of gl_TexCoord. If the accessed index is >= gl_MaxTextureCoords
    // its an error
    if (node->getName() == "gl_TexCoord") {
        TSymbol* texCoord = symbolTable.find("gl_MaxTextureCoords");
        if (! texCoord || ! texCoord->getAsVariable()) {
            infoSink.info.message(EPrefixInternalError, "gl_MaxTextureCoords not defined", loc);
            return true;
        }

        int texCoordValue = texCoord->getAsVariable()->getConstUnionPointer()[0].getIConst();
        if (texCoordValue <= size) {
            error(loc, "", "[", "gl_TexCoord can only have a max array size of up to gl_MaxTextureCoords", "");
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
void TParseContext::nonInitConstCheck(TSourceLoc loc, TString& identifier, TPublicType& type)
{
    //
    // Make the qualifier make sense.
    //
    if (type.qualifier.storage  == EvqConst) {
        type.qualifier.storage = EvqTemporary;
        error(loc, "variables with qualifier 'const' must be initialized", identifier.c_str(), "");
    }
}

//
// Do semantic checking for a variable declaration that has no initializer,
// and update the symbol table.
//
void TParseContext::nonInitCheck(TSourceLoc loc, TString& identifier, TPublicType& type)
{
    reservedErrorCheck(loc, identifier);

    TVariable* variable = new TVariable(&identifier, TType(type));

    if (! symbolTable.insert(*variable))
        error(loc, "redefinition", variable->getName().c_str(), "");
    else {
        voidErrorCheck(loc, identifier, type);

        // see if it's a linker-level object to track
        if (type.qualifier.isUniform() || type.qualifier.isPipeInput() || type.qualifier.isPipeOutput())
            intermediate.addSymbolLinkageNode(linkage, *variable);
    }
}

void TParseContext::paramCheck(TSourceLoc loc, TStorageQualifier qualifier, TType* type)
{
    switch (qualifier) {
    case EvqConst:
    case EvqConstReadOnly:
        type->getQualifier().storage = EvqConstReadOnly;
        break;
    case EvqIn:
    case EvqOut:
    case EvqInOut:
        type->getQualifier().storage = qualifier;
        break;
    case EvqTemporary:
        type->getQualifier().storage = EvqIn;
        break;
    default:
        type->getQualifier().storage = EvqIn;
        error(loc, "qualifier not allowed on function parameter", getStorageQualifierString(qualifier), "");
        break;
    }
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

//
// Layout qualifier stuff.
//

// Put the id's layout qualification into the public type.
void TParseContext::setLayoutQualifier(TSourceLoc loc, TPublicType& publicType, TString& id)
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
        error(loc, "requires an integer assignment (e.g., location = 4)", "location", "");
    else if (id == "binding")
        error(loc, "requires an integer assignment (e.g., binding = 4)", "binding", "");
    else
        error(loc, "unrecognized layout identifier", id.c_str(), "");
}

// Put the id's layout qualifier value into the public type.
void TParseContext::setLayoutQualifier(TSourceLoc loc, TPublicType& publicType, TString& id, int value)
{
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    if (id == "location") {
        if ((unsigned int)value >= TQualifier::layoutLocationEnd)
            error(loc, "value is too large", id.c_str(), "");
        else
            publicType.qualifier.layoutSlotLocation = value;
    } else if (id == "binding")
        error(loc, "not supported", "binding", "");
    else
        error(loc, "there is no such layout identifier taking an assigned value", id.c_str(), "");

    // TODO: semantics: error check: make sure locations are non-overlapping across the whole stage
    // TODO: semantics: error check: if more than one fragment output, all must have a location
    // TODO: semantics: error check: output arrays can only be indexed with a constant (es 300)
}

// Merge any layout qualifier information from src into dst, leaving everything else in dst alone
void TParseContext::mergeLayoutQualifiers(TSourceLoc loc, TQualifier& dst, const TQualifier& src)
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
const TFunction* TParseContext::findFunction(TSourceLoc loc, TFunction* call, bool *builtIn)
{
    TSymbol* symbol = symbolTable.find(call->getMangledName(), builtIn);

    if (symbol == 0) {        
        error(loc, "no matching overloaded function found", call->getName().c_str(), "");

        return 0;
    }
    
    const TFunction* function = symbol->getAsFunction();
    if (! function) {
        error(loc, "function name expected", call->getName().c_str(), "");

        return 0;
    }
    
    return function;
}

//
// Initializers show up in several places in the grammar.  Have one set of
// code to handle them here.
//
bool TParseContext::executeInitializerError(TSourceLoc loc, TString& identifier, TPublicType& pType, 
                                            TIntermTyped* initializer, TIntermNode*& intermNode, TVariable* variable)
{
    TType type(pType);

    if (variable == 0) {
        if (reservedErrorCheck(loc, identifier))
            return true;

        if (voidErrorCheck(loc, identifier, pType))
            return true;

        //
        // add variable to symbol table
        //
        variable = new TVariable(&identifier, type);
        if (! symbolTable.insert(*variable)) {
            error(loc, "redefinition", variable->getName().c_str(), "");
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
        error(loc, " cannot initialize this type of qualifier ", variable->getType().getStorageQualifierString(), "");
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
            error(loc, " assigning non-constant to", "=", "'%s'", variable->getType().getCompleteString().c_str());
            variable->getType().getQualifier().storage = EvqTemporary;
            return true;
        }
        if (type != initializer->getType()) {
            error(loc, " non-matching types for const initializer ", 
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
            TSymbol* symbol = symbolTable.find(initializer->getAsSymbolNode()->getName());
            if (TVariable* tVar = symbol->getAsVariable()) {
                constUnion* constArray = tVar->getConstUnionPointer();
                variable->shareConstPointer(constArray);
            } else {
                error(loc, "expected variable", initializer->getAsSymbolNode()->getName().c_str(), "");
                return true;
            }
        } else {
            error(loc, " cannot assign to", "=", "'%s'", variable->getType().getCompleteString().c_str());
            variable->getType().getQualifier().storage = EvqTemporary;
            return true;
        }
    }
 
    if (qualifier != EvqConst) {
        TIntermSymbol* intermSymbol = intermediate.addSymbol(variable->getUniqueId(), variable->getName(), variable->getType(), loc);
        intermNode = intermediate.addAssign(EOpAssign, intermSymbol, initializer, loc);
        if (intermNode == 0) {
            assignError(loc, "=", intermSymbol->getCompleteString(), initializer->getCompleteString());
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
TIntermTyped* TParseContext::addConstructor(TIntermNode* node, const TType& type, TOperator op, TFunction* fnCall, TSourceLoc loc)
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
            newNode = constructStruct(*p, elementType, paramCount+1, node->getLoc());
        else if (op == EOpConstructStruct)
            newNode = constructStruct(*p, *(memberTypes[paramCount]).type, paramCount+1, node->getLoc());
        else
            newNode = constructBuiltIn(type, op, *p, node->getLoc(), true);
        
        if (newNode) {
            p = sequenceVector.erase(p); 
            p = sequenceVector.insert(p, newNode);
        }
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
    if (subset || newNode != node && newNode->getType() == type)
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
                node->getAsTyped()->getType().getCompleteTypeString().c_str(), type.getCompleteTypeString().c_str());
        
        return 0;
    }

    return converted;
}

//
// Do everything needed to add an interface block.
//
void TParseContext::addBlock(TSourceLoc loc, TTypeList& typeList, const TString* instanceName, TArraySizes arraySizes)
{
    // First, error checks

    if (reservedErrorCheck(loc, *blockName))
        return;

    if (instanceName && reservedErrorCheck(loc, *instanceName))
        return;

    if (profile == EEsProfile && arraySizes)
        arraySizeRequiredCheck(loc, arraySizes->front());        

    if (currentBlockDefaults.storage == EvqUniform) {
        requireProfile(loc, (EProfileMask)(~ENoProfileMask), "uniform block");
        profileRequires(loc, EEsProfile, 300, 0, "uniform block");
    } else {
        error(loc, "only uniform interface blocks are supported", blockName->c_str(), "");

        return;
    }

    arrayDimCheck(loc, arraySizes, 0);

    // check for qualifiers and types that don't belong within a block
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier memberQualifier = typeList[member].type->getQualifier();
        if (memberQualifier.storage != EvqTemporary && memberQualifier.storage != EvqGlobal && memberQualifier.storage != currentBlockDefaults.storage)
            error(loc, "member storage qualifier cannot contradict block storage qualifier", typeList[member].type->getFieldName().c_str(), "");
        if (currentBlockDefaults.storage == EvqUniform && memberQualifier.isInterpolation() || memberQualifier.isAuxiliary())
            error(loc, "member of uniform block cannot have an auxiliary or interpolation qualifier", typeList[member].type->getFieldName().c_str(), "");

        TBasicType basicType = typeList[member].type->getBasicType();
        if (basicType == EbtSampler)
            error(loc, "member of block cannot be a sampler type", typeList[member].type->getFieldName().c_str(), "");
    }

    // Make default block qualification, and adjust the member qualifications

    TQualifier defaultQualification;
    switch (currentBlockDefaults.storage) {
    case EvqUniform:  defaultQualification = globalUniformDefaults;    break;
    case EvqIn:       defaultQualification = globalInputDefaults;      break;
    case EvqOut:      defaultQualification = globalOutputDefaults;     break;
    default:          defaultQualification.clear();                    break;
    }

    mergeLayoutQualifiers(loc, defaultQualification, currentBlockDefaults);
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier memberQualification = defaultQualification;
        mergeQualifiers(loc, memberQualification, typeList[member].type->getQualifier(), false);
        typeList[member].type->getQualifier() = memberQualification;
    }

    // Build and add the interface block as a new type named blockName

    TType blockType(&typeList, *blockName, currentBlockDefaults.storage);
    if (arraySizes)
        blockType.setArraySizes(arraySizes);
    blockType.getQualifier().layoutPacking = defaultQualification.layoutPacking;
    TVariable* userTypeDef = new TVariable(blockName, blockType, true);
    if (! symbolTable.insert(*userTypeDef)) {
        error(loc, "redefinition", blockName->c_str(), "block name");

        return;
    }

    // Add the variable, as anonymous or named instanceName

    // make an anonymous variable if no name was provided
    if (! instanceName)
        instanceName = new TString("");

    TVariable* variable = new TVariable(instanceName, blockType);
    if (! symbolTable.insert(*variable)) {
        if (*instanceName == "")
            error(loc, "nameless block contains a member that already has a name at global scope", blockName->c_str(), "");
        else
            error(loc, "block instance name redefinition", variable->getName().c_str(), "");

        return;
    }

    // save it in case there are no references in the AST, so the linker can error test against it
    intermediate.addSymbolLinkageNode(linkage, *variable);
}

// For an identifier that is already declared, add more qualification to it.
void TParseContext::addQualifierToExisting(TSourceLoc loc, TQualifier qualifier, const TString& identifier)
{
    TSymbol* existing = symbolTable.find(identifier);
    TVariable* variable = existing ? existing->getAsVariable() : 0;
    if (! variable) {
        error(loc, "identifier not previously declared", identifier.c_str(), "");

        return;
    }

    if (qualifier.isAuxiliary() || 
        qualifier.isMemory() ||
        qualifier.isInterpolation() ||
        qualifier.storage != EvqTemporary ||
        qualifier.precision != EpqNone) {
        error(loc, "cannot add storage, auxiliary, memory, interpolation, or precision qualifier to an existing variable", identifier.c_str(), "");

        return;
    }

    if (qualifier.invariant)
        variable->getType().getQualifier().invariant = true;
}

void TParseContext::addQualifierToExisting(TSourceLoc loc, TQualifier qualifier, TIdentifierList& identifiers)
{
    for (unsigned int i = 0; i < identifiers.size(); ++i)
        addQualifierToExisting(loc, qualifier, *identifiers[i]);
}

void TParseContext::updateQualifierDefaults(TQualifier qualifier)
{
    switch (qualifier.storage) {
    case EvqUniform:
        if (qualifier.layoutMatrix != ElmNone)
            globalUniformDefaults.layoutMatrix = qualifier.layoutMatrix;
        if (qualifier.layoutPacking != ElpNone)
            globalUniformDefaults.layoutPacking = qualifier.layoutPacking;
        break;
    case EvqIn:
        if (qualifier.hasLocation())
            globalInputDefaults.layoutSlotLocation = qualifier.layoutSlotLocation;
        break;
    case EvqOut:
        if (qualifier.hasLocation())
            globalOutputDefaults.layoutSlotLocation = qualifier.layoutSlotLocation;
        break;
    default:
        // error handling should be done by callers of this function
        break;
    }
}

void TParseContext::updateQualifierDefaults(TSourceLoc loc, TQualifier qualifier)
{
    if (qualifier.isAuxiliary() || 
        qualifier.isMemory() ||
        qualifier.isInterpolation() ||
        qualifier.precision != EpqNone)
        error(loc, "cannot use auxiliary, memory, interpolation, or precision qualifier in a standalone qualifier", "", "");

    switch (qualifier.storage) {
    case EvqUniform:
    case EvqIn:
    case EvqOut:
        break;
    default:
        error(loc, "standalone qualifier requires 'uniform', 'in', or 'out' storage qualification", "", "");
        return;
    }

    updateQualifierDefaults(qualifier);
}

void TParseContext::updateTypedDefaults(TSourceLoc loc, TQualifier qualifier, const TString* id)
{
    bool cantHaveId = false;

    if (! id) {
        if (qualifier.hasLayout())
            warn(loc, "cannot set qualifier defaults when using a type and no identifier", "", "");
        
        return;
    }

    if (qualifier.storage == EvqUniform) {
        if (qualifier.layoutMatrix != ElmNone)
            error(loc, "cannot specify matrix layout on a variable declaration", id->c_str(), "");
        if (qualifier.layoutPacking != ElpNone)
            error(loc, "cannot specify packing on a variable declaration", id->c_str(), "");
    } else if (qualifier.storage == EvqVaryingIn) {
        if (qualifier.hasLayout() && language != EShLangVertex) {
            error(loc, "can only use location layout qualifier on a vertex input or fragment output", id->c_str(), "");
        }
    } else if (qualifier.storage == EvqVaryingOut) {
        if (qualifier.hasLayout() && language != EShLangFragment) {
            error(loc, "can only use location layout qualifier on a vertex input or fragment output", id->c_str(), "");
        }
    } else {
        if (qualifier.layoutMatrix != ElmNone ||
            qualifier.layoutPacking != ElpNone)
            error(loc, "layout qualifiers for matrix layout and packing only apply to uniform blocks", id->c_str(), "");
        else if (qualifier.hasLocation())
            error(loc, "location qualifiers only appy to uniform, in, or out storage qualifiers", id->c_str(), "");
    }

    if (cantHaveId)
        error(loc, "cannot set global layout qualifiers on uniform variable, use just 'uniform' or a block", id->c_str(), "");

    updateQualifierDefaults(qualifier);
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
                         prevExpression->getAsConstantUnion()->getUnionArrayPointer()->getIConst() == 
                          newExpression->getAsConstantUnion()->getUnionArrayPointer()->getIConst())
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
        expression->getBasicType() != EbtInt && expression->getBasicType() != EbtUint ||
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

//
// This function returns the tree representation for the vector field(s) being accessed from contant vector.
// If only one component of vector is accessed (v.x or v[0] where v is a contant vector), then a contant node is
// returned, else an aggregate node is returned (for v.xy). The input to this function could either be the symbol
// node or it could be the intermediate tree representation of accessing fields in a constant structure or column of 
// a constant matrix.
//
TIntermTyped* TParseContext::addConstVectorNode(TVectorFields& fields, TIntermTyped* node, TSourceLoc loc)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();

    constUnion *unionArray;
    if (tempConstantNode) {
        unionArray = tempConstantNode->getUnionArrayPointer();

        if (!unionArray) {  // this error message should never be raised
            infoSink.info.message(EPrefixInternalError, "constUnion not initialized in addConstVectorNode function", loc);

            return node;
        }
    } else { // The node has to be either a symbol node or an aggregate node or a tempConstant node, else, its an error
        error(loc, "Cannot offset into the vector", "Error", "");

        return 0;
    }

    constUnion* constArray = new constUnion[fields.num];

    for (int i = 0; i < fields.num; i++) {
        if (fields.offsets[i] >= node->getType().getObjectSize()) {
            error(loc, "", "[", "vector index out of range '%d'", fields.offsets[i]);
            fields.offsets[i] = 0;
        }
        
        constArray[i] = unionArray[fields.offsets[i]];
    } 
    typedNode = intermediate.addConstantUnion(constArray, node->getType(), loc);

    return typedNode;
}

//
// This function returns the column being accessed from a constant matrix. The values are retrieved from
// the symbol table and parse-tree is built for a vector (each column of a matrix is a vector). The input 
// to the function could either be a symbol node (m[0] where m is a constant matrix)that represents a 
// constant matrix or it could be the tree representation of the constant matrix (s.m1[0] where s is a constant structure)
//
TIntermTyped* TParseContext::addConstMatrixNode(int index, TIntermTyped* node, TSourceLoc loc)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();

    if (index >= node->getType().getMatrixCols()) {
        error(loc, "", "[", "matrix field selection out of range '%d'", index);
        index = 0;
    }

    if (tempConstantNode) {
         constUnion* unionArray = tempConstantNode->getUnionArrayPointer();
         int size = tempConstantNode->getType().getMatrixRows();
         // Note: the type is corrected (dereferenced) by the caller
         typedNode = intermediate.addConstantUnion(&unionArray[size*index], tempConstantNode->getType(), loc);
    } else {
        error(loc, "Cannot offset into the matrix", "Error", "");

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
TIntermTyped* TParseContext::addConstArrayNode(int index, TIntermTyped* node, TSourceLoc loc)
{
    TIntermTyped* typedNode;
    TIntermConstantUnion* tempConstantNode = node->getAsConstantUnion();
    int arraySize = node->getType().getArraySize();
    TType arrayElementType(node->getType());
    arrayElementType.dereference();

    if (index >= node->getType().getArraySize() || index < 0) {
        error(loc, "", "[", "array index '%d' out of range", index);
        index = 0;
    }

    int arrayElementSize = arrayElementType.getObjectSize();

    if (tempConstantNode) {
         constUnion* unionArray = tempConstantNode->getUnionArrayPointer();
         typedNode = intermediate.addConstantUnion(&unionArray[arrayElementSize * index], tempConstantNode->getType(), loc);
    } else {
        error(loc, "Cannot offset into the array", "Error", "");

        return 0;
    }

    return typedNode;
}


//
// This function returns the value of a particular field inside a constant structure from the symbol table. 
// If there is an embedded/nested struct, it appropriately calls addConstStructNested or addConstStructFromAggr
// function and returns the parse-tree with the values of the embedded/nested struct.
//
TIntermTyped* TParseContext::addConstStruct(TString& identifier, TIntermTyped* node, TSourceLoc loc)
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

         typedNode = intermediate.addConstantUnion(constArray+instanceSize, tempConstantNode->getType(), loc); // type will be changed in the calling function
    } else {
        error(loc, "Cannot offset into the structure", "Error", "");

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
