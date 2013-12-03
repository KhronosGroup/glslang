//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2013 LunarG, Inc.
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
// cpp.c
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "PpContext.h"
#include "PpTokens.h"

namespace glslang {

int TPpContext::InitCPP()
{
    // Add various atoms needed by the CPP line scanner:
    bindAtom = LookUpAddString("bind");
    constAtom = LookUpAddString("const");
    defaultAtom = LookUpAddString("default");
    defineAtom = LookUpAddString("define");
    definedAtom = LookUpAddString("defined");
    elifAtom = LookUpAddString("elif");
    elseAtom = LookUpAddString("else");
    endifAtom = LookUpAddString("endif");
    ifAtom = LookUpAddString("if");
    ifdefAtom = LookUpAddString("ifdef");
    ifndefAtom = LookUpAddString("ifndef");
    includeAtom = LookUpAddString("include");
    lineAtom = LookUpAddString("line");
    pragmaAtom = LookUpAddString("pragma");
    texunitAtom = LookUpAddString("texunit");
    undefAtom = LookUpAddString("undef");
    errorAtom = LookUpAddString("error");
    __LINE__Atom = LookUpAddString("__LINE__");
    __FILE__Atom = LookUpAddString("__FILE__");
    __VERSION__Atom = LookUpAddString("__VERSION__");
    versionAtom = LookUpAddString("version");
    coreAtom = LookUpAddString("core");
    compatibilityAtom = LookUpAddString("compatibility");
    esAtom = LookUpAddString("es");
    extensionAtom = LookUpAddString("extension");
    pool = mem_CreatePool(0, 0);

    return 1;
}

// Handle #define
int TPpContext::CPPdefine(TPpToken* ppToken)
{
    int token, atom, args[maxMacroArgs], argc;
    MacroSymbol mac;
    Symbol *symb;
    token = currentInput->scan(this, currentInput, ppToken);
    if (token != CPP_IDENTIFIER) {
        parseContext.error(ppToken->loc, "must be followed by macro name", "#define", "");
        return token;
    }
    atom = ppToken->atom;
    const char* definedName = GetAtomString(atom);
    if (ppToken->loc.string >= 0) {
        // We are in user code; check for reserved name use:
        parseContext.reservedPpErrorCheck(ppToken->loc, definedName, "#define");
    }
    token = currentInput->scan(this, currentInput, ppToken);
    if (token == '(' && !ppToken->ival) {
        // gather arguments
        argc = 0;
        do {
            token = currentInput->scan(this, currentInput, ppToken);
            if (argc == 0 && token == ')') 
                break;
            if (token != CPP_IDENTIFIER) {
                parseContext.error(ppToken->loc, "bad argument", "#define", "");

                return token;
            }
            // check for duplication
            bool duplicate = false;
            for (int a = 0; a < argc; ++a) {
                if (args[a] == ppToken->atom) {
                    parseContext.error(ppToken->loc, "duplicate macro parameter", "#define", "");
                    duplicate = true;
                    break;
                }
            }
            if (! duplicate) {
                if (argc < maxMacroArgs)
                    args[argc++] = ppToken->atom;
                else
                    parseContext.error(ppToken->loc, "too many macro parameters", "#define", "");                    
            }
            token = currentInput->scan(this, currentInput, ppToken);
        } while (token == ',');
        if (token != ')') {            
            parseContext.error(ppToken->loc, "missing parenthesis", "#define", "");

            return token;
        }
        mac.argc = argc;
        mac.args = (int*)mem_Alloc(pool, argc * sizeof(int));
        memcpy(mac.args, args, argc * sizeof(int));
        token = currentInput->scan(this, currentInput, ppToken);
    }
    TSourceLoc defineLoc = ppToken->loc; // because ppToken is going to go to the next line before we report errors
    mac.body = new TokenStream;
    while (token != '\n') {
        if (token == '\\') {
            parseContext.lineContinuationCheck(ppToken->loc);
            token = currentInput->scan(this, currentInput, ppToken);
            if (token == '\n')
                token = currentInput->scan(this, currentInput, ppToken);
        }
        RecordToken(mac.body, token, ppToken);
        int spaceCandidate = currentInput->getch(this, currentInput, ppToken);
        if (spaceCandidate == ' ' || spaceCandidate == '\t')
            RecordToken(mac.body, ' ', 0);
        else
            currentInput->ungetch(this, currentInput, spaceCandidate, ppToken);
        token = currentInput->scan(this, currentInput, ppToken);
    }

    symb = LookUpSymbol(atom);
    if (symb) {
        if (! symb->mac.undef) {
            // Already defined -- need to make sure they are identical:
            // "Two replacement lists are identical if and only if the preprocessing tokens in both have the same number,
            // ordering, spelling, and white-space separation, where all white-space separations are considered identical."
            if (symb->mac.argc != mac.argc)
                parseContext.error(defineLoc, "Macro redefined; different number of arguments:", "#define", GetAtomString(atom));
            else {
                for (argc=0; argc < mac.argc; argc++) {
                    if (symb->mac.args[argc] != mac.args[argc])
                        parseContext.error(defineLoc, "Macro redefined; different argument names:", "#define", GetAtomString(atom));
                }
                RewindTokenStream(symb->mac.body);
                RewindTokenStream(mac.body);
                int newToken;
                do {
                    int oldToken;
                    TPpToken oldPpToken;
                    TPpToken newPpToken;                    
                    oldToken = ReadToken(symb->mac.body, &oldPpToken);
                    newToken = ReadToken(mac.body, &newPpToken);
                    if (oldToken != newToken || oldPpToken != newPpToken) {
                        parseContext.error(defineLoc, "Macro redefined; different substitutions:", "#define", GetAtomString(atom));
                        break; 
                    }
                } while (newToken > 0);
            }
        }
    } else {
        symb = AddSymbol(atom);
    }
    delete symb->mac.body;
    symb->mac = mac;

    return '\n';
}

// Handle #undef
int TPpContext::CPPundef(TPpToken* ppToken)
{
    int token = currentInput->scan(this, currentInput, ppToken);
    Symbol *symb;
    if (token != CPP_IDENTIFIER) {
        parseContext.error(ppToken->loc, "must be followed by macro name", "#undef", "");

        return token;
    }

    const char* name = GetAtomString(ppToken->atom); // TODO preprocessor simplification: the token text should have been built into the ppToken during currentInput->scan()
    parseContext.reservedPpErrorCheck(ppToken->loc, name, "#undef");

    symb = LookUpSymbol(ppToken->atom);
    if (symb) {
        symb->mac.undef = 1;
    }
    token = currentInput->scan(this, currentInput, ppToken);
    if (token != '\n')
        parseContext.error(ppToken->loc, "can only be followed by a single macro name", "#undef", "");

    return token;
}

// Handle #else
/* Skip forward to appropriate spot.  This is used both
** to skip to a #endif after seeing an #else, AND to skip to a #else,
** #elif, or #endif after a #if/#ifdef/#ifndef/#elif test was false.
*/
int TPpContext::CPPelse(int matchelse, TPpToken* ppToken)
{
    int atom;
    int depth = 0;
    int token = currentInput->scan(this, currentInput, ppToken);

    while (token != EOF) {
        if (token != '#') {
            while (token != '\n' && token != EOF)
                token = currentInput->scan(this, currentInput, ppToken);
            
            if (token == EOF)
                return EOF;

            token = currentInput->scan(this, currentInput, ppToken);
            continue;
        }

        if ((token = currentInput->scan(this, currentInput, ppToken)) != CPP_IDENTIFIER)
            continue;

        atom = ppToken->atom;
        if (atom == ifAtom || atom == ifdefAtom || atom == ifndefAtom) {
            depth++; 
            ifdepth++; 
            elsetracker++;
        } else if (atom == endifAtom) {
            token = extraTokenCheck(atom, ppToken, currentInput->scan(this, currentInput, ppToken));
            elseSeen[elsetracker] = false;
            --elsetracker;
            if (depth == 0) {
                // found the #endif we are looking for
                if (ifdepth) 
                    --ifdepth;
                break;
            }
            --depth;
            --ifdepth;
        } else if (matchelse && depth == 0) {
            if (atom == elseAtom ) {
                token = extraTokenCheck(atom, ppToken, currentInput->scan(this, currentInput, ppToken));
                // found the #else we are looking for
                break;
            } else if (atom == elifAtom) {
                /* we decrement ifdepth here, because CPPif will increment
                * it and we really want to leave it alone */
                if (ifdepth) {
                    --ifdepth;
                    elseSeen[elsetracker] = false;
                    --elsetracker;
                }

                return CPPif(ppToken);
            }
        } else if (atom == elseAtom) {
            if (elseSeen[elsetracker])
                parseContext.error(ppToken->loc, "#else after #else", "#else", "");
            else
                elseSeen[elsetracker] = true;
            token = extraTokenCheck(atom, ppToken, currentInput->scan(this, currentInput, ppToken));
        } else if (atom == elifAtom) {
            if (elseSeen[elsetracker])
                parseContext.error(ppToken->loc, "#elif after #else", "#else", "");
        }
    }

    return token;
}

// Call when there should be no more tokens left on a line.
int TPpContext::extraTokenCheck(int atom, TPpToken* ppToken, int token)
{
    if (token != '\n') {
        static const char* message = "unexpected tokens following directive";

        const char* label;
        if (atom == elseAtom)
            label = "#else";
        else if (atom == elifAtom)
            label = "#elif";
        else if (atom == endifAtom)
            label = "#endif";
        else if (atom == ifAtom)
            label = "#if";
        else if (atom == lineAtom)
            label = "#line";
        else
            label = "";

        if (parseContext.messages & EShMsgRelaxedErrors)
            parseContext.warn(ppToken->loc, message, label, "");
        else
            parseContext.error(ppToken->loc, message, label, "");

        while (token != '\n')
            token = currentInput->scan(this, currentInput, ppToken);
    }

    return token;
}

enum eval_prec {
    MIN_PRECEDENCE,
    COND, LOGOR, LOGAND, OR, XOR, AND, EQUAL, RELATION, SHIFT, ADD, MUL, UNARY,
    MAX_PRECEDENCE
};

namespace {

    int op_logor(int a, int b) { return a || b; }
    int op_logand(int a, int b) { return a && b; }
    int op_or(int a, int b) { return a | b; }
    int op_xor(int a, int b) { return a ^ b; }
    int op_and(int a, int b) { return a & b; }
    int op_eq(int a, int b) { return a == b; }
    int op_ne(int a, int b) { return a != b; }
    int op_ge(int a, int b) { return a >= b; }
    int op_le(int a, int b) { return a <= b; }
    int op_gt(int a, int b) { return a > b; }
    int op_lt(int a, int b) { return a < b; }
    int op_shl(int a, int b) { return a << b; }
    int op_shr(int a, int b) { return a >> b; }
    int op_add(int a, int b) { return a + b; }
    int op_sub(int a, int b) { return a - b; }
    int op_mul(int a, int b) { return a * b; }
    int op_div(int a, int b) { return a / b; }
    int op_mod(int a, int b) { return a % b; }
    int op_pos(int a) { return a; }
    int op_neg(int a) { return -a; }
    int op_cmpl(int a) { return ~a; }
    int op_not(int a) { return !a; }

};

struct Tbinops {
    int token, precedence, (*op)(int, int);
} binop[] = {
    { CPP_OR_OP, LOGOR, op_logor },
    { CPP_AND_OP, LOGAND, op_logand },
    { '|', OR, op_or },
    { '^', XOR, op_xor },
    { '&', AND, op_and },
    { CPP_EQ_OP, EQUAL, op_eq },
    { CPP_NE_OP, EQUAL, op_ne },
    { '>', RELATION, op_gt },
    { CPP_GE_OP, RELATION, op_ge },
    { '<', RELATION, op_lt },
    { CPP_LE_OP, RELATION, op_le },
    { CPP_LEFT_OP, SHIFT, op_shl },
    { CPP_RIGHT_OP, SHIFT, op_shr },
    { '+', ADD, op_add },
    { '-', ADD, op_sub },
    { '*', MUL, op_mul },
    { '/', MUL, op_div },
    { '%', MUL, op_mod },
};

struct tunops {
    int token, (*op)(int);
} unop[] = {
    { '+', op_pos },
    { '-', op_neg },
    { '~', op_cmpl },
    { '!', op_not },
};

#define ALEN(A) (sizeof(A)/sizeof(A[0]))

int TPpContext::eval(int token, int precedence, int& res, bool& err, TPpToken* ppToken)
{
    int         i, val;
    Symbol      *s;

    if (token == CPP_IDENTIFIER) {
        if (ppToken->atom == definedAtom) {
            bool needclose = 0;
            token = currentInput->scan(this, currentInput, ppToken);
            if (token == '(') {
                needclose = true;
                token = currentInput->scan(this, currentInput, ppToken);
            }
            if (token != CPP_IDENTIFIER) {
                parseContext.error(ppToken->loc, "incorrect directive, expected identifier", "preprocessor evaluation", "");
                err = true;
                res = 0;

                return token;
            }
            res = (s = LookUpSymbol(ppToken->atom)) ? !s->mac.undef : 0;
            token = currentInput->scan(this, currentInput, ppToken);
            if (needclose) {
                if (token != ')') {
                    parseContext.error(ppToken->loc, "#else after #else", "preprocessor evaluation", "");
                    err = true;
                    res = 0;

                    return token;
                }
                token = currentInput->scan(this, currentInput, ppToken);
            }
        } else {
            int macroReturn = MacroExpand(ppToken->atom, ppToken, 1);
            if (macroReturn == 0) {
                parseContext.error(ppToken->loc, "can't evaluate expression", "preprocessor evaluation", "");
                err = true;
                res = 0;

                return token;
            } else {
                if (macroReturn == -1) {
                    if (parseContext.profile == EEsProfile) {
                        if (parseContext.messages & EShMsgRelaxedErrors)
                            parseContext.warn(ppToken->loc, "undefined macro in expression not allowed in es profile", "preprocessor evaluation", "");
                        else {
                            parseContext.error(ppToken->loc, "undefined macro in expression", "preprocessor evaluation", "");

                            err = true;
                        }
                    }
                }
                token = currentInput->scan(this, currentInput, ppToken);

                return eval(token, precedence, res, err, ppToken);
            }
        }
    } else if (token == CPP_INTCONSTANT) {
        res = ppToken->ival;
        token = currentInput->scan(this, currentInput, ppToken);
    } else if (token == '(') {
        token = currentInput->scan(this, currentInput, ppToken);
        token = eval(token, MIN_PRECEDENCE, res, err, ppToken);
        if (! err) {
            if (token != ')') {
                parseContext.error(ppToken->loc, "expected ')'", "preprocessor evaluation", "");
                err = true;
                res = 0;

                return token;
            }
            token = currentInput->scan(this, currentInput, ppToken);
        }
    } else {
        for (i = ALEN(unop) - 1; i >= 0; i--) {
            if (unop[i].token == token)
                break;
        }
        if (i >= 0) {
            token = currentInput->scan(this, currentInput, ppToken);
            token = eval(token, UNARY, res, err, ppToken);
            res = unop[i].op(res);
        } else {
            parseContext.error(ppToken->loc, "bad expression", "preprocessor evaluation", "");
            err = true;
            res = 0;

            return token;
        }
    }
    while (! err) {
        if (token == ')' || token == '\n') 
            break;
        for (i = ALEN(binop) - 1; i >= 0; i--) {
            if (binop[i].token == token)
                break;
        }
        if (i < 0 || binop[i].precedence <= precedence)
            break;
        val = res;
        token = currentInput->scan(this, currentInput, ppToken);
        token = eval(token, binop[i].precedence, res, err, ppToken);
        res = binop[i].op(val, res);
    }

    return token;
}

// Handle #if
int TPpContext::CPPif(TPpToken* ppToken) 
{
    int token = currentInput->scan(this, currentInput, ppToken);
    elsetracker++;
    if (! ifdepth++)
        ifloc = ppToken->loc;
    if (ifdepth > maxIfNesting) {
        parseContext.error(ppToken->loc, "maximum nesting depth exceeded", "#if", "");
        return 0;
    }
    int res = 0;
    bool err = false;
    token = eval(token, MIN_PRECEDENCE, res, err, ppToken);
    token = extraTokenCheck(ifAtom, ppToken, token);
    if (!res && !err)
        token = CPPelse(1, ppToken);

    return token;
}

// Handle #ifdef
int TPpContext::CPPifdef(int defined, TPpToken* ppToken)
{
    int token = currentInput->scan(this, currentInput, ppToken);
    int name = ppToken->atom;
    if (++ifdepth > maxIfNesting) {
        parseContext.error(ppToken->loc, "maximum nesting depth exceeded", "#ifdef", "");
        return 0;
    }
    elsetracker++;
    if (token != CPP_IDENTIFIER) {
        if (defined)
            parseContext.error(ppToken->loc, "must be followed by macro name", "#ifdef", "");
        else 
            parseContext.error(ppToken->loc, "must be followed by macro name", "#ifndef", "");
    } else {
        Symbol *s = LookUpSymbol(name);
        token = currentInput->scan(this, currentInput, ppToken);
        if (token != '\n') {
            parseContext.error(ppToken->loc, "unexpected tokens following #ifdef directive - expected a newline", "#ifdef", "");
            while (token != '\n')
                token = currentInput->scan(this, currentInput, ppToken);
        }
        if (((s && !s->mac.undef) ? 1 : 0) != defined)
            token = CPPelse(1, ppToken);
    }

    return token;
}

// Handle #line
int TPpContext::CPPline(TPpToken* ppToken) 
{
    int token = currentInput->scan(this, currentInput, ppToken);
    if (token == '\n') {
        parseContext.error(ppToken->loc, "must by followed by an integral literal", "#line", "");
        return token;
    }

    int lineRes = 0;
    bool lineErr = false;
    token = eval(token, MIN_PRECEDENCE, lineRes, lineErr, ppToken);
    if (! lineErr) {
        if (token == '\n')
            ++lineRes;
        parseContext.setCurrentLine(lineRes);
        if (token != '\n') {
            int fileRes = 0;
            bool fileErr = false;
            token = eval(token, MIN_PRECEDENCE, fileRes, fileErr, ppToken);
            if (! fileErr)
                parseContext.setCurrentString(fileRes);
        }
    }
    token = extraTokenCheck(lineAtom, ppToken, token);

    return token;
}

// Handle #error
int TPpContext::CPPerror(TPpToken* ppToken) 
{
    int token = currentInput->scan(this, currentInput, ppToken);
    std::string message;
    TSourceLoc loc = ppToken->loc;

    while (token != '\n') {
        if (token == CPP_INTCONSTANT || token == CPP_UINTCONSTANT ||
            token == CPP_FLOATCONSTANT || token == CPP_DOUBLECONSTANT) {
                message.append(ppToken->name);
        } else if (token == CPP_IDENTIFIER || token == CPP_STRCONSTANT) {
            message.append(GetAtomString(ppToken->atom));
        } else {
            message.append(GetAtomString(token));
        }
        message.append(" ");
        token = currentInput->scan(this, currentInput, ppToken);
    }
    //store this msg into the shader's information log..set the Compile Error flag!!!!
    parseContext.error(loc, message.c_str(), "#error", "");

    return '\n';
}

// Handle #pragma
int TPpContext::CPPpragma(TPpToken* ppToken)
{
    char SrcStrName[2];
    int tokenCount = 0;
    int maxTokenCount = 10;
    const char* SrcStr;
    TVector<TString> tokens;

    TSourceLoc loc = ppToken->loc;  // because we go to the next line before processing
    int token = currentInput->scan(this, currentInput, ppToken);
    while (token != '\n' && token != EOF) {
        switch (token) {
        case CPP_IDENTIFIER:
            SrcStr = GetAtomString(ppToken->atom);
            tokens.push_back(SrcStr);
            break;
        case CPP_INTCONSTANT:
        case CPP_UINTCONSTANT:
        case CPP_FLOATCONSTANT:
        case CPP_DOUBLECONSTANT:
            SrcStr = ppToken->name;
            tokens.push_back(SrcStr);
            break;
        default:
            SrcStrName[0] = token;
            SrcStrName[1] = '\0';
            tokens.push_back(SrcStrName);
        }
        token = currentInput->scan(this, currentInput, ppToken);
    }

    if (token == EOF)
        parseContext.error(loc, "directive must end with a newline", "#pragma", "");
    else
        parseContext.handlePragma(loc, tokens);

    return token;    
}

// #version: This is just for error checking: the version and profile are decided before preprocessing starts
int TPpContext::CPPversion(TPpToken* ppToken)
{
    int token = currentInput->scan(this, currentInput, ppToken);

    if (errorOnVersion)
        parseContext.error(ppToken->loc, "must occur first in shader", "#version", "");

    if (token == '\n') {
        parseContext.error(ppToken->loc, "must be followed by version number", "#version", "");

        return token;
    }

    if (token != CPP_INTCONSTANT)
        parseContext.error(ppToken->loc, "must be followed by version number", "#version", "");

    ppToken->ival = atoi(ppToken->name);

    token = currentInput->scan(this, currentInput, ppToken);

    if (token == '\n')
        return token;
    else {
        if (ppToken->atom != coreAtom &&
            ppToken->atom != compatibilityAtom &&
            ppToken->atom != esAtom)
            parseContext.error(ppToken->loc, "bad profile name; use es, core, or compatibility", "#version", "");

        token = currentInput->scan(this, currentInput, ppToken);

        if (token == '\n')
            return token;
        else
            parseContext.error(ppToken->loc, "bad tokens following profile -- expected newline", "#version", "");
    }

    return token;
}

// Handle #extension
int TPpContext::CPPextension(TPpToken* ppToken)
{
    int token = currentInput->scan(this, currentInput, ppToken);
    char extensionName[80];

    if (token=='\n') {
        parseContext.error(ppToken->loc, "extension name not specified", "#extension", "");
        return token;
    }

    if (token != CPP_IDENTIFIER)
        parseContext.error(ppToken->loc, "extension name expected", "#extension", "");

    strcpy(extensionName, GetAtomString(ppToken->atom));

    token = currentInput->scan(this, currentInput, ppToken);
    if (token != ':') {
        parseContext.error(ppToken->loc, "':' missing after extension name", "#extension", "");
        return token;
    }

    token = currentInput->scan(this, currentInput, ppToken);
    if (token != CPP_IDENTIFIER) {
        parseContext.error(ppToken->loc, "behavior for extension not specified", "#extension", "");
        return token;
    }

    parseContext.updateExtensionBehavior(extensionName, GetAtomString(ppToken->atom));

    token = currentInput->scan(this, currentInput, ppToken);
    if (token == '\n')
        return token;
    else
        parseContext.error(ppToken->loc,  "extra tokens -- expected newline", "#extension","");

    return token;
}

int TPpContext::readCPPline(TPpToken* ppToken)
{
    int token = currentInput->scan(this, currentInput, ppToken);
    bool isVersion = false;

    if (token == CPP_IDENTIFIER) {
        if (ppToken->atom == defineAtom) {
            token = CPPdefine(ppToken);
        } else if (ppToken->atom == elseAtom) {
            if (! elsetracker[elseSeen]) {
                elsetracker[elseSeen] = true;
                if (! ifdepth)
                    parseContext.error(ppToken->loc, "mismatched statements", "#else", "");
                token = extraTokenCheck(elseAtom, ppToken, currentInput->scan(this, currentInput, ppToken));
                token = CPPelse(0, ppToken);
            } else {
                parseContext.error(ppToken->loc, "#else after a #else", "#else", "");
                ifdepth = 0;
                return 0;
            }
        } else if (ppToken->atom == elifAtom) {
            if (! ifdepth)
                parseContext.error(ppToken->loc, "mismatched statements", "#elif", "");
            // this token is really a dont care, but we still need to eat the tokens
            token = currentInput->scan(this, currentInput, ppToken); 
            while (token != '\n')
                token = currentInput->scan(this, currentInput, ppToken);
            token = CPPelse(0, ppToken);
        } else if (ppToken->atom == endifAtom) {
            elseSeen[elsetracker] = false;
            --elsetracker;
            if (! ifdepth)
                parseContext.error(ppToken->loc, "mismatched statements", "#endif", "");
            else
                --ifdepth;
            token = extraTokenCheck(endifAtom, ppToken, currentInput->scan(this, currentInput, ppToken));
        } else if (ppToken->atom == ifAtom) {
            token = CPPif (ppToken);
        } else if (ppToken->atom == ifdefAtom) {
            token = CPPifdef(1, ppToken);
        } else if (ppToken->atom == ifndefAtom) {
            token = CPPifdef(0, ppToken);
        } else if (ppToken->atom == lineAtom) {
            token = CPPline(ppToken);
        } else if (ppToken->atom == pragmaAtom) {
            token = CPPpragma(ppToken);
        } else if (ppToken->atom == undefAtom) {
            token = CPPundef(ppToken);
        } else if (ppToken->atom == errorAtom) {
            token = CPPerror(ppToken);
        } else if (ppToken->atom == versionAtom) {
            token = CPPversion(ppToken);
            isVersion = true;
        } else if (ppToken->atom == extensionAtom) {
            token = CPPextension(ppToken);
        } else {
            parseContext.error(ppToken->loc, "invalid directive:", "#", GetAtomString(ppToken->atom));
        }
    } else if (token != '\n' && token > 0)
        parseContext.error(ppToken->loc, "invalid directive", "#", "");

    while (token != '\n' && token != 0 && token != EOF)
        token = currentInput->scan(this, currentInput, ppToken);

    return token;
}

int eof_scan(TPpContext*, TPpContext::InputSrc* in, TPpToken* ppToken) { return -1; }
void noop(TPpContext*, TPpContext::InputSrc* in, int ch, TPpToken* ppToken) { }

void TPpContext::PushEofSrc()
{
    InputSrc *in = new InputSrc;
    in->scan = eof_scan;
    in->getch = eof_scan;
    in->ungetch = noop;
    in->prev = currentInput;
    currentInput = in;
}

void TPpContext::PopEofSrc()
{
    if (currentInput->scan == eof_scan) {
        InputSrc *in = currentInput;
        currentInput = in->prev;
        delete in;
    }
}

TPpContext::TokenStream* TPpContext::PrescanMacroArg(TokenStream *a, TPpToken* ppToken)
{
    int token;
    TokenStream *n;
    RewindTokenStream(a);
    do {
        token = ReadToken(a, ppToken);
        if (token == CPP_IDENTIFIER && LookUpSymbol(ppToken->atom))
            break;
    } while (token != EOF);
    if (token == EOF)
        return a;
    n = new TokenStream;
    PushEofSrc();
    ReadFromTokenStream(a, 0, 0);
    while ((token = currentInput->scan(this, currentInput, ppToken)) > 0) {
        if (token == CPP_IDENTIFIER && MacroExpand(ppToken->atom, ppToken, 0) == 1)
            continue;
        RecordToken(n, token, ppToken);
    }
    PopEofSrc();
    delete a;

    return n;
}

//
// These are called through function pointers
//

/* 
** return the next token for a macro expansion, handling macro args 
*/
int TPpContext::macro_scan(TPpContext* pp, InputSrc* inInput, TPpToken* ppToken) 
{
    MacroInputSrc* in = (TPpContext::MacroInputSrc*)inInput;

    int i;
    int token;
    do {
        token = pp->ReadToken(in->mac->body, ppToken);
    } while (token == ' ');  // handle white space in macro
    // TODO: preprocessor:  properly handle whitespace (or lack of it) between tokens when expanding
    if (token == CPP_IDENTIFIER) {
        for (i = in->mac->argc-1; i>=0; i--)
            if (in->mac->args[i] == ppToken->atom) 
                break;
        if (i >= 0) {
            pp->ReadFromTokenStream(in->args[i], ppToken->atom, 0);

            return pp->currentInput->scan(pp, pp->currentInput, ppToken);
        }
    }

    if (token != EOF) 
        return token;

    in->mac->busy = 0;
    pp->currentInput = in->prev;
    delete in;

    return pp->currentInput->scan(pp, pp->currentInput, ppToken);
}

// return a zero, for scanning a macro that was never defined
int TPpContext::zero_scan(TPpContext* pp, InputSrc *inInput, TPpToken* ppToken) 
{
    MacroInputSrc* in = (MacroInputSrc*)inInput;

    strcpy(ppToken->name, "0");
    ppToken->ival = 0;

    // pop input
    pp->currentInput = in->prev;
    delete in;

    return CPP_INTCONSTANT;
}

/*
** Check an identifier (atom) to see if it is a macro that should be expanded.
** If it is, push an InputSrc that will produce the appropriate expansion
** and return 1.
** If it is, but undefined, it should expand to 0, push an InputSrc that will 
** expand to 0 and return -1.
** Otherwise, return 0.
*/
int TPpContext::MacroExpand(int atom, TPpToken* ppToken, int expandUndef)
{
    Symbol *sym = LookUpSymbol(atom);
    MacroInputSrc *in;
    int token;
    int depth = 0;

    if (atom == __LINE__Atom) {
        ppToken->ival = parseContext.getCurrentLoc().line;
        sprintf(ppToken->name, "%d", ppToken->ival);
        UngetToken(CPP_INTCONSTANT, ppToken);

        return 1;
    }

    if (atom == __FILE__Atom) {
        ppToken->ival = parseContext.getCurrentLoc().string;
        sprintf(ppToken->name, "%d", ppToken->ival);
        UngetToken(CPP_INTCONSTANT, ppToken);

        return 1;
    }

    if (atom == __VERSION__Atom) {
        ppToken->ival = parseContext.version;
        sprintf(ppToken->name, "%d", ppToken->ival);
        UngetToken(CPP_INTCONSTANT, ppToken);

        return 1;
    }

    // no recursive expansions
    if (sym && sym->mac.busy)
        return 0;

    // not expanding of undefined symbols
    if ((! sym || sym->mac.undef) && ! expandUndef)
        return 0;

    in = new MacroInputSrc;

    if ((! sym || sym->mac.undef) && expandUndef) {
        // push input
        in->scan = zero_scan;
        in->prev = currentInput;
        currentInput = in;

        return -1;
    }

    TSourceLoc loc = ppToken->loc;  // in case we go to the next line before discovering the error
    in->scan = macro_scan;
    in->mac = &sym->mac;
    if (sym->mac.args) {
        token = currentInput->scan(this, currentInput, ppToken);
        if (token != '(') {
            UngetToken(token, ppToken);
            ppToken->atom = atom;

            return 0;
        }
        in->args.resize(in->mac->argc);
        for (int i = 0; i < in->mac->argc; i++)
            in->args[i] = new TokenStream;
        int arg = 0;
        bool tokenRecorded = false;
        do {
            depth = 0;
            while (1) {
                token = currentInput->scan(this, currentInput, ppToken);
                if (token <= 0) {
                    parseContext.error(loc, "EOF in macro", "macro expansion", GetAtomString(atom));
                    return 1;
                }
                if (token == '\n') {
                    // TODO: Preprocessor functionality:  Correctly handle new line and escaped new line, for expansions that are both in and not in another preprocessor directive

                    //if (in a pp line) {
                    //    parseContext.error(loc, "missing ')':", "macro expansion", GetAtomString(atom));
                    //    return 1;
                    //}
                    continue;
                }
                if (token == '#') {
                    parseContext.error(ppToken->loc, "unexpected '#'", "macro expansion", GetAtomString(atom));
                    return 1;
                }
                if (in->mac->argc == 0 && token != ')')
                    break;
                if (depth == 0 && (token == ',' || token == ')'))
                    break;
                if (token == '(')
                    depth++;
                if (token == ')')
                    depth--;
                RecordToken(in->args[arg], token, ppToken);
                tokenRecorded = true;
            }
            if (token == ')') {
                if (in->mac->argc == 1 && tokenRecorded == 0)
                    break;
                arg++;
                break;
            }
            arg++;
        } while (arg < in->mac->argc);

        if (arg < in->mac->argc)
            parseContext.error(loc, "Too few args in Macro", "macro expansion", GetAtomString(atom));
        else if (token != ')') {
            depth=0;
            while (token >= 0 && (depth > 0 || token != ')')) {
                if (token == ')')
                    depth--;
                token = currentInput->scan(this, currentInput, ppToken);
                if (token == '(')
                    depth++;
            }

            if (token <= 0) {
                parseContext.error(loc, "EOF in macro", "macro expansion", GetAtomString(atom));
                return 1;
            }
            parseContext.error(loc, "Too many args in macro", "macro expansion", GetAtomString(atom));
        }
        for (int i = 0; i < in->mac->argc; i++)
            in->args[i] = PrescanMacroArg(in->args[i], ppToken);
    }

    /*retain the input source*/
    in->prev = currentInput;
    sym->mac.busy = 1;
    RewindTokenStream(sym->mac.body);
    currentInput = in;

    return 1;
}

} // end namespace glslang