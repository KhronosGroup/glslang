//
//Copyright (C) 2016 Google, Inc.
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
//    Neither the name of Google, Inc., nor the names of its
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
// This holds context specific to the GLSL scanner, which
// sits between the preprocessor scanner and parser.
//

#ifndef HLSLSCANCONTEXT_H_
#define HLSLSCANCONTEXT_H_

#include "../glslang/MachineIndependent/ParseHelper.h"
#include "hlslTokens.h"

namespace glslang {

class TPpContext;
class TPpToken;

struct HlslToken {
    TSourceLoc loc;
    EHlslTokenClass tokenClass;
    bool isType;
    union {
        glslang::TString *string;
        int i;
        unsigned int u;
        bool b;
        double d;
    };
    glslang::TSymbol* symbol;
};

class HlslScanContext {
public:
    HlslScanContext(TParseContextBase& parseContext, TPpContext& ppContext)
        : parseContext(parseContext), ppContext(ppContext), afterType(false), field(false) { }
    virtual ~HlslScanContext() { }

    static void fillInKeywordMap();
    static void deleteKeywordMap();

    void tokenize(HlslToken&);

protected:
    HlslScanContext(HlslScanContext&);
    HlslScanContext& operator=(HlslScanContext&);

    EHlslTokenClass tokenizeClass(HlslToken&);
    EHlslTokenClass tokenizeIdentifier();
    EHlslTokenClass identifierOrType();
    EHlslTokenClass reservedWord();
    EHlslTokenClass identifierOrReserved(bool reserved);
    EHlslTokenClass nonreservedKeyword(int version);

    TParseContextBase& parseContext;
    TPpContext& ppContext;
    bool afterType;           // true if we've recognized a type, so can only be looking for an identifier
    bool field;               // true if we're on a field, right after a '.'
    TSourceLoc loc;
    TPpToken* ppToken;
    HlslToken* parserToken;

    const char* tokenText;
    EHlslTokenClass keyword;
};

} // end namespace glslang

#endif // HLSLSCANCONTEXT_H_
