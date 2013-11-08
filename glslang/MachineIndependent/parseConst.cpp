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

//
// Travarse a tree of constants to create a single folded constant.
// It should only be used when the whole tree is known to be constant.
//

#include "ParseHelper.h"

namespace glslang {

class TConstTraverser : public TIntermTraverser {
public:
    TConstTraverser(const TConstUnionArray& cUnion, bool singleConstParam, TOperator constructType, const TType& t) : unionArray(cUnion), type(t),
        constructorType(constructType), singleConstantParam(singleConstParam), error(false), isMatrix(false), 
        matrixCols(0), matrixRows(0) {  index = 0; tOp = EOpNull; }
    int index;
    TConstUnionArray unionArray;
    TOperator tOp;
    const TType& type;
    TOperator constructorType;
    bool singleConstantParam;
    bool error;
    int size; // size of the constructor ( 4 for vec4)
    bool isMatrix;
    int matrixCols;
    int matrixRows;
};

bool ParseAggregate(bool /* preVisit */, TIntermAggregate* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);

    if (! node->isConstructor() && node->getOp() != EOpComma) {
        oit->error = true;

        return false;  
    }

    if (node->getSequence().size() == 0) {
        oit->error = true;

        return false;
    }

    bool flag = node->getSequence().size() == 1 && node->getSequence()[0]->getAsTyped()->getAsConstantUnion();
    if (flag) {
        oit->singleConstantParam = true; 
        oit->constructorType = node->getOp();
        oit->size = node->getType().getObjectSize();

        if (node->getType().isMatrix()) {
            oit->isMatrix = true;
            oit->matrixCols = node->getType().getMatrixCols();
            oit->matrixRows = node->getType().getMatrixRows();
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
        oit->matrixCols = 0;
        oit->matrixRows = 0;
    }

    return false;
}

void ParseConstantUnion(TIntermConstantUnion* node, TIntermTraverser* it)
{
    TConstTraverser* oit = static_cast<TConstTraverser*>(it);
    TConstUnionArray leftUnionArray(oit->unionArray);
    int instanceSize = oit->type.getObjectSize();

    if (oit->index >= instanceSize)
        return;

    if (! oit->singleConstantParam) {
        int size = node->getType().getObjectSize();
    
        const TConstUnionArray& rightUnionArray = node->getConstArray();
        for (int i = 0; i < size; i++) {
            if (oit->index >= instanceSize)
                return;
            leftUnionArray[oit->index] = rightUnionArray[i];

            oit->index++;
        }
    } else {
        int endIndex = oit->index + oit->size;
        const TConstUnionArray& rightUnionArray = node->getConstArray();
        if (! oit->isMatrix) {
            int count = 0;
            for (int i = oit->index; i < endIndex; i++) {
                if (i >= instanceSize)
                    return;

                leftUnionArray[i] = rightUnionArray[count];

                (oit->index)++;
                
                if (node->getType().getObjectSize() > 1)
                    count++;
            }
        } else {
            // constructing a matrix, but from what?
            if (node->isMatrix()) {
                // Matrix from a matrix; oit has the outer matrix, node is the argument matrix.
                // Traverse the outer, potentially bigger matrix, fill in missing pieces with the
                // identity matrix.
                for (int c = 0; c < oit->matrixCols; ++c) {
                    for (int r = 0; r < oit->matrixRows; ++r) {
                        int targetOffset = oit->index + c * oit->matrixRows + r;
                        if (r < node->getType().getMatrixRows() && c < node->getType().getMatrixCols()) {
                            int srcOffset = c * node->getType().getMatrixRows() + r;
                            leftUnionArray[targetOffset] = rightUnionArray[srcOffset];
                        } else if (r == c)
                            leftUnionArray[targetOffset].setDConst(1.0);
                        else
                            leftUnionArray[targetOffset].setDConst(0.0);
                    }
                }
            } else {
                // matrix from vector
                int count = 0;
                int index = oit->index;
                for (int i = index; i < endIndex; i++) {
                    if (i >= instanceSize)
                        return;
                    if (i == index || (i - index) % (oit->matrixRows + 1) == 0 )
                        leftUnionArray[i] = rightUnionArray[count];
                    else 
                        leftUnionArray[i].setDConst(0.0);

                    oit->index++;

                    if (node->getType().getObjectSize() > 1)
                        count++;                
                }
            }
        }
    }
}

bool TIntermediate::parseConstTree(TIntermNode* root, TConstUnionArray unionArray, TOperator constructorType, const TType& t, bool singleConstantParam)
{
    if (root == 0)
        return false;

    TConstTraverser it(unionArray, singleConstantParam, constructorType, t);
    
    it.visitAggregate = ParseAggregate;
    it.visitConstantUnion = ParseConstantUnion;

    root->traverse(&it);
    if (it.error)
        return true;
    else
        return false;
}

} // end namespace glslang
