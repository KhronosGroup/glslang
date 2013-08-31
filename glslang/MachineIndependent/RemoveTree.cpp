//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
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

#include "../Include/intermediate.h"
#include "RemoveTree.h"

namespace glslang {

//
// Code to recursively delete the intermediate tree.
//

void RemoveSymbol(TIntermSymbol* node, TIntermTraverser* it)
{
	delete node;
}

bool RemoveBinary(bool  /*preVisit*/ , TIntermBinary* node, TIntermTraverser*)
{
	delete node;

	return true;
}

bool RemoveUnary(bool /*preVisit */, TIntermUnary* node, TIntermTraverser*)
{
    delete node;

	return true;
}

bool RemoveAggregate(bool  /*preVisit*/ , TIntermAggregate* node, TIntermTraverser*)
{
	delete node;

	return true;
}

bool RemoveSelection(bool  /*preVisit*/ , TIntermSelection* node, TIntermTraverser*)
{
	delete node;

	return true;
}

bool RemoveSwitch(bool  /*preVisit*/ , TIntermSwitch* node, TIntermTraverser*)
{
	delete node;

	return true;
}

void RemoveConstantUnion(TIntermConstantUnion* node, TIntermTraverser*)
{
	delete node;
}

bool RemoveLoop(bool  /*preVisit*/ , TIntermLoop* node, TIntermTraverser*)
{
	delete node;

    return true;
}

bool RemoveBranch(bool  /*preVisit*/ , TIntermBranch* node, TIntermTraverser*)
{
	delete node;

    return true;
}

//
// Entry point.
//
void RemoveAllTreeNodes(TIntermNode* root)
{
    TIntermTraverser it;

    it.visitSymbol        = RemoveSymbol;
    it.visitConstantUnion = RemoveConstantUnion;
    it.visitBinary        = RemoveBinary;
    it.visitUnary         = RemoveUnary;
    it.visitAggregate     = RemoveAggregate;
    it.visitSelection     = RemoveSelection;
    it.visitLoop          = RemoveLoop;
    it.visitBranch        = RemoveBranch;
    it.visitSwitch        = RemoveSwitch;

	it.preVisit = false;
	it.postVisit = true;

    root->traverse(&it);
}

} // end namespace glslang
