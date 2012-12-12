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

#include "../Include/intermediate.h"

//
// Traverse the intermediate representation tree, and
// call a node type specific function for each node.
// Done recursively through the member function Traverse().
// Node types can be skipped if their function to call is 0,
// but their subtree will still be traversed.
// Nodes with children can have their whole subtree skipped
// if preVisit is turned on and the type specific function
// returns false.
//
// preVisit, postVisit, and rightToLeft control what order
// nodes are visited in.
//

//
// Traversal functions for terminals are straighforward....
//
void TIntermSymbol::traverse(TIntermTraverser* it)
{
    if (it->visitSymbol)
        it->visitSymbol(this, it);
}

void TIntermConstantUnion::traverse(TIntermTraverser* it)
{
    if (it->visitConstantUnion)
        it->visitConstantUnion(this, it);
}

//
// Traverse a binary node.
//
void TIntermBinary::traverse(TIntermTraverser* it)
{
    bool visit = true;

    //
    // visit the node before children if pre-visiting.
    //
    if (it->preVisit && it->visitBinary)
        visit = it->visitBinary(true, this, it);
    
    //
    // Visit the children, in the right order.
    //
    if (visit) {
        ++it->depth;
        if (it->rightToLeft) {
            if (right)
                right->traverse(it);
            if (left)
                left->traverse(it);
        } else {
            if (left)
                left->traverse(it);
            if (right)
                right->traverse(it);
        }
        --it->depth;
    }

    //
    // Visit the node after the children, if requested and the traversal
    // hasn't been cancelled yet.
    //
    if (visit && it->postVisit && it->visitBinary)
        it->visitBinary(false, this, it);
}

//
// Traverse a unary node.  Same comments in binary node apply here.
//
void TIntermUnary::traverse(TIntermTraverser* it)
{
    bool visit = true;

    if (it->preVisit && it->visitUnary)
        visit = it->visitUnary(true, this, it);

    if (visit) {
        ++it->depth;
        operand->traverse(it);
        --it->depth;
    }
    
    if (visit && it->postVisit && it->visitUnary)
        it->visitUnary(false, this, it);
}

//
// Traverse an aggregate node.  Same comments in binary node apply here.
//
void TIntermAggregate::traverse(TIntermTraverser* it)
{
    bool visit = true;
    
    if (it->preVisit && it->visitAggregate)
        visit = it->visitAggregate(true, this, it);
    
    if (visit) {
        ++it->depth;

        TIntermSequence::iterator sit;
        if (it->rightToLeft) {
            sit = sequence.end();
            while (sit != sequence.begin()) {
                --sit;
                (*sit)->traverse(it);
            }
        } else {
            for (sit = sequence.begin(); sit != sequence.end(); ++sit)
                (*sit)->traverse(it);
        }
        
        --it->depth;
    }

    if (visit && it->postVisit && it->visitAggregate)
        it->visitAggregate(false, this, it);
}

//
// Traverse a selection node.  Same comments in binary node apply here.
//
void TIntermSelection::traverse(TIntermTraverser* it)
{
    bool visit = true;

    if (it->preVisit && it->visitSelection)
        visit = it->visitSelection(true, this, it);
    
    if (visit) {
        ++it->depth;
        if (it->rightToLeft) {
            if (falseBlock)
                falseBlock->traverse(it);
			if (trueBlock)
				trueBlock->traverse(it);
            condition->traverse(it);
        } else {
            condition->traverse(it);
			if (trueBlock)
				trueBlock->traverse(it);
            if (falseBlock)
                falseBlock->traverse(it);
        }
        --it->depth;
    }

    if (visit && it->postVisit && it->visitSelection)
        it->visitSelection(false, this, it);
}

//
// Traverse a loop node.  Same comments in binary node apply here.
//
void TIntermLoop::traverse(TIntermTraverser* it)
{
    bool visit = true;

    if (it->preVisit && it->visitLoop)
        visit = it->visitLoop(true, this, it);
    
    if (visit) {
        ++it->depth;
        if (it->rightToLeft) {
            if (terminal)
                terminal->traverse(it);
            if (body)
                body->traverse(it);
			if (test)
				test->traverse(it);
        } else {
			if (test)
				test->traverse(it);
            if (body)
                body->traverse(it);
            if (terminal)
                terminal->traverse(it);
        }
        --it->depth;
    }

    if (visit && it->postVisit && it->visitLoop)
        it->visitLoop(false, this, it);
}

//
// Traverse a branch node.  Same comments in binary node apply here.
//
void TIntermBranch::traverse(TIntermTraverser* it)
{
    bool visit = true;

    if (it->preVisit && it->visitBranch)
        visit = it->visitBranch(true, this, it);
    
    if (visit && expression) {
        ++it->depth;
        expression->traverse(it);
        --it->depth;
    }

    if (visit && it->postVisit && it->visitBranch)
        it->visitBranch(false, this, it);
}

