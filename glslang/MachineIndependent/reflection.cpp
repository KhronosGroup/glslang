//
//Copyright (C) 2013 LunarG, Inc.
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

#include "../Include/Common.h"
#include "reflection.h"
#include "localintermediate.h"

//
// Grow the reflection database through a friend traverser class of TReflection and a 
// collection of functions to do a liveness traversal that note what uniforms are used
// in semantically non-dead code.
//
// Can be used multiple times, once per stage, to grow a program reflection.
//
// High-level algorithm for one stage:
//
// 1. Put main() on list of live functions.
//
// 2. Traverse any live function, while skipping if-tests with a compile-time constant 
//    condition of false, and while adding any encountered function calls to the live 
//    function list.
//
//    Repeat until the live function list is empty.
//
// 3. Add any encountered uniform variables and blocks to the reflection database.
//
// Can be attempted with a failed link, but will return false if recursion had been detected, or 
// there wasn't exactly one main.
//

namespace glslang {

//
// The traverser: mostly pass through, except 
//  - processing function-call nodes to push live functions onto the stack of functions to process
//  - processing binary nodes to see if they are dereferences of aggregates to track
//  - processing symbol nodes to see if they are non-aggregate objects to track
//  - processing selection nodes to trim semantically dead code
//
// This is in the glslang namespace directly so it can be a friend of TReflection.
//

class TLiveTraverser : public TIntermTraverser {
public:
    TLiveTraverser(const TIntermediate& i, TReflection& r) : intermediate(i), reflection(r) { }

    // Track live funtions as well as uniforms, so that we don't visit dead functions
    // and only visit each function once.
    void addFunctionCall(TIntermAggregate* call)
    {
        // just use the map to ensure we process each function at most once
        if (reflection.nameToIndex.find(call->getName()) == reflection.nameToIndex.end()) {
            reflection.nameToIndex[call->getName()] = -1;
            pushFunction(call->getName());
        }
    }

    // Add a simple uniform variable reference to the uniform database, no derefence involved.
    void addUniform(const TIntermSymbol& symbol)
    {
        if (reflection.nameToIndex.find(symbol.getName()) == reflection.nameToIndex.end()) {
            if (isReflectionGranularity(symbol.getType())) {
                reflection.nameToIndex[symbol.getName()] = reflection.indexToUniform.size();
                reflection.indexToUniform.push_back(TObjectReflection(symbol.getName(), -1, MapToGlType(symbol.getType()), MapToGlArraySize(symbol.getType()), -1));
            }
        }
    }

    // Add a complex uniform reference where blocks/struct/arrays are involved in tha access.
    void addDereferencedUniform(TIntermSymbol* base, TIntermBinary* node)
    {
        bool block = base->getBasicType() == EbtBlock;
        int offset = -1;
        int blockIndex = -1;
        bool anonymous = false;
        if (block) {
            anonymous = base->getName().compare(0, 6, "__anon") == 0;
            const TString& blockName = anonymous ? base->getType().getTypeName() : base->getName();
            TReflection::TNameToIndex::const_iterator it = reflection.nameToIndex.find(blockName);
            if (it == reflection.nameToIndex.end()) {
                blockIndex = reflection.indexToUniformBlock.size();
                reflection.nameToIndex[blockName] = blockIndex;
                reflection.indexToUniformBlock.push_back(TObjectReflection(blockName, -1,  -1, 1, -1));
            } else
                blockIndex = it->second;
        }
        TString name;

        switch (node->getOp()) {
        case EOpIndexDirect:
        case EOpIndexIndirect:
            // TODO: reflection: handle array dereferences
            //name = base->getName();
            //name.append("[]");
            break;
        case EOpIndexDirectStruct:
        {
            if (! anonymous) {
                name = base->getName();
                name.append(".");
            }
            int structIndex = node->getRight()->getAsConstantUnion()->getConstArray()[0].getIConst();
            if (block)
                offset = structIndex * 16; // TODO: reflection: compute std140 offsets
            name.append((*base->getType().getStruct())[structIndex].type->getFieldName().c_str());
            break;
        }
        default:
            break;
        }

        // TODO: reflection: handle deeper dereference chains than just one dereference

        if (name.size() > 0) {
            if (reflection.nameToIndex.find(name) == reflection.nameToIndex.end()) {
                reflection.nameToIndex[name] = reflection.indexToUniform.size();                        
                reflection.indexToUniform.push_back(TObjectReflection(name, offset, MapToGlType(node->getType()), MapToGlArraySize(node->getType()), blockIndex));
            }
        }
    }

    //
    // Given a function name, find its subroot in the tree, and push it onto the stack of 
    // functions left to process.
    //
    void pushFunction(const TString& name)
    {
        TIntermSequence& globals = intermediate.getTreeRoot()->getAsAggregate()->getSequence();
        for (unsigned int f = 0; f < globals.size(); ++f) {
            TIntermAggregate* candidate = globals[f]->getAsAggregate();
            if (candidate && candidate->getOp() == EOpFunction && candidate->getName() == name) {
                functions.push_back(candidate);
                break;
            }
        }
    }

    // Are we at a level in a dereference chain at which individual active uniform queries are made?
    bool isReflectionGranularity(const TType& type)
    {
        return type.getBasicType() != EbtBlock && type.getBasicType() != EbtStruct;
    }

    // For a binary operation indexing into an aggregate, chase down the base of the aggregate.
    // Return 0 if the topology does not fit this situation.
    TIntermSymbol* findBase(const TIntermBinary* node)
    {
        TIntermSymbol *symbol = node->getLeft()->getAsSymbolNode();
        if (symbol)
            return symbol;
        TIntermBinary* left = node->getLeft()->getAsBinaryNode();
        if (! left)
            return 0;

        return findBase(left);
    }

    int MapToGlType(const TType& type)
    {
        // TODO: reflection: flesh out all GL types
        #define GL_FLOAT_VEC4 0x8B52

        return GL_FLOAT_VEC4;
    }

    int MapToGlArraySize(const TType& type)
    {
        return type.isArray() ? type.getArraySize() : 1;
    }
    
    typedef std::list<TIntermAggregate*> TFunctionStack;
    TFunctionStack functions;
    const TIntermediate& intermediate;
    TReflection& reflection;
};

namespace {

//
// Implement the traversal functions of interest.
//

// To catch which function calls are not dead, and hence which functions must be visited.
bool LiveAggregate(bool /* preVisit */, TIntermAggregate* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    if (node->getOp() == EOpFunctionCall)
        oit->addFunctionCall(node);

    return true; // traverse this subtree
}

// To catch dereferenced aggregates that must be reflected.
bool LiveBinary(bool /* preVisit */, TIntermBinary* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    switch (node->getOp()) {
    case EOpIndexDirect:
    case EOpIndexIndirect:
    case EOpIndexDirectStruct:
        // If the left side is already small enough granularity to report, ignore
        // this operation, and pick it up when the left side is visited.
        if (! oit->isReflectionGranularity(node->getLeft()->getType()) &&
            oit->isReflectionGranularity(node->getType())) {            
            // right granularity; see if this really is a uniform-based dereference
            TIntermSymbol* base = oit->findBase(node);
            if (base && base->getQualifier().storage == EvqUniform)
                oit->addDereferencedUniform(base, node);
        }
    default:
        break;
    }

    return true;  // still need to visit everything below
}

// To catch non-dereferenced objects that must be reflected.
void LiveSymbol(TIntermSymbol* symbol, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    if (symbol->getQualifier().storage == EvqUniform)
        oit->addUniform(*symbol);
}

// To prune semantically dead paths.
bool LiveSelection(bool /* preVisit */,  TIntermSelection* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    TIntermConstantUnion* constant = node->getCondition()->getAsConstantUnion();
    if (constant) {
        // cull the path that is dead
        if (constant->getConstArray()[0].getBConst() == true && node->getTrueBlock())
            node->getTrueBlock()->traverse(it);
        if (constant->getConstArray()[0].getBConst() == false && node->getFalseBlock())
            node->getFalseBlock()->traverse(it);

        return false; // don't traverse any more, we did it all above
    } else
        return true; // traverse the whole subtree
}

} // end anonymous namespace

//
// Implement TReflection methods.
//

// Merge live symbols from 'intermediate' into the existing reflection database.
//
// Returns false if the input is too malformed to do this.
bool TReflection::addStage(EShLanguage, const TIntermediate& intermediate)
{    
    if (intermediate.getNumMains() != 1 || intermediate.isRecursive())
        return false;

    TLiveTraverser it(intermediate, *this);
    it.visitSymbol = LiveSymbol;
    it.visitSelection = LiveSelection;
    it.visitBinary = LiveBinary;
    it.visitAggregate = LiveAggregate;

    // put main() on functions to process
    it.pushFunction("main(");

    // process all the functions
    while (! it.functions.empty()) {
        TIntermNode* function = it.functions.back();
        it.functions.pop_back();
        function->traverse(&it);
    }

    return true;
}

void TReflection::dump()
{
    printf("Uniform reflection:\n");
    for (size_t i = 0; i < indexToUniform.size(); ++i) {
        printf("%d:", (int)i);
        indexToUniform[i].dump();
    }
    printf("\n");

    printf("Uniform block reflection:\n");
    for (size_t i = 0; i < indexToUniformBlock.size(); ++i) {
        printf("%d: ", (int)i);
        indexToUniformBlock[i].dump();
    }
    printf("\n");

    printf("Live names\n");
    for (TNameToIndex::const_iterator it = nameToIndex.begin(); it != nameToIndex.end(); ++it)
        printf("%s: %d\n", it->first.c_str(), it->second);
    printf("\n");
}

} // end namespace glslang
