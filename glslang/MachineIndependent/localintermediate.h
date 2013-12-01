//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
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

#ifndef _LOCAL_INTERMEDIATE_INCLUDED_
#define _LOCAL_INTERMEDIATE_INCLUDED_

#include "../Include/intermediate.h"
#include "../Public/ShaderLang.h"
#include "Versions.h"

#include <algorithm>
#include <set>

class TInfoSink;

namespace glslang {

struct TVectorFields {
    int offsets[4];
    int num;
};

class TSymbolTable;
class TSymbol;

//
// Set of helper functions to help parse and build the tree.
//
class TIntermediate {
public:
    explicit TIntermediate(EShLanguage l, int v = 0, EProfile p = ENoProfile) : language(l), treeRoot(0), profile(p), version(v), 
        numMains(0), numErrors(0), recursive(false),
        invocations(0), maxVertices(0), inputPrimitive(ElgNone), outputPrimitive(ElgNone), pixelCenterInteger(false), originUpperLeft(false) { }
    bool postProcess(TIntermNode*, EShLanguage);
    void outputTree(TInfoSink&);
	void removeTree();

    void setVersion(int v) { version = v; }
    int getVersion() const { return version; }
    void setProfile(EProfile p) { profile = p; }
    EProfile getProfile() const { return profile; }
    void setTreeRoot(TIntermNode* r) { treeRoot = r; }
    TIntermNode* getTreeRoot() const { return treeRoot; }
    void addMainCount() { ++numMains; }
    int getNumMains() const { return numMains; }
    int getNumErrors() const { return numErrors; }
    bool isRecursive() const { return recursive; }
    
    TIntermSymbol* addSymbol(int Id, const TString&, const TType&, TSourceLoc);
    TIntermTyped* addConversion(TOperator, const TType&, TIntermTyped*);
    TIntermTyped* addBinaryMath(TOperator, TIntermTyped* left, TIntermTyped* right, TSourceLoc);
    TIntermTyped* addAssign(TOperator op, TIntermTyped* left, TIntermTyped* right, TSourceLoc);
    TIntermTyped* addIndex(TOperator op, TIntermTyped* base, TIntermTyped* index, TSourceLoc);
    TIntermTyped* addUnaryMath(TOperator, TIntermNode* child, TSourceLoc);
    TIntermTyped* addBuiltInFunctionCall(TSourceLoc line, TOperator, bool unary, TIntermNode*, const TType& returnType);
    bool canImplicitlyPromote(TBasicType from, TBasicType to);
    TIntermAggregate* growAggregate(TIntermNode* left, TIntermNode* right);
    TIntermAggregate* growAggregate(TIntermNode* left, TIntermNode* right, TSourceLoc);
    TIntermAggregate* makeAggregate(TIntermNode* node);
    TIntermAggregate* makeAggregate(TIntermNode* node, TSourceLoc);
    TIntermTyped* setAggregateOperator(TIntermNode*, TOperator, const TType& type, TSourceLoc);
    bool areAllChildConst(TIntermAggregate* aggrNode);
    TIntermNode*  addSelection(TIntermTyped* cond, TIntermNodePair code, TSourceLoc);
    TIntermTyped* addSelection(TIntermTyped* cond, TIntermTyped* trueBlock, TIntermTyped* falseBlock, TSourceLoc);
    TIntermTyped* addComma(TIntermTyped* left, TIntermTyped* right, TSourceLoc);
    TIntermTyped* addMethod(TIntermTyped*, const TType&, const TString*, TSourceLoc);
    TIntermConstantUnion* addConstantUnion(const TConstUnionArray&, const TType&, TSourceLoc);
    TIntermTyped* promoteConstantUnion(TBasicType, TIntermConstantUnion*) ;
    bool parseConstTree(TIntermNode*, TConstUnionArray, TOperator, const TType&, bool singleConstantParam = false);
    TIntermLoop* addLoop(TIntermNode*, TIntermTyped*, TIntermTyped*, bool testFirst, TSourceLoc);
    TIntermBranch* addBranch(TOperator, TSourceLoc);
    TIntermBranch* addBranch(TOperator, TIntermTyped*, TSourceLoc);
    TIntermTyped* addSwizzle(TVectorFields&, TSourceLoc);

    // Constant folding (in Constant.cpp)
    TIntermTyped* fold(TIntermAggregate* aggrNode);
    TIntermTyped* foldConstructor(TIntermAggregate* aggrNode);
    TIntermTyped* foldDereference(TIntermTyped* node, int index, TSourceLoc);
    TIntermTyped* foldSwizzle(TIntermTyped* node, TVectorFields& fields, TSourceLoc);

    // Linkage related
    void addSymbolLinkageNodes(TIntermAggregate*& linkage, EShLanguage, TSymbolTable&);
    void addSymbolLinkageNode(TIntermAggregate*& linkage, TSymbolTable&, const TString&);
    void addSymbolLinkageNode(TIntermAggregate*& linkage, const TSymbol&);

    bool setInvocations(int i) 
    {
        if (invocations > 0)
            return false;
        invocations = i;
        return true;
    }
    bool setMaxVertices(int m)
    {
        if (maxVertices > 0)
            return maxVertices == m;
        maxVertices = m;
        return true;
    }
    bool setInputPrimitive(TLayoutGeometry p)
    {
        if (inputPrimitive != ElgNone)
            return inputPrimitive == p;
        inputPrimitive = p;
        return true;
    }
    TLayoutGeometry getInputPrimitive() { return inputPrimitive; }
    bool setOutputPrimitive(TLayoutGeometry p)
    {
        if (outputPrimitive != ElgNone)
            return outputPrimitive == p;
        outputPrimitive = p;
        return true;
    }
    void setOriginUpperLeft() { originUpperLeft = true; }
    bool getOriginUpperLeft() const { return originUpperLeft; }
    void setPixelCenterInteger() { pixelCenterInteger = true; }
    bool getPixelCenterInteger() const { return pixelCenterInteger; }

    void addToCallGraph(TInfoSink&, const TString& caller, const TString& callee);
    void merge(TInfoSink&, TIntermediate&);
    void errorCheck(TInfoSink&);

    void addIoAccessed(const TString& name) { ioAccessed.insert(name); }
    bool inIoAccessed(const TString& name) const { return ioAccessed.find(name) != ioAccessed.end(); }

protected:
    void error(TInfoSink& infoSink, const char*);
    void mergeBodies(TInfoSink&, TIntermSequence& globals, const TIntermSequence& unitGlobals);
    void mergeLinkerObjects(TInfoSink&, TIntermSequence& linkerObjects, const TIntermSequence& unitLinkerObjects);
    void mergeErrorCheck(TInfoSink&, const TIntermSymbol&, const TIntermSymbol&, bool crossStage);
    void checkCallGraphCycles(TInfoSink&);
    void inOutLocationCheck(TInfoSink&);
    TIntermSequence& findLinkerObjects() const;
    bool userOutputUsed() const;

protected:
    const EShLanguage language;
    TIntermNode* treeRoot;
    EProfile profile;
    int version;
    int numMains;
    int numErrors;
    bool recursive;
    int invocations;
    int maxVertices;
    TLayoutGeometry inputPrimitive;
    TLayoutGeometry outputPrimitive;
    bool pixelCenterInteger;
    bool originUpperLeft;

    // for detecting recursion:  pair is <caller, callee>
    struct TCall {
        TCall(const TString& pCaller, const TString& pCallee) : caller(pCaller), callee(pCallee) { }
        TString caller;
        TString callee;
        bool visited;
        bool currentPath;
        bool errorGiven;
    };
    typedef std::list<TCall> TGraph;
    TGraph callGraph;

    std::set<TString> ioAccessed;  // set of names of statically read/written I/O that might need extra checking

private:
    void operator=(TIntermediate&); // prevent assignments
};

} // end namespace glslang

#endif // _LOCAL_INTERMEDIATE_INCLUDED_
