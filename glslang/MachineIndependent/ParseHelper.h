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

struct TMatrixFields {
    bool wholeRow;
    bool wholeCol;
    int row;
    int col;
};

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

//
// The following are extra variables needed during parsing, grouped together so
// they can be passed to the parser without needing a global.
//
struct TParseContext {
    TParseContext(TSymbolTable& symt, TIntermediate& interm, EShLanguage L, TInfoSink& is);
    TIntermediate& intermediate; // to hold and build a parse tree
    TSymbolTable& symbolTable;   // symbol table that goes with the language currently being parsed
    TInfoSink& infoSink;
    EShLanguage language;        // vertex or fragment language
    TIntermNode* treeRoot;       // root of parse tree being created
    bool recoveredFromError;     // true if a parse error has occurred, but we continue to parse
    int numErrors;
    bool lexAfterType;           // true if we've recognized a type, so can only be looking for an identifier
    int loopNestingLevel;        // 0 if outside all loops
    int switchNestingLevel;      // 0 if outside all switch statements
    bool inTypeParen;            // true if in parentheses, looking only for an identifier
    const TType* currentFunctionType;  // the return type of the function that's currently being parsed
    bool functionReturnsValue;   // true if a non-void function has a return

    int version;                 // the declared version in the shader (110 by default)
    EProfile profile;            // the declared profile in the shader (core by default)
    bool futureCompatibility;    // true if requesting errors for future compatibility (false by default)
    TMap<TString, TBehavior> extensionBehavior;    // for each extension string, what it's current enablement is

    struct TPragma contextPragma;
    TPrecisionQualifier defaultPrecision[EbtNumTypes];
	TString HashErrMsg;
    bool AfterEOF;

    void initializeExtensionBehavior();

    void C_DECL error(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    bool reservedErrorCheck(int line, const TString& identifier);
    void recover();

    bool parseVectorFields(const TString&, int vecSize, TVectorFields&, int line);
    void assignError(int line, const char* op, TString left, TString right);
    void unaryOpError(int line, char* op, TString operand);
    void binaryOpError(int line, char* op, TString left, TString right);
    void variableErrorCheck(TIntermTyped*& nodePtr);
    bool lValueErrorCheck(int line, char* op, TIntermTyped*);
    bool constErrorCheck(TIntermTyped* node);
    bool integerErrorCheck(TIntermTyped* node, char* token);
    bool globalErrorCheck(int line, bool global, char* token);
    bool constructorErrorCheck(int line, TIntermNode*, TFunction&, TOperator, TType*);
    bool arraySizeErrorCheck(int line, TIntermTyped* expr, int& size);
    bool arrayQualifierErrorCheck(int line, TPublicType type);
    bool arraySizeRequiredErrorCheck(int line, int& size);
    bool arrayErrorCheck(int line, TString& identifier, TPublicType type, TVariable*& variable);
    bool insertBuiltInArrayAtGlobalLevel();
    bool voidErrorCheck(int, const TString&, const TPublicType&);
    bool boolErrorCheck(int, const TIntermTyped*);
    bool boolErrorCheck(int, const TPublicType&);
    bool samplerErrorCheck(int line, const TPublicType& pType, const char* reason);
    bool globalQualifierFixAndErrorCheck(int line, TQualifier&);
    bool structQualifierErrorCheck(int line, const TPublicType& pType);
    void setDefaultPrecision(int line, TBasicType, TPrecisionQualifier);
    bool parameterSamplerErrorCheck(int line, TStorageQualifier qualifier, const TType& type);
    bool containsSampler(TType& type);
    bool nonInitConstErrorCheck(int line, TString& identifier, TPublicType& type);
    bool nonInitErrorCheck(int line, TString& identifier, TPublicType& type);
    bool paramErrorCheck(int line, TStorageQualifier qualifier, TType* type);
    const TFunction* findFunction(int line, TFunction* pfnCall, bool *builtIn = 0);
    bool executeInitializer(TSourceLoc line, TString& identifier, TPublicType& pType,
                            TIntermTyped* initializer, TIntermNode*& intermNode, TVariable* variable = 0);
    bool areAllChildConst(TIntermAggregate* aggrNode);
    TIntermTyped* addConstructor(TIntermNode*, const TType*, TOperator, TFunction*, TSourceLoc);
    TIntermTyped* foldConstConstructor(TIntermAggregate* aggrNode, const TType& type);
    TIntermTyped* constructStruct(TIntermNode*, TType*, int, TSourceLoc, bool subset);
    TIntermTyped* constructBuiltIn(const TType*, TOperator, TIntermNode*, TSourceLoc, bool subset);
    TIntermTyped* addConstVectorNode(TVectorFields&, TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstMatrixNode(int , TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstArrayNode(int index, TIntermTyped* node, TSourceLoc line);
    TIntermTyped* addConstStruct(TString& , TIntermTyped*, TSourceLoc);
    bool arraySetMaxSize(TIntermSymbol*, TType*, int, bool, TSourceLoc);
    void requireProfile(int line, EProfileMask profileMask, const char *featureDesc);
    void requireStage(int line, EShLanguageMask languageMask, const char *featureDesc);
    void profileRequires(int line, EProfile callingProfile, int minVersion, int numExtensions, const char* extensions[], const char *featureDesc);
    void profileRequires(int line, EProfile callingProfile, int minVersion, const char* extension, const char *featureDesc);
    void checkDeprecated(int line, EProfile callingProfile, int depVersion, const char *featureDesc);
    void requireNotRemoved(int line, EProfile callingProfile, int removedVersion, const char *featureDesc);
};

int PaParseStrings(char* argv[], int strLen[], int argc, TParseContext&);
void PaReservedWord();
int PaIdentOrType(TString& id, TParseContext&, TSymbol*&);
int PaParseComment(int &lineno, TParseContext&);
void setInitialState();

typedef TParseContext* TParseContextPointer;
extern TParseContextPointer& GetGlobalParseContext();
#define GlobalParseContext GetGlobalParseContext()

typedef struct TThreadParseContextRec
{
	TParseContext *lpGlobalParseContext;
} TThreadParseContext;

#endif // _PARSER_HELPER_INCLUDED_
