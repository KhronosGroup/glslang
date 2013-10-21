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
#ifndef _PARSER_HELPER_INCLUDED_
#define _PARSER_HELPER_INCLUDED_

#include "Versions.h"
#include "../Include/ShHandle.h"
#include "SymbolTable.h"
#include "localintermediate.h"

namespace glslang {

struct TPragma {
	TPragma(bool o, bool d) : optimize(o), debug(d) { }
	bool optimize;
	bool debug;
	TPragmaTable pragmaTable;
};

class TScanContext;
class TPpContext;

typedef std::set<int> TIdSetType;

//
// The following are extra variables needed during parsing, grouped together so
// they can be passed to the parser without needing a global.
//
class TParseContext {
public:
    TParseContext(TSymbolTable&, TIntermediate&, bool parsingBuiltins, int version, EProfile, EShLanguage, TInfoSink&,
                  bool forwardCompatible = false, EShMessages messages = EShMsgDefault);

public:
    bool parseShaderStrings(TPpContext&, char* strings[], size_t strLen[], int numStrings);
    void parserError(const char *s);     // for bison's yyerror

    void C_DECL error(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    void C_DECL  warn(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    bool reservedErrorCheck(TSourceLoc, const TString& identifier);

    void updateExtensionBehavior(const char* extName, const char* behavior);
    void handlePragma(const char **tokens, int numTokens);
    TIntermTyped* handleVariable(TSourceLoc, TSymbol* symbol, TString* string);
    TIntermTyped* handleBracketDereference(TSourceLoc, TIntermTyped* base, TIntermTyped* index);
    TIntermTyped* handleDotDereference(TSourceLoc, TIntermTyped* base, TString& field);
    TFunction* handleFunctionDeclarator(TSourceLoc loc, TFunction& function);
    TIntermAggregate* handleFunctionPrototype(TSourceLoc, TFunction&);
    TIntermTyped* handleFunctionCall(TSourceLoc, TFunction*, TIntermNode*, TIntermAggregate*);
    void nonOpBuiltInCheck(TSourceLoc, const TFunction&, TIntermAggregate*);
    TFunction* handleConstructorCall(TSourceLoc, TPublicType&);

    bool parseVectorFields(TSourceLoc, const TString&, int vecSize, TVectorFields&);
    void assignError(TSourceLoc, const char* op, TString left, TString right);
    void unaryOpError(TSourceLoc, const char* op, TString operand);
    void binaryOpError(TSourceLoc, const char* op, TString left, TString right);
    void variableCheck(TIntermTyped*& nodePtr);
    bool lValueErrorCheck(TSourceLoc, const char* op, TIntermTyped*);
    void constantValueCheck(TIntermTyped* node, const char* token);
    void integerCheck(TIntermTyped* node, const char* token);
    void globalCheck(TSourceLoc, const char* token);
    bool constructorError(TSourceLoc, TIntermNode*, TFunction&, TOperator, TType&);
    void arraySizeCheck(TSourceLoc, TIntermTyped* expr, int& size);
    bool arrayQualifierError(TSourceLoc, const TQualifier&);
    void arraySizeRequiredCheck(TSourceLoc, int size);
    void arrayDimError(TSourceLoc);
    void arrayDimCheck(TSourceLoc, TArraySizes* sizes1, TArraySizes* sizes2);
    void arrayDimCheck(TSourceLoc, const TType*, TArraySizes*);
    bool voidErrorCheck(TSourceLoc, const TString&, TBasicType);
    void boolCheck(TSourceLoc, const TIntermTyped*);
    void boolCheck(TSourceLoc, const TPublicType&);
    bool samplerErrorCheck(TSourceLoc, const TPublicType& pType, const char* reason);
    void pipeInOutFix(TSourceLoc, TQualifier&);
    void globalQualifierCheck(TSourceLoc, const TQualifier&, const TPublicType&);
    bool structQualifierErrorCheck(TSourceLoc, const TPublicType& pType);
    void mergeQualifiers(TSourceLoc, TQualifier& dst, const TQualifier& src, bool force);
    void setDefaultPrecision(TSourceLoc, TPublicType&, TPrecisionQualifier);
    int computeSamplerTypeIndex(TSampler&);
    TPrecisionQualifier getDefaultPrecision(TPublicType&);
    void precisionQualifierCheck(TSourceLoc, TPublicType&);
    void parameterSamplerCheck(TSourceLoc, TStorageQualifier qualifier, const TType& type);
    bool containsSampler(const TType& type);
    TSymbol* redeclareBuiltin(TSourceLoc, const TString&, bool& newDeclaration);
    void paramCheck(TSourceLoc, const TStorageQualifier&, TType* type);
    void nestedBlockCheck(TSourceLoc);
    void nestedStructCheck(TSourceLoc);
    void arrayObjectCheck(TSourceLoc, const TType&, const char* op);
    void inductiveLoopCheck(TSourceLoc, TIntermNode* init, TIntermLoop* loop);
    void inductiveLoopBodyCheck(TIntermNode*, int loopIndexId, TSymbolTable&);
    void constantIndexExpressionCheck(TIntermNode*);

    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&);
    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&, int);
    void mergeLayoutQualifiers(TSourceLoc, TQualifier& dest, const TQualifier& src);
    void layoutCheck(TSourceLoc, const TSymbol&);

    const TFunction* findFunction(TSourceLoc, TFunction* pfnCall, bool *builtIn = 0);
    TIntermNode* declareVariable(TSourceLoc, TString& identifier, TPublicType&, TArraySizes* typeArray = 0, TIntermTyped* initializer = 0);
    TIntermTyped* addConstructor(TSourceLoc, TIntermNode*, const TType&, TOperator);
    TIntermTyped* constructStruct(TIntermNode*, const TType&, int, TSourceLoc);
    TIntermTyped* constructBuiltIn(const TType&, TOperator, TIntermNode*, TSourceLoc, bool subset);
    void addBlock(TSourceLoc, TTypeList& typeList, const TString* instanceName = 0, TArraySizes* arraySizes = 0);
    void addQualifierToExisting(TSourceLoc, TQualifier, const TString& identifier);
    void addQualifierToExisting(TSourceLoc, TQualifier, TIdentifierList&);
    void updateQualifierDefaults(TQualifier);
    void updateQualifierDefaults(TSourceLoc, TQualifier);
    void updateTypedDefaults(TSourceLoc, TQualifier, const TString* id);
    void wrapupSwitchSubsequence(TIntermAggregate* statements, TIntermNode* branchNode);
    TIntermNode* addSwitch(TSourceLoc, TIntermTyped* expression, TIntermAggregate* body);
    TIntermTyped* addConstVectorNode(TVectorFields&, TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstMatrixNode(int , TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstArrayNode(int index, TIntermTyped* node, TSourceLoc);
    TIntermTyped* addConstStruct(TString& , TIntermTyped*, TSourceLoc);

    void updateMaxArraySize(TSourceLoc, TIntermNode*, int index);

    void setScanContext(TScanContext* c) { scanContext = c; }
    TScanContext* getScanContext() const { return scanContext; }
    void setPpContext(TPpContext* c) { ppContext = c; }
    TPpContext* getPpContext() const { return ppContext; }
    void addError() { ++numErrors; }
    int getNumErrors() const { return numErrors; }

    // The following are implemented in Versions.cpp to localize version/profile/stage/extensions control
    void initializeExtensionBehavior();
    void requireProfile(TSourceLoc, int queryProfiles, const char *featureDesc);
    void profileRequires(TSourceLoc, int queryProfiles, int minVersion, int numExtensions, const char* extensions[], const char *featureDesc);
    void profileRequires(TSourceLoc, int queryProfiles, int minVersion, const char* extension, const char *featureDesc);
    void requireStage(TSourceLoc, EShLanguageMask, const char *featureDesc);
    void requireStage(TSourceLoc, EShLanguage, const char *featureDesc);
    void checkDeprecated(TSourceLoc, int queryProfiles, int depVersion, const char *featureDesc);
    void requireNotRemoved(TSourceLoc, int queryProfiles, int removedVersion, const char *featureDesc);
    void fullIntegerCheck(TSourceLoc, const char* op);
    void doubleCheck(TSourceLoc, const char* op);

protected:
    const char* getPreamble();
    void nonInitConstCheck(TSourceLoc, TString& identifier, TType& type);
    TVariable* declareNonArray(TSourceLoc, TString& identifier, TType&, bool& newDeclaration);
    void declareArray(TSourceLoc, TString& identifier, const TType&, TSymbol*&, bool& newDeclaration);
    TIntermNode* executeInitializer(TSourceLoc, TString& identifier, TIntermTyped* initializer, TVariable* variable);
    TIntermTyped* convertInitializerList(TSourceLoc, const TType&, TIntermTyped* initializer);
    TOperator mapTypeToConstructorOp(const TType&);
    void finalize();

public:
    //
    // Generally, bison productions, the scanner, and the PP need read/write access to these; just give them direct access
    //

    TIntermediate& intermediate; // helper for making and hooking up pieces of the parse tree
    TSymbolTable& symbolTable;   // symbol table that goes with the current language, version, and profile
    TInfoSink& infoSink;

    // compilation mode
    EShLanguage language;        // vertex or fragment language
    int version;                 // version, updated by #version in the shader
    EProfile profile;            // the declared profile in the shader (core by default)
    bool forwardCompatible;      // true if errors are to be given for use of deprecated features
    EShMessages messages;        // errors/warnings

    // Current state of parsing
    struct TPragma contextPragma;
    int loopNestingLevel;        // 0 if outside all loops
    int structNestingLevel;      // 0 if outside blocks and structures
    TList<TIntermSequence*> switchSequenceStack;  // case, node, case, case, node, ...; ensure only one node between cases;   stack of them for nesting
    const TType* currentFunctionType;  // the return type of the function that's currently being parsed
    bool functionReturnsValue;   // true if a non-void function has a return
    const TString* blockName;
    TQualifier currentBlockDefaults;
    TIntermAggregate *linkage;   // aggregate node of objects the linker may need, if not referenced by the rest of the AST
    TPrecisionQualifier defaultPrecision[EbtNumTypes];
    TSourceLoc currentLoc;
    bool tokensBeforeEOF;
    TLimits limits;

protected:
    TScanContext* scanContext;
    TPpContext* ppContext;
    int numErrors;               // number of compile-time errors encountered
    bool parsingBuiltins;        // true if parsing built-in symbols/functions
    TMap<TString, TExtensionBehavior> extensionBehavior;    // for each extension string, what it's current behavior is set to
    static const int maxSamplerIndex = EsdNumDims * (EbtNumTypes * (2 * 2)); // see computeSamplerTypeIndex()
    TPrecisionQualifier defaultSamplerPrecision[maxSamplerIndex];
    bool afterEOF;
    TQualifier globalBufferDefaults;
    TQualifier globalUniformDefaults;
    TQualifier globalInputDefaults;
    TQualifier globalOutputDefaults;
    TString currentCaller;
    TIdSetType inductiveLoopIds;
    bool anyIndexLimits;
    TVector<TIntermTyped*> needsIndexLimitationChecking;
    // TODO: desktop functionality: track use of gl_FragDepth before redeclaration
};

} // end namespace glslang

#endif // _PARSER_HELPER_INCLUDED_
