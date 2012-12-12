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

class TAliveTraverser : public TIntermTraverser {
public:
    TAliveTraverser(TQualifier q) : TIntermTraverser(), found(false), qualifier(q)
    {
        visitSymbol    = AliveSymbol;
        visitSelection = AliveSelection;
        rightToLeft    = true;
    }
    bool wasFound() { return found; }
protected:
    bool found;
    TQualifier qualifier;

    friend void AliveSymbol(TIntermSymbol*, TIntermTraverser*);
    friend bool AliveSelection(bool, TIntermSelection*, TIntermTraverser*);
};

//
// Report whether or not a variable of the given qualifier type
// is guaranteed written.  Not always possible to determine if
// it is written conditionally.
//
// ?? It does not do this well yet, this is just a place holder
// that simply determines if it was reference at all, anywhere.
//
bool QualifierWritten(TIntermNode* node, TQualifier qualifier)
{
    TAliveTraverser it(qualifier);

    if (node)
        node->traverse(&it);

    return it.wasFound();
}

void AliveSymbol(TIntermSymbol* node, TIntermTraverser* it)
{
    TAliveTraverser* lit = static_cast<TAliveTraverser*>(it);

    //
    // If it's what we're looking for, record it.
    //
    if (node->getQualifier() == lit->qualifier)
        lit->found = true;
}

bool AliveSelection(bool preVisit, TIntermSelection* node, TIntermTraverser* it)
{
    TAliveTraverser* lit = static_cast<TAliveTraverser*>(it);

    if (lit->wasFound())
        return false;

    return true;
}
