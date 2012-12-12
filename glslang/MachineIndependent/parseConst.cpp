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

#include "ParseHelper.h"

//
// Use this class to carry along data from node to node in 
// the traversal
//
class TConstTraverser : public TIntermTraverser {
public:
    TConstTraverser(constUnion* cUnion, bool singleConstParam, TOperator constructType, TInfoSink& sink, TSymbolTable& symTable, TType& t) : unionArray(cUnion), type(t),
        constructorType(constructType), singleConstantParam(singleConstParam), infoSink(sink), symbolTable(symTable), error(false), isMatrix(false), matrixSize(0) {  index = 0; tOp = EOpNull;}
    int index ;
    constUnion *unionArray;
    TOperator tOp;
    TType type;
    TOperator constructorType;
    bool singleConstantParam;
    TInfoSink& infoSink;
    TSymbolTable& symbolTable;
    bool error;
    int size; // size of the constructor ( 4 for vec4)
    bool isMatrix;
    int matrixSize; // dimension of the matrix (nominal size and not the instance size)
};

//
// The rest of the file are the traversal functions.  The last one
// is the one that starts the traversal.
//
// Return true from interior nodes to have the external traversal
// continue on to children.  If you process children yourself,
// return false.
//

void ParseSymbol(TIntermSymbol* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    oit->infoSink.info.message(EPrefixInternalError, "Symbol Node found in constant constructor", node->getLine());
    return;

}

bool ParseBinary(bool /* preVisit */, TIntermBinary* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    
    TQualifier qualifier = node->getType().getQualifier();
    
    if (qualifier != EvqConst) {
        char buf[200];
        sprintf(buf, "'constructor' : assigning non-constant to %s", oit->type.getCompleteString().c_str());
        oit->infoSink.info.message(EPrefixError, buf, node->getLine());
        oit->error = true;
        return false;  
    }

   oit->infoSink.info.message(EPrefixInternalError, "Binary Node found in constant constructor", node->getLine());
    
    return false;
}

bool ParseUnary(bool /* preVisit */, TIntermUnary* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);

    char buf[200];
    sprintf(buf, "'constructor' : assigning non-constant to '%s'", oit->type.getCompleteString().c_str());
    oit->infoSink.info.message(EPrefixError, buf, node->getLine());
    oit->error = true;
    return false;  
}

bool ParseAggregate(bool /* preVisit */, TIntermAggregate* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);

    if (!node->isConstructor() && node->getOp() != EOpComma) {
        char buf[200];
        sprintf(buf, "'constructor' : assigning non-constant to '%s'", oit->type.getCompleteString().c_str());
        oit->infoSink.info.message(EPrefixError, buf, node->getLine());
        oit->error = true;
        return false;  
    }

    if (node->getSequence().size() == 0) {
        oit->error = true;
        return false;
    }

    bool flag = node->getSequence().size() == 1 && node->getSequence()[0]->getAsTyped()->getAsConstantUnion();
    if (flag) 
    {
        oit->singleConstantParam = true; 
        oit->constructorType = node->getOp();
        oit->size = node->getType().getObjectSize();

        if (node->getType().isMatrix()) {
            oit->isMatrix = true;
            oit->matrixSize = node->getType().getNominalSize();
        }
    }       

    for (TIntermSequence::iterator p = node->getSequence().begin(); 
                                   p != node->getSequence().end(); p++) {

        if (node->getOp() == EOpComma)
            oit->index = 0;           

        (*p)->traverse(oit);
    }   
    if (flag) 
    {
        oit->singleConstantParam = false;   
        oit->constructorType = EOpNull;
        oit->size = 0;
        oit->isMatrix = false;
        oit->matrixSize = 0;
    }
    return false;
}

bool ParseSelection(bool /* preVisit */, TIntermSelection* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    oit->infoSink.info.message(EPrefixInternalError, "Selection Node found in constant constructor", node->getLine());
    oit->error = true;
    return false;
}

void ParseConstantUnion(TIntermConstantUnion* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    constUnion* leftUnionArray = oit->unionArray;
    int instanceSize = oit->type.getObjectSize();

    if (oit->index >= instanceSize)
        return;

    if (!oit->singleConstantParam) {
        int size = node->getType().getObjectSize();
    
        constUnion *rightUnionArray = node->getUnionArrayPointer();
        for (int i=0; i < size; i++) {
            if (oit->index >= instanceSize)
                return;
            leftUnionArray[oit->index] = rightUnionArray[i];

            (oit->index)++;
        }
    } else {
        int size, totalSize, matrixSize;
        bool isMatrix = false;
        size = oit->size;
        matrixSize = oit->matrixSize;
        isMatrix = oit->isMatrix;
        totalSize = oit->index + size ;
        constUnion *rightUnionArray = node->getUnionArrayPointer();
        if (!isMatrix) {
            int count = 0;
            for (int i = oit->index; i < totalSize; i++) {
                if (i >= instanceSize)
                    return;

                leftUnionArray[i] = rightUnionArray[count];

                (oit->index)++;
                
                if (node->getType().getObjectSize() > 1)
                    count++;
            }
        } else {  // for matrix constructors
            int count = 0;
            int index = oit->index;
            for (int i = index; i < totalSize; i++) {
                if (i >= instanceSize)
                    return;
                if (index - i == 0 || (i - index) % (matrixSize + 1) == 0 )
                    leftUnionArray[i] = rightUnionArray[count];
                else 
                    leftUnionArray[i].setFConst(0.0f);

                (oit->index)++;

                if (node->getType().getObjectSize() > 1)
                    count++;                
            }
        }
    }
}

bool ParseLoop(bool /* preVisit */, TIntermLoop* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    oit->infoSink.info.message(EPrefixInternalError, "Loop Node found in constant constructor", node->getLine());
    oit->error = true;
    return false;
}

bool ParseBranch(bool /* previsit*/, TIntermBranch* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    oit->infoSink.info.message(EPrefixInternalError, "Branch Node found in constant constructor", node->getLine());
    oit->error = true;
    return false;
}

//
// This function is the one to call externally to start the traversal.
// Individual functions can be initialized to 0 to skip processing of that
// type of node.  It's children will still be processed.
//
bool TIntermediate::parseConstTree(TSourceLoc line, TIntermNode* root, constUnion* unionArray, TOperator constructorType, TSymbolTable& symbolTable, TType t, bool singleConstantParam)
{
    if (root == 0)
        return false;

    TConstTraverser it(unionArray, singleConstantParam, constructorType, infoSink, symbolTable, t);
    
    it.visitAggregate = ParseAggregate;
    it.visitBinary = ParseBinary;
    it.visitConstantUnion = ParseConstantUnion;
    it.visitSelection = ParseSelection;
    it.visitSymbol = ParseSymbol;
    it.visitUnary = ParseUnary;
    it.visitLoop = ParseLoop;
    it.visitBranch = ParseBranch;

    root->traverse(&it);
    if (it.error)
        return true;
    else
        return false;
}
