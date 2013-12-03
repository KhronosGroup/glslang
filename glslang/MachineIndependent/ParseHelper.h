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
#include "Scan.h"

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

    void setLimits(const TBuiltInResource&);
    bool parseShaderStrings(TPpContext&, TInputScanner& input, bool versionWillBeError = false);
    void parserError(const char *s);     // for bison's yyerror
    const char* getPreamble();

    void C_DECL error(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    void C_DECL  warn(TSourceLoc, const char *szReason, const char *szToken,
                      const char *szExtraInfoFormat, ...);
    bool reservedErrorCheck(TSourceLoc, const TString&);
    void reservedPpErrorCheck(TSourceLoc, const char* name, const char* op);
    void lineContinuationCheck(TSourceLoc);
    void commentCharacterCheck(TSourceLoc, int ch);
    bool builtInName(const TString&);

    void handlePragma(TSourceLoc, const TVector<TString>&);
    TIntermTyped* handleVariable(TSourceLoc, TSymbol* symbol, TString* string);
    TIntermTyped* handleBracketDereference(TSourceLoc, TIntermTyped* base, TIntermTyped* index);
    void checkIndex(TSourceLoc, const TType&, int& index);
    void handleIndexLimits(TSourceLoc, TIntermTyped* base, TIntermTyped* index);
    void handleInputArrayAccess(TSourceLoc, TIntermTyped* base);
    void checkInputArrayConsistency(TSourceLoc, bool tailOnly = false);
    void checkInputArrayConsistency(TSourceLoc, TLayoutGeometry, TType&, const TString&);
    TIntermTyped* handleDotDereference(TSourceLoc, TIntermTyped* base, TString& field);
    TFunction* handleFunctionDeclarator(TSourceLoc loc, TFunction& function);
    TIntermAggregate* handleFunctionDefinition(TSourceLoc, TFunction&);
    TIntermTyped* handleFunctionCall(TSourceLoc, TFunction*, TIntermNode*, TIntermAggregate*);
    void nonOpBuiltInCheck(TSourceLoc, const TFunction&, TIntermAggregate&);
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
    void samplerCheck(TSourceLoc, const TType&, const TString& identifier);
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
    TSymbol* redeclareBuiltinVariable(TSourceLoc, const TString&, const TQualifier&, const TShaderQualifiers&, bool& newDeclaration);
    bool redeclareBuiltinBlock(TSourceLoc, TTypeList& typeList, const TString& blockName, const TString* instanceName, TArraySizes* arraySizes);
    void paramCheckFix(TSourceLoc, const TStorageQualifier&, TType& type);
    void paramCheckFix(TSourceLoc, const TQualifier&, TType& type);
    void nestedBlockCheck(TSourceLoc);
    void nestedStructCheck(TSourceLoc);
    void arrayObjectCheck(TSourceLoc, const TType&, const char* op);
    void opaqueCheck(TSourceLoc, const TType&, const char* op);
    void structTypeCheck(TSourceLoc, TPublicType&);
    void inductiveLoopCheck(TSourceLoc, TIntermNode* init, TIntermLoop* loop);
    void inductiveLoopBodyCheck(TIntermNode*, int loopIndexId, TSymbolTable&);
    void constantIndexExpressionCheck(TIntermNode*);

    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&);
    void setLayoutQualifier(TSourceLoc, TPublicType&, TString&, int);
    void mergeShaderLayoutQualifiers(TSourceLoc, TShaderQualifiers& dst, const TShaderQualifiers& src);
    void mergeObjectLayoutQualifiers(TSourceLoc, TQualifier& dest, const TQualifier& src);
    void layoutTypeCheck(TSourceLoc, const TSymbol&);
    void layoutQualifierCheck(TSourceLoc, const TQualifier&);
    void checkNoShaderLayouts(TSourceLoc, const TShaderQualifiers&);

    const TFunction* findFunction(TSourceLoc loc, const TFunction& call, bool& builtIn);
    const TFunction* findFunctionExact(TSourceLoc loc, const TFunction& call, bool& builtIn);
    const TFunction* findFunction120(TSourceLoc loc, const TFunction& call, bool& builtIn);
    const TFunction* findFunction400(TSourceLoc loc, const TFunction& call, bool& builtIn);
    TIntermNode* declareVariable(TSourceLoc, TString& identifier, const TPublicType&, TArraySizes* typeArray = 0, TIntermTyped* initializer = 0);
    TIntermTyped* addConstructor(TSourceLoc, TIntermNode*, const TType&, TOperator);
    TIntermTyped* constructStruct(TIntermNode*, const TType&, int, TSourceLoc);
    TIntermTyped* constructBuiltIn(const TType&, TOperator, TIntermNode*, TSourceLoc, bool subset);
    void declareBlock(TSourceLoc, TTypeList& typeList, const TString* instanceName = 0, TArraySizes* arraySizes = 0);
    void addQualifierToExisting(TSourceLoc, TQualifier, const TString& identifier);
    void addQualifierToExisting(TSourceLoc, TQualifier, TIdentifierList&);
    void invariantCheck(TSourceLoc, const TType&, const TString& identifier);
    void updateStandaloneQualifierDefaults(TSourceLoc, const TPublicType&);
    void updateTypedDefaults(TSourceLoc, const TQualifier&, const TString* id);
    void wrapupSwitchSubsequence(TIntermAggregate* statements, TIntermNode* branchNode);
    TIntermNode* addSwitch(TSourceLoc, TIntermTyped* expression, TIntermAggregate* body);

    void updateMaxArraySize(TSourceLoc, TIntermNode*, int index);

    void setScanContext(TScanContext* c) { scanContext = c; }
    TScanContext* getScanContext() const { return scanContext; }
    void setPpContext(TPpContext* c) { ppContext = c; }
    TPpContext* getPpContext() const { return ppContext; }
    void addError() { ++numErrors; }
    int getNumErrors() const { return numErrors; }
    const TSourceLoc& getCurrentLoc() const { return currentScanner->getSourceLoc(); }
    void setCurrentLine(int line) { currentScanner->setLine(line); }
    void setCurrentString(int string) { currentScanner->setString(string); }

    // The following are implemented in Versions.cpp to localize version/profile/stage/extensions control
    void initializeExtensionBehavior();
    void requireProfile(TSourceLoc, int queryProfiles, const char *featureDesc);
    void profileRequires(TSourceLoc, int queryProfiles, int minVersion, int numExtensions, const char* const extensions[], const char *featureDesc);
    void profileRequires(TSourceLoc, int queryProfiles, int minVersion, const char* const extension, const char *featureDesc);
    void requireStage(TSourceLoc, EShLanguageMask, const char *featureDesc);
    void requireStage(TSourceLoc, EShLanguage, const char *featureDesc);
    void checkDeprecated(TSourceLoc, int queryProfiles, int depVersion, const char *featureDesc);
    void requireNotRemoved(TSourceLoc, int queryProfiles, int removedVersion, const char *featureDesc);
    void requireExtensions(TSourceLoc, int numExtensions, const char* const extensions[], const char *featureDesc);
    TExtensionBehavior getExtensionBehavior(const char*);
    bool extensionsTurnedOn(int numExtensions, const char* const extensions[]);
    void updateExtensionBehavior(const char* const extension, const char* behavior);
    void fullIntegerCheck(TSourceLoc, const char* op);
    void doubleCheck(TSourceLoc, const char* op);

protected:
    void nonInitConstCheck(TSourceLoc, TString& identifier, TType& type);
    TVariable* declareNonArray(TSourceLoc, TString& identifier, TType&, bool& newDeclaration);
    void declareArray(TSourceLoc, TString& identifier, const TType&, TSymbol*&, bool& newDeclaration);
    TIntermNode* executeInitializer(TSourceLoc, TString& identifier, TIntermTyped* initializer, TVariable* variable);
    TIntermTyped* convertInitializerList(TSourceLoc, const TType&, TIntermTyped* initializer);
    TOperator mapTypeToConstructorOp(const TType&);
    void finalErrorCheck();

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
    TQualifier currentBlockQualifier;
    TIntermAggregate *linkage;   // aggregate node of objects the linker may need, if not referenced by the rest of the AST
    TPrecisionQualifier defaultPrecision[EbtNumTypes];
    bool tokensBeforeEOF;
    TBuiltInResource resources;
    TLimits& limits;

protected:
    TScanContext* scanContext;
    TPpContext* ppContext;
    TInputScanner* currentScanner;
    int numErrors;               // number of compile-time errors encountered
    bool parsingBuiltins;        // true if parsing built-in symbols/functions
    TMap<TString, TExtensionBehavior> extensionBehavior;    // for each extension string, what its current behavior is set to
    static const int maxSamplerIndex = EsdNumDims * (EbtNumTypes * (2 * 2 * 2)); // see computeSamplerTypeIndex()
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

    //
    // Geometry shader input arrays:
    //  - array sizing is based on input primitive and/or explicit size
    //  - array sizing is retroactive
    //  - built-in block redeclarations interact with this
    //
    // Design:
    //  - use a per-context "resize-list", a list of entities whose array sizes
    //    can be fixed; this is logically one list, but physically two:
    //     * a list for nodes in the AST
    //     * a list for symbols in the symbol table
    //    this could be done a bit more simply, but this allows better error messages.
    //
    //  - the resize-list starts empty at beginning of user-shader compilation, it does
    //    not have built-ins in it
    //
    //  - on built-in input array use: copy-up symbol and add both the symbol and
    //    its use to resize-list
    //
    //  - on user-input array declaration: add it to the resize-list
    //
    //  - on block redeclaration: copy-up symbol and add it to the resize-list
    //     * note, that appropriately gives an error if redeclaring a block that
    //       was already used and hence already copied-up
    //
    //  - on seeing an input primitive-layout declaration, fix everything in the resize-list,
    //    giving errors for mismatch
    //
    //  - on seeing an array size declaration, give errors on mismatch between it and previous
    //    input primitive declarations
    //
    TVector<TIntermSymbol*> inputArrayNodeResizeList;
    TVector<TSymbol*> inputArraySymbolResizeList;
};

} // end namespace glslang

#endif // _PARSER_HELPER_INCLUDED_
