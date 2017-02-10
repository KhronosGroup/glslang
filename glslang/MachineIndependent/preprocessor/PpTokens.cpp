//
// Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
// Copyright (C) 2013 LunarG, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
/****************************************************************************\
Copyright (c) 2002, NVIDIA Corporation.

NVIDIA Corporation("NVIDIA") supplies this software to you in
consideration of your agreement to the following terms, and your use,
installation, modification or redistribution of this NVIDIA software
constitutes acceptance of these terms.  If you do not agree with these
terms, please do not use, install, modify or redistribute this NVIDIA
software.

In consideration of your agreement to abide by the following terms, and
subject to these terms, NVIDIA grants you a personal, non-exclusive
license, under NVIDIA's copyrights in this original NVIDIA software (the
"NVIDIA Software"), to use, reproduce, modify and redistribute the
NVIDIA Software, with or without modifications, in source and/or binary
forms; provided that if you redistribute the NVIDIA Software, you must
retain the copyright notice of NVIDIA, this notice and the following
text and disclaimers in all such redistributions of the NVIDIA Software.
Neither the name, trademarks, service marks nor logos of NVIDIA
Corporation may be used to endorse or promote products derived from the
NVIDIA Software without specific prior written permission from NVIDIA.
Except as expressly stated in this notice, no other rights or licenses
express or implied, are granted by NVIDIA herein, including but not
limited to any patent rights that may be infringed by your derivative
works or by other works in which the NVIDIA Software may be
incorporated. No hardware is licensed hereunder.

THE NVIDIA SOFTWARE IS BEING PROVIDED ON AN "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION, WARRANTIES OR CONDITIONS OF TITLE,
NON-INFRINGEMENT, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
ITS USE AND OPERATION EITHER ALONE OR IN COMBINATION WITH OTHER
PRODUCTS.

IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT,
INCIDENTAL, EXEMPLARY, CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, LOST PROFITS; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) OR ARISING IN ANY WAY
OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE
NVIDIA SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT,
TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF
NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\****************************************************************************/

//
// For recording and playing back the stream of tokens in a macro definition.
//

#if (defined(_MSC_VER) && _MSC_VER < 1900 /*vs2015*/)
#define _CRT_SECURE_NO_WARNINGS
#define snprintf sprintf_s
#endif

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "PpContext.h"
#include "PpTokens.h"

namespace glslang {

// push onto back of stream
void TPpContext::putSubtoken(TokenStream& stream, int subtoken)
{
    assert((subtoken & ~0xff) == 0);
    stream.data.push_back(static_cast<unsigned char>(subtoken));
}

// get the next token in stream
int TPpContext::getSubtoken(TokenStream& stream)
{
    if (stream.current < stream.data.size())
        return stream.data[stream.current++];
    else
        return EndOfInput;
}

// back up one position in the stream
void TPpContext::ungetSubtoken(TokenStream& stream)
{
    if (stream.current > 0)
        --stream.current;
}

/*
* Add a token to the end of a list for later playback.
*/
void TPpContext::RecordToken(TokenStream& pTok, int token, TPpToken* ppToken)
{
    const char* s;
    char* str = NULL;

    putSubtoken(pTok, token);

    switch (token) {
    case PpAtomIdentifier:
    case PpAtomConstString:
        s = ppToken->name;
        while (*s)
            putSubtoken(pTok, *s++);
        putSubtoken(pTok, 0);
        break;
    case PpAtomConstInt:
    case PpAtomConstUint:
    case PpAtomConstInt64:
    case PpAtomConstUint64:
    case PpAtomConstFloat:
    case PpAtomConstDouble:
#ifdef AMD_EXTENSIONS
    case PpAtomConstFloat16:
#endif
        str = ppToken->name;
        while (*str) {
            putSubtoken(pTok, *str);
            str++;
        }
        putSubtoken(pTok, 0);
        break;
    default:
        break;
    }
}

/*
* Reset a token stream in preparation for reading.
*/
void TPpContext::RewindTokenStream(TokenStream& pTok)
{
    pTok.current = 0;
}

/*
* Read the next token from a token stream (not the source stream, but stream used to hold a tokenized macro).
*/
int TPpContext::ReadToken(TokenStream& pTok, TPpToken *ppToken)
{
    int len;
    int ch;

    int subtoken = getSubtoken(pTok);
    ppToken->loc = parseContext.getCurrentLoc();
    switch (subtoken) {
    case '#':
        // Check for ##, unless the current # is the last character
        if (pTok.current < pTok.data.size()) {
            if (getSubtoken(pTok) == '#') {
                parseContext.requireProfile(ppToken->loc, ~EEsProfile, "token pasting (##)");
                parseContext.profileRequires(ppToken->loc, ~EEsProfile, 130, 0, "token pasting (##)");
                subtoken = PpAtomPaste;
            } else
                ungetSubtoken(pTok);
        }
        break;
    case PpAtomConstString:
    case PpAtomIdentifier:
    case PpAtomConstFloat:
    case PpAtomConstDouble:
#ifdef AMD_EXTENSIONS
    case PpAtomConstFloat16:
#endif
    case PpAtomConstInt:
    case PpAtomConstUint:
    case PpAtomConstInt64:
    case PpAtomConstUint64:
        len = 0;
        ch = getSubtoken(pTok);
        while (ch != 0 && ch != EndOfInput) {
            if (len < MaxTokenLength) {
                ppToken->name[len] = (char)ch;
                len++;
                ch = getSubtoken(pTok);
            } else {
                parseContext.error(ppToken->loc, "token too long", "", "");
                break;
            }
        }
        ppToken->name[len] = 0;

        switch (subtoken) {
        case PpAtomIdentifier:
            break;
        case PpAtomConstString:
            break;
        case PpAtomConstFloat:
        case PpAtomConstDouble:
#ifdef AMD_EXTENSIONS
        case PpAtomConstFloat16:
#endif
            ppToken->dval = atof(ppToken->name);
            break;
        case PpAtomConstInt:
            if (len > 0 && ppToken->name[0] == '0') {
                if (len > 1 && (ppToken->name[1] == 'x' || ppToken->name[1] == 'X'))
                    ppToken->ival = (int)strtol(ppToken->name, 0, 16);
                else
                    ppToken->ival = (int)strtol(ppToken->name, 0, 8);
            } else
                ppToken->ival = atoi(ppToken->name);
            break;
        case PpAtomConstUint:
            if (len > 0 && ppToken->name[0] == '0') {
                if (len > 1 && (ppToken->name[1] == 'x' || ppToken->name[1] == 'X'))
                    ppToken->ival = (int)strtoul(ppToken->name, 0, 16);
                else
                    ppToken->ival = (int)strtoul(ppToken->name, 0, 8);
            } else
                ppToken->ival = (int)strtoul(ppToken->name, 0, 10);
            break;
        case PpAtomConstInt64:
            if (len > 0 && ppToken->name[0] == '0') {
                if (len > 1 && (ppToken->name[1] == 'x' || ppToken->name[1] == 'X'))
                    ppToken->i64val = strtoll(ppToken->name, nullptr, 16);
                else
                    ppToken->i64val = strtoll(ppToken->name, nullptr, 8);
            } else
                ppToken->i64val = atoll(ppToken->name);
            break;
        case PpAtomConstUint64:
            if (len > 0 && ppToken->name[0] == '0') {
                if (len > 1 && (ppToken->name[1] == 'x' || ppToken->name[1] == 'X'))
                    ppToken->i64val = (long long)strtoull(ppToken->name, nullptr, 16);
                else
                    ppToken->i64val = (long long)strtoull(ppToken->name, nullptr, 8);
            } else
                ppToken->i64val = (long long)strtoull(ppToken->name, 0, 10);
            break;
        }
    }

    return subtoken;
}

int TPpContext::tTokenInput::scan(TPpToken* ppToken)
{
    return pp->ReadToken(*tokens, ppToken);
}

// We are pasting if
//   1. we are preceding a pasting operator within this stream
// or
//   2. the entire macro is preceding a pasting operator (lastTokenPastes)
//      and we are also on the last token
bool TPpContext::tTokenInput::peekPasting()
{
    // 1. preceding ##?

    size_t savePos = tokens->current;
    int subtoken;
    // skip white space
    do {
        subtoken = pp->getSubtoken(*tokens);
    } while (subtoken == ' ');
    tokens->current = savePos;
    if (subtoken == PpAtomPaste)
        return true;

    // 2. last token and we've been told after this there will be a ##

    if (! lastTokenPastes)
        return false;
    // Getting here means the last token will be pasted, after this

    // Are we at the last non-whitespace token?
    savePos = tokens->current;
    bool moreTokens = false;
    do {
        subtoken = pp->getSubtoken(*tokens);
        if (subtoken == EndOfInput)
            break;
        if (subtoken != ' ') {
            moreTokens = true;
            break;
        }
    } while (true);
    tokens->current = savePos;

    return !moreTokens;
}

void TPpContext::pushTokenStreamInput(TokenStream& ts, bool prepasting)
{
    pushInput(new tTokenInput(this, &ts, prepasting));
    RewindTokenStream(ts);
}

int TPpContext::tUngotTokenInput::scan(TPpToken* ppToken)
{
    if (done)
        return EndOfInput;

    int ret = token;
    *ppToken = lval;
    done = true;

    return ret;
}

void TPpContext::UngetToken(int token, TPpToken* ppToken)
{
    pushInput(new tUngotTokenInput(this, token, ppToken));
}

} // end namespace glslang
