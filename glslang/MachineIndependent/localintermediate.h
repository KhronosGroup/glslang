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
#include "SymbolTable.h"

struct TVectorFields {
    int offsets[4];
    int num;
};

//
// Set of helper functions to help parse and build the tree.
//
class TInfoSink;
class TIntermediate {
public:    
    POOL_ALLOCATOR_NEW_DELETE(GlobalPoolAllocator)

    TIntermediate(TInfoSink& i) : infoSink(i) { }
    TIntermSymbol* addSymbol(int Id, const TString&, const TType&, TSourceLoc);
    TIntermTyped* addConversion(TOperator, const TType&, TIntermTyped*);
    TIntermTyped* addBinaryMath(TOperator op, TIntermTyped* left, TIntermTyped* right, TSourceLoc, TSymbolTable&);
    TIntermTyped* addAssign(TOperator op, TIntermTyped* left, TIntermTyped* right, TSourceLoc);
    TIntermTyped* addIndex(TOperator op, TIntermTyped* base, TIntermTyped* index, TSourceLoc);
    TIntermTyped* addUnaryMath(TOperator op, TIntermNode* child, TSourceLoc, TSymbolTable&);
    TIntermAggregate* growAggregate(TIntermNode* left, TIntermNode* right, TSourceLoc);
    TIntermAggregate* makeAggregate(TIntermNode* node, TSourceLoc);
    TIntermAggregate* setAggregateOperator(TIntermNode*, TOperator, TSourceLoc);
    TIntermNode*  addSelection(TIntermTyped* cond, TIntermNodePair code, TSourceLoc);
    TIntermTyped* addSelection(TIntermTyped* cond, TIntermTyped* trueBlock, TIntermTyped* falseBlock, TSourceLoc);
    TIntermTyped* addComma(TIntermTyped* left, TIntermTyped* right, TSourceLoc);
    TIntermConstantUnion* addConstantUnion(constUnion*, const TType&, TSourceLoc);
    TIntermTyped* promoteConstantUnion(TBasicType, TIntermConstantUnion*) ;
    bool parseConstTree(TSourceLoc, TIntermNode*, constUnion*, TOperator, TSymbolTable&, TType, bool singleConstantParam = false);        
    TIntermNode* addLoop(TIntermNode*, TIntermTyped*, TIntermTyped*, bool testFirst, TSourceLoc);
    TIntermBranch* addBranch(TOperator, TSourceLoc);
    TIntermBranch* addBranch(TOperator, TIntermTyped*, TSourceLoc);
    TIntermTyped* addSwizzle(TVectorFields&, TSourceLoc);
    bool postProcess(TIntermNode*, EShLanguage);
	void remove(TIntermNode*);
    void outputTree(TIntermNode*);
    
protected:
    TInfoSink& infoSink;

private:
    void operator=(TIntermediate&); // prevent assignments
};

#endif // _LOCAL_INTERMEDIATE_INCLUDED_
