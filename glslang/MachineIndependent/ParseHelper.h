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

typedef enum {
    EBhRequire,
    EBhEnable,
    EBhWarn,
    EBhDisable
} TBehavior;

struct TPragma {
	TPragma(bool o, bool d) : optimize(o), debug(d) { }
	bool optimize;
	bool debug;
	TPragmaTable pragmaTable;
};

class TScanContext;
class TPpContext;

//
// The following are extra variables needed during parsing, grouped together so
// they can be passed to the parser without needing a global.
//
class TParseContext {
public:
    TParseContext(TSymbolTable&, TIntermediate&, bool parsingBuiltins, int version, EProfile, EShLanguage, TInfoSink&,
                  bool forwardCompatible = false, EShMessages messages = EShMsgDefault);

    TScanContext* scanContext;
    TPpContext* ppContext;
    TIntermediate& intermediate; // to hold and build a parse tree
    TSymbolTable& symbolTable;   // symbol table that goes with the current language, version, and profile
    TInfoSink& infoSink;
    EShLanguage language;        // vertex or fragment language
    TIntermNode* treeRoot;       // root of parse tree being created
    TIntermAggregate *linkage;   // aggregate node of objects the linker may need, if not reference by the rest of the AST
    int numErrors;               // number of compile-time errors encountered
    int loopNestingLevel;        // 0 if outside all loops
    int structNestingLevel;      // 0 if outside blocks and structures
    TList<TIntermSequence*> switchSequenceStack;  // case, node, case, case, node, ...; ensure only one node between cases;   stack of them for nesting
    bool inTypeParen;            // true if in parentheses, looking only for an identifier
    const TType* currentFunctionType;  // the return type of the function that's currently being parsed
    bool functionReturnsValue;   // true if a non-void function has a return
    bool parsingBuiltins;        // true if parsing built-in symbols/functions

    int version;                 // version, updated by #version in the shader
    EProfile profile;            // the declared profile in the shader (core by default)
    bool forwardCompatible;      // true if errors are to be given for use of deprecated features
    EShMessages messages;        // errors/warnings
    TMap<TString, TBehavior> extensionBehavior;    // for each extension string, what it's current enablement is

    struct TPragma contextPragma;
    TPrecisionQualifier defaultPrecision[EbtNumTypes];
    static const int maxSamplerIndex = EsdNumDims * (EbtNumTypes * (2 * 2)); // see computeSamplerTypeIndex()
    TPrecisionQualifier defaultSamplerPrecision[maxSamplerIndex];
    bool afterEOF;
    bool tokensBeforeEOF;
    TSourceLoc currentLoc;
    const TString* blockName;
    TQualifier globalUniformDefaults;
    TQualifier globalInputDefaults;
    TQualifier globalOutputDefaults;
    TQualifier currentBlockDefaults;

    void initializeExtensionBehavior();
    const char* getPreamble();
    bool parseShaderStrings(TPpContext&, char* strings[], int strLen[], int numStrings);
    void parserError(const char *s);

    void handlePragma(const char **tokens, int numTokens);
    TBehavior getExtensionBehavior(const char* behavior);
    void updateExtensionBehavior(const char* extName, const char* behavior);
    
    void C_DECL error(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    void C_DECL  warn(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    bool reservedErrorCheck(TSourceLoc, const TString& identifier);

    TIntermTyped* handleVariable(TSourceLoc, TSymbol* symbol, TString* string);
    TIntermTyped* handleBracketDereference(TSourceLoc, TIntermTyped* base, TIntermTyped* index);
    TIntermTyped* handleDotDereference(TSourceLoc, TIntermTyped* base, TString& field);
    TIntermAggregate* handleFunctionPrototype(TSourceLoc, TFunction&);
    TIntermTyped* handleFunctionCall(TSourceLoc, TFunction*, TIntermNode*, TIntermAggregate*);
    TFunction* handleConstructorCall(TSourceLoc, TPublicType&);

    bool parseVectorFields(TSourceLoc, const TString&, int vecSize, TVectorFields&);
    void assignError(TSourceLoc, const char* op, TString left, TString right);
    void unaryOpError(TSourceLoc, const char* op, TString operand);
    void binaryOpError(TSourceLoc, const char* op, TString left, TString right);
    void variableCheck(TIntermTyped*& nodePtr);
    bool lValueErrorCheck(TSourceLoc, const char* op, TIntermTyped*);
    void constCheck(TIntermTyped* node, const char* token);
    void integerCheck(TIntermTyped* node, const char* token);
    void globalCheck(TSourceLoc, bool global, const char* token);
    bool constructorError(TSourceLoc, TIntermNode*, TFunction&, TOperator, TType&);
    void arraySizeCheck(TSourceLoc, TIntermTyped* expr, int& size);
    bool arrayQualifierError(TSourceLoc, const TPublicType&);
    void arraySizeRequiredCheck(TSourceLoc, int& size);
    void arrayDimError(TSourceLoc);
    void arrayDimCheck(TSourceLoc, TArraySizes sizes1, TArraySizes sizes2);
    void arrayDimCheck(TSourceLoc, const TType*, TArraySizes);
    void arrayCheck(TSourceLoc, TString& identifier, const TPublicType&, TVariable*& variable);
    bool insertBuiltInArrayAtGlobalLevel();
    bool voidErrorCheck(TSourceLoc, const TString&, const TPublicType&);
    void boolCheck(TSourceLoc, const TIntermTyped*);
    void boolCheck(TSourceLoc, const TPublicType&);
    bool samplerErrorCheck(TSourceLoc, const TPublicType& pType, const char* reason);
    void globalQualifierFix(TSourceLoc, TQualifier&, const TPublicType&);
    bool structQualifierErrorCheck(TSourceLoc, const TPublicType& pType);
    void mergeQualifiers(TSourceLoc, TQualifier& dst, const TQualifier& src, bool force);
    void setDefaultPrecision(TSourceLoc, TPublicType&, TPrecisionQualifier);
    int computeSamplerTypeIndex(TSampler&);
    TPrecisionQualifier getDefaultPrecision(TPublicType&);
    void precisionQualifierCheck(TSourceLoc, TPublicType&);
    void parameterSamplerCheck(TSourceLoc, TStorageQualifier qualifier, const TType& type);
    bool containsSampler(const TType& type);
    void nonInitConstCheck(TSourceLoc, TString& identifier, TPublicType& type);
    void nonInitCheck(TSourceLoc, TString& identifier, TPublicType& type);
    void paramCheck(TSourceLoc, TStorageQualifier qualifier, TType* type);
    void nestedBlockCheck(TSourceLoc);
    void nestedStructCheck(TSourceLoc);

    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&);
    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&, int);
    void mergeLayoutQualifiers(TSourceLoc, TQualifier& dest, const TQualifier& src);

    const TFunction* findFunction(TSourceLoc, TFunction* pfnCall, bool *builtIn = 0);
    bool executeInitializerError(TSourceLoc, TString& identifier, TPublicType& pType,
                                 TIntermTyped* initializer, TIntermNode*& intermNode, TVariable* variable = 0);
    TIntermTyped* addConstructor(TIntermNode*, const TType&, TOperator, TFunction*, TSourceLoc);
    TIntermTyped* constructStruct(TIntermNode*, const TType&, int, TSourceLoc);
    TIntermTyped* constructBuiltIn(const TType&, TOperator, TIntermNode*, TSourceLoc, bool subset);
    void addBlock(TSourceLoc, TTypeList& typeList, const TString* instanceName = 0, TArraySizes arraySizes = 0);
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

    bool arraySetMaxSize(TIntermSymbol*, TType*, int, bool, TSourceLoc);

    void requireProfile(TSourceLoc, EProfileMask profileMask, const char *featureDesc);
    void requireStage(TSourceLoc, EShLanguageMask languageMask, const char *featureDesc);
    void profileRequires(TSourceLoc, EProfile callingProfile, int minVersion, int numExtensions, const char* extensions[], const char *featureDesc);
    void profileRequires(TSourceLoc, EProfile callingProfile, int minVersion, const char* extension, const char *featureDesc);
    void checkDeprecated(TSourceLoc, EProfile callingProfile, int depVersion, const char *featureDesc);
    void requireNotRemoved(TSourceLoc, EProfile callingProfile, int removedVersion, const char *featureDesc);
    void fullIntegerCheck(TSourceLoc, const char* op);
    void doubleCheck(TSourceLoc, const char* op);
};

} // end namespace glslang

#endif // _PARSER_HELPER_INCLUDED_
