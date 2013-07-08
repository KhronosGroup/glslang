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

/* Don't use memory.c's replacements, as we clean up properly here */
#undef malloc
#undef free

int TPpContext::InitCPP()
{
    TPpContext::AtomTable* atable = &atomTable;
    // Add various atoms needed by the CPP line scanner:
    bindAtom = LookUpAddString(atable, "bind");
    constAtom = LookUpAddString(atable, "const");
    defaultAtom = LookUpAddString(atable, "default");
    defineAtom = LookUpAddString(atable, "define");
    definedAtom = LookUpAddString(atable, "defined");
    elifAtom = LookUpAddString(atable, "elif");
    elseAtom = LookUpAddString(atable, "else");
    endifAtom = LookUpAddString(atable, "endif");
    ifAtom = LookUpAddString(atable, "if");
    ifdefAtom = LookUpAddString(atable, "ifdef");
    ifndefAtom = LookUpAddString(atable, "ifndef");
    includeAtom = LookUpAddString(atable, "include");
    lineAtom = LookUpAddString(atable, "line");
    pragmaAtom = LookUpAddString(atable, "pragma");
    texunitAtom = LookUpAddString(atable, "texunit");
    undefAtom = LookUpAddString(atable, "undef");
    errorAtom = LookUpAddString(atable, "error");
    __LINE__Atom = LookUpAddString(atable, "__LINE__");
    __FILE__Atom = LookUpAddString(atable, "__FILE__");
    __VERSION__Atom = LookUpAddString(atable, "__VERSION__");
    versionAtom = LookUpAddString(atable, "version");
    coreAtom = LookUpAddString(atable, "core");
    compatibilityAtom = LookUpAddString(atable, "compatibility");
    esAtom = LookUpAddString(atable, "es");
    extensionAtom = LookUpAddString(atable, "extension");
    macros = NewScopeInPool(mem_CreatePool(0, 0));

    return 1;
} // InitCPP

int TPpContext::FreeCPP()
{
    if (macros) {
        mem_FreePool(macros->pool);
        macros = 0;
    }

    return 1;
}

int TPpContext::FinalCPP()
{
    if (ifdepth)
        parseContext.error(parseContext.currentLoc, "missing #endif", "#if", "");
    return 1;
}

int TPpContext::CPPdefine(TPpToken * yylvalpp)
{
    int token, name, args[maxMacroArgs], argc;
    MacroSymbol mac;
    Symbol *symb;
    memset(&mac, 0, sizeof(mac));
    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token != CPP_IDENTIFIER) {
        parseContext.error(yylvalpp->loc, "must be followed by macro name", "#define", "");
        return token;
    }
    name = yylvalpp->atom;
    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token == '(' && !yylvalpp->ival) {
        // gather arguments
        argc = 0;
        do {
            token = currentInput->scan(this, currentInput, yylvalpp);
            if (argc == 0 && token == ')') 
                break;
            if (token != CPP_IDENTIFIER) {
                parseContext.error(yylvalpp->loc, "bad argument", "#define", "");

                return token;
            }
            if (argc < maxMacroArgs)
                args[argc++] = yylvalpp->atom;
            token = currentInput->scan(this, currentInput, yylvalpp);
        } while (token == ',');
        if (token != ')') {            
            parseContext.error(yylvalpp->loc, "missing parenthesis", "#define", "");

            return token;
        }
        mac.argc = argc;
        mac.args = (int*)mem_Alloc(macros->pool, argc * sizeof(int));
        memcpy(mac.args, args, argc * sizeof(int));
        token = currentInput->scan(this, currentInput, yylvalpp);
    }
    mac.body = NewTokenStream(GetAtomString(&atomTable, name), macros->pool);
    while (token != '\n') {
        while (token == '\\') {
            token = currentInput->scan(this, currentInput, yylvalpp);
            if (token == '\n')
                token = currentInput->scan(this, currentInput, yylvalpp);
            else
                RecordToken(mac.body, '\\', yylvalpp);
        }
        RecordToken(mac.body, token, yylvalpp);
        token = currentInput->scan(this, currentInput, yylvalpp);
    };

    symb = LookUpSymbol(macros, name);
    if (symb) {
        if (!symb->details.mac.undef) {
            // already defined -- need to make sure they are identical
            if (symb->details.mac.argc != mac.argc)
                goto error;
            for (argc=0; argc < mac.argc; argc++)
                if (symb->details.mac.args[argc] != mac.args[argc])
                    goto error;
            RewindTokenStream(symb->details.mac.body);
            RewindTokenStream(mac.body);
            do {
                int old_lval, old_token;
                old_token = ReadToken(symb->details.mac.body, yylvalpp);
                old_lval = yylvalpp->ival;
                token = ReadToken(mac.body, yylvalpp);
                if (token != old_token || yylvalpp->ival != old_lval) { 
error:
                    parseContext.error(yylvalpp->loc, "Macro Redefined", "#define", GetStringOfAtom(&atomTable, name));
                    break; 
                }
            } while (token > 0);
        }
        //FreeMacro(&symb->details.mac);
    } else {
        symb = AddSymbol(&yylvalpp->loc, macros, name, MACRO_S);
    }
    symb->details.mac = mac;

    return '\n';
} // CPPdefine

int TPpContext::CPPundef(TPpToken * yylvalpp)
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    Symbol *symb;
    if (token == '\n') {
        parseContext.error(yylvalpp->loc, "must be followed by macro name", "#undef", "");

        return token;
    }
    if (token != CPP_IDENTIFIER) {
        parseContext.error(yylvalpp->loc, "must be followed by macro name", "#undef", "");

        return token;
    }

    symb = LookUpSymbol(macros, yylvalpp->atom);
    if (symb) {
        symb->details.mac.undef = 1;
    }
    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token != '\n')
        parseContext.error(yylvalpp->loc, "can only be followed by a single macro name", "#undef", "");

    return token;
} // CPPundef

/* CPPelse -- skip forward to appropriate spot.  This is actually used
** to skip to a #endif after seeing an #else, AND to skip to a #else,
** #elif, or #endif after a #if/#ifdef/#ifndef/#elif test was false
*/

int TPpContext::CPPelse(int matchelse, TPpToken * yylvalpp)
{
    int atom;
    int depth = 0;
    int token = currentInput->scan(this, currentInput, yylvalpp);

    while (token > 0) {
        if (token != '#') {
            while (token != '\n')
                token = currentInput->scan(this, currentInput, yylvalpp);

            token = currentInput->scan(this, currentInput, yylvalpp);
            continue;
        }

        if ((token = currentInput->scan(this, currentInput, yylvalpp)) != CPP_IDENTIFIER)
            continue;

        atom = yylvalpp->atom;
        if (atom == ifAtom || atom == ifdefAtom || atom == ifndefAtom) {
            depth++; 
            ifdepth++; 
            elsetracker++;
        } else if (atom == endifAtom) {
            elsedepth[elsetracker] = 0;
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
                // found the #else we are looking for
                token = currentInput->scan(this, currentInput, yylvalpp);
                if (token != '\n') {
                    parseContext.warn(yylvalpp->loc, "#else", "unexpected tokens following #else directive - expected a newline", "");
                    while (token != '\n')
                        token = currentInput->scan(this, currentInput, yylvalpp);
                } 
                break;
            } else if (atom == elifAtom) {
                /* we decrement ifdepth here, because CPPif will increment
                * it and we really want to leave it alone */
                if (ifdepth) {
                    --ifdepth;
                    elsedepth[elsetracker] = 0;
                    --elsetracker;
                }

                return CPPif (yylvalpp);
            }
        } else if ((atom == elseAtom) && (!ChkCorrectElseNesting()))
            parseContext.error(yylvalpp->loc, "#else after #else", "#else", "");
    };  // end while

    return token;
}

enum eval_prec {
    MIN_PREC,
    COND, LOGOR, LOGAND, OR, XOR, AND, EQUAL, RELATION, SHIFT, ADD, MUL, UNARY,
    MAX_PREC
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
    int token, prec, (*op)(int, int);
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

int TPpContext::eval(int token, int prec, int *res, int *err, TPpToken * yylvalpp)
{
    int         i, val;
    Symbol      *s;

    if (token == CPP_IDENTIFIER) {
        if (yylvalpp->atom == definedAtom) {
            bool needclose = 0;
            token = currentInput->scan(this, currentInput, yylvalpp);
            if (token == '(') {
                needclose = true;
                token = currentInput->scan(this, currentInput, yylvalpp);
            }
            if (token != CPP_IDENTIFIER) {
                parseContext.error(yylvalpp->loc, "incorrect directive, expected identifier", "preprocessor", "");
                *err = 1;
                *res = 0;

                return token;
            }
            *res = (s = LookUpSymbol(macros, yylvalpp->atom))
                ? !s->details.mac.undef : 0;
            token = currentInput->scan(this, currentInput, yylvalpp);
            if (needclose) {
                if (token != ')') {
                    parseContext.error(yylvalpp->loc, "#else after #else", "", "");
                    *err = 1;
                    *res = 0;

                    return token;
                }
                token = currentInput->scan(this, currentInput, yylvalpp);
            }
        } else {
            int macroReturn = MacroExpand(yylvalpp->atom, yylvalpp, 1);
            if (macroReturn == 0) {
                parseContext.error(yylvalpp->loc, "can't evaluate expression", "preprocessor", "");
                *err = 1;
                *res = 0;

                return token;
            } else {
                if (macroReturn == -1) {
                    if (parseContext.profile == EEsProfile) {
                        if (parseContext.messages & EShMsgRelaxedErrors)
                            parseContext.warn(yylvalpp->loc, "undefined macro in expression not allowed in es profile", "preprocessor", "");
                        else {
                            parseContext.error(yylvalpp->loc, "undefined macro in expression", "preprocessor", "");

                            *err = 1;
                        }
                    }
                }
                token = currentInput->scan(this, currentInput, yylvalpp);

                return eval(token, prec, res, err, yylvalpp);
            }
        }
    } else if (token == CPP_INTCONSTANT) {
        *res = yylvalpp->ival;
        token = currentInput->scan(this, currentInput, yylvalpp);
    } else if (token == '(') {
        token = currentInput->scan(this, currentInput, yylvalpp);
        token = eval(token, MIN_PREC, res, err, yylvalpp);
        if (!*err) {
            if (token != ')') {
                parseContext.error(yylvalpp->loc, "expected ')'", "preprocessor", "");
                *err = 1;
                *res = 0;

                return token;
            }
            token = currentInput->scan(this, currentInput, yylvalpp);
        }
    } else {
        for (i = ALEN(unop) - 1; i >= 0; i--) {
            if (unop[i].token == token)
                break;
        }
        if (i >= 0) {
            token = currentInput->scan(this, currentInput, yylvalpp);
            token = eval(token, UNARY, res, err, yylvalpp);
            *res = unop[i].op(*res);
        } else {
            parseContext.error(yylvalpp->loc, "", "bad expression", "");
            *err = 1;
            *res = 0;

            return token;
        }
    }
    while (!*err) {
        if (token == ')' || token == '\n') 
            break;
        for (i = ALEN(binop) - 1; i >= 0; i--) {
            if (binop[i].token == token)
                break;
        }
        if (i < 0 || binop[i].prec <= prec)
            break;
        val = *res;
        token = currentInput->scan(this, currentInput, yylvalpp);
        token = eval(token, binop[i].prec, res, err, yylvalpp);
        *res = binop[i].op(val, *res);
    }

    return token;
} // eval

int TPpContext::CPPif (TPpToken * yylvalpp) 
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    int res = 0, err = 0;
    elsetracker++;
    if (! ifdepth++)
        ifloc = yylvalpp->loc;
    if (ifdepth > maxIfNesting) {
        parseContext.error(yylvalpp->loc, "maximum nesting depth exceeded", "#if", "");
        return 0;
    }
    token = eval(token, MIN_PREC, &res, &err, yylvalpp);
    if (token != '\n') {
        parseContext.warn(yylvalpp->loc, "unexpected tokens following #if directive - expected a newline", "#if", "");
        while (token != '\n')
            token = currentInput->scan(this, currentInput, yylvalpp);
    } 
    if (!res && !err) {
        token = CPPelse(1, yylvalpp);
    }

    return token;
} // CPPif

int TPpContext::CPPifdef(int defined, TPpToken * yylvalpp)
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    int name = yylvalpp->atom;
    if (++ifdepth > maxIfNesting) {
        parseContext.error(yylvalpp->loc, "maximum nesting depth exceededextension name not specified", "#ifdef", "");
        return 0;
    }
    elsetracker++;
    if (token != CPP_IDENTIFIER) {
        if (defined)
            parseContext.error(yylvalpp->loc, "must be followed by macro name", "#ifdef", "");
        else 
            parseContext.error(yylvalpp->loc, "must be followed by macro name", "#ifndef", "");
    } else {
        Symbol *s = LookUpSymbol(macros, name);
        token = currentInput->scan(this, currentInput, yylvalpp);
        if (token != '\n') {
            parseContext.error(yylvalpp->loc, "unexpected tokens following #ifdef directive - expected a newline", "#ifdef", "");
            while (token != '\n')
                token = currentInput->scan(this, currentInput, yylvalpp);
        }
        if (((s && !s->details.mac.undef) ? 1 : 0) != defined)
            token = CPPelse(1, yylvalpp);
    }
    return token;
} // CPPifdef

// Handle #line
int TPpContext::CPPline(TPpToken * yylvalpp) 
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    if (token == '\n') {
        parseContext.error(yylvalpp->loc, "must by followed by an integral literal", "#line", "");
        return token;
    }
    else if (token == CPP_INTCONSTANT) {
        parseContext.currentLoc.line = atoi(yylvalpp->name);
        token = currentInput->scan(this, currentInput, yylvalpp);

        if (token == CPP_INTCONSTANT) {
            parseContext.currentLoc.string = atoi(yylvalpp->name);
            token = currentInput->scan(this, currentInput, yylvalpp);
            if (token != '\n')
                parseContext.error(parseContext.currentLoc, "cannot be followed by more than two integral literals", "#line", "");
        } else if (token == '\n')

            return token;
        else
            parseContext.error(parseContext.currentLoc, "second argument can only be an integral literal", "#line", "");
    } else
        parseContext.error(parseContext.currentLoc, "first argument can only be an integral literal", "#line", "");

    return token;
}

// Handle #error
int TPpContext::CPPerror(TPpToken * yylvalpp) 
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    std::string message;
    TSourceLoc loc = yylvalpp->loc;

    while (token != '\n') {
        if (token == CPP_INTCONSTANT || token == CPP_UINTCONSTANT ||
            token == CPP_FLOATCONSTANT || token == CPP_DOUBLECONSTANT) {
                message.append(yylvalpp->name);
        } else if (token == CPP_IDENTIFIER || token == CPP_STRCONSTANT) {
            message.append(GetStringOfAtom(&atomTable, yylvalpp->atom));
        } else {
            message.append(GetStringOfAtom(&atomTable, token));
        }
        message.append(" ");
        token = currentInput->scan(this, currentInput, yylvalpp);
    }
    //store this msg into the shader's information log..set the Compile Error flag!!!!
    parseContext.error(loc, message.c_str(), "#error", "");

    return '\n';
}

int TPpContext::CPPpragma(TPpToken * yylvalpp)
{
    char SrcStrName[2];
    char** allTokens;
    int tokenCount = 0;
    int maxTokenCount = 10;
    const char* SrcStr;
    int i;

    int token = currentInput->scan(this, currentInput, yylvalpp);

    if (token=='\n') {
        parseContext.error(yylvalpp->loc, "must be followed by pragma arguments", "#pragma", "");
        return token;
    }

    allTokens = (char**)malloc(sizeof(char*) * maxTokenCount);	

    while (token != '\n') {
        if (tokenCount >= maxTokenCount) {
            maxTokenCount *= 2;
            allTokens = (char**)realloc((char**)allTokens, sizeof(char*) * maxTokenCount);
        }
        switch (token) {
        case CPP_IDENTIFIER:
            SrcStr = GetAtomString(&atomTable, yylvalpp->atom);
            allTokens[tokenCount] = (char*)malloc(strlen(SrcStr) + 1);
            strcpy(allTokens[tokenCount++], SrcStr);
            break;
        case CPP_INTCONSTANT:
        case CPP_UINTCONSTANT:
        case CPP_FLOATCONSTANT:
        case CPP_DOUBLECONSTANT:
            SrcStr = yylvalpp->name;
            allTokens[tokenCount] = (char*)malloc(strlen(SrcStr) + 1);
            strcpy(allTokens[tokenCount++], SrcStr);
            break;
        case EOF:
            parseContext.error(yylvalpp->loc, "directive must end with a newline", "#pragma", "");
            return token;
        default:
            SrcStrName[0] = token;
            SrcStrName[1] = '\0';
            allTokens[tokenCount] = (char*)malloc(2);
            strcpy(allTokens[tokenCount++], SrcStrName);
        }
        token = currentInput->scan(this, currentInput, yylvalpp);
    }

    currentInput->ungetch(this, currentInput, token, yylvalpp);
    parseContext.handlePragma((const char**)allTokens, tokenCount);
    token = currentInput->scan(this, currentInput, yylvalpp);

    for (i = 0; i < tokenCount; ++i) {
        free (allTokens[i]);
    }
    free (allTokens);	

    return token;    
} // CPPpragma

// This is just for error checking: the version and profile are decided before preprocessing starts
int TPpContext::CPPversion(TPpToken * yylvalpp)
{
    int token = currentInput->scan(this, currentInput, yylvalpp);

    if (notAVersionToken)
        parseContext.error(yylvalpp->loc, "must occur before any other statement in the program", "#version", "");

    if (token == '\n') {
        parseContext.error(yylvalpp->loc, "must be followed by version number", "#version", "");

        return token;
    }

    if (token != CPP_INTCONSTANT)
        parseContext.error(yylvalpp->loc, "must be followed by version number", "#version", "");

    yylvalpp->ival = atoi(yylvalpp->name);

    token = currentInput->scan(this, currentInput, yylvalpp);

    if (token == '\n')
        return token;
    else {
        if (yylvalpp->atom != coreAtom &&
            yylvalpp->atom != compatibilityAtom &&
            yylvalpp->atom != esAtom)
            parseContext.error(yylvalpp->loc, "bad profile name; use es, core, or compatibility", "#version", "");

        token = currentInput->scan(this, currentInput, yylvalpp);

        if (token == '\n')
            return token;
        else
            parseContext.error(yylvalpp->loc, "bad tokens following profile -- expected newline", "#version", "");
    }

    return token;
} // CPPversion

int TPpContext::CPPextension(TPpToken * yylvalpp)
{

    int token = currentInput->scan(this, currentInput, yylvalpp);
    char extensionName[80];

    if (token=='\n') {
        parseContext.error(yylvalpp->loc, "extension name not specified", "#extension", "");
        return token;
    }

    if (token != CPP_IDENTIFIER)
        parseContext.error(yylvalpp->loc, "extension name expected", "#extension", "");

    strcpy(extensionName, GetAtomString(&atomTable, yylvalpp->atom));

    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token != ':') {
        parseContext.error(yylvalpp->loc, "':' missing after extension name", "#extension", "");
        return token;
    }

    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token != CPP_IDENTIFIER) {
        parseContext.error(yylvalpp->loc, "behavior for extension not specified", "#extension", "");
        return token;
    }

    parseContext.updateExtensionBehavior(extensionName, GetAtomString(&atomTable, yylvalpp->atom));

    token = currentInput->scan(this, currentInput, yylvalpp);
    if (token == '\n')
        return token;
    else
        parseContext.error(yylvalpp->loc,  "extra tokens -- expected newline", "#extension","");

    return token;
} // CPPextension

int TPpContext::readCPPline(TPpToken * yylvalpp)
{
    int token = currentInput->scan(this, currentInput, yylvalpp);
    bool isVersion = false;

    if (token == CPP_IDENTIFIER) {
        if (yylvalpp->atom == defineAtom) {
            token = CPPdefine(yylvalpp);
        } else if (yylvalpp->atom == elseAtom) {
            if (ChkCorrectElseNesting()) {
                if (! ifdepth) {
                    parseContext.error(yylvalpp->loc, "mismatched statements", "#else", "");
                }
                token = currentInput->scan(this, currentInput, yylvalpp);
                if (token != '\n') {                     
                    parseContext.warn(yylvalpp->loc, "unexpected tokens following #else directive - expected a newline", "#else", "");
                    while (token != '\n')
                        token = currentInput->scan(this, currentInput, yylvalpp);
                }
                token = CPPelse(0, yylvalpp);
            } else {
                parseContext.error(yylvalpp->loc, "#else after a #else", "#else", "");
                ifdepth = 0;
                notAVersionToken = true;
                return 0;
            }
        } else if (yylvalpp->atom == elifAtom) {
            if (! ifdepth) {
                parseContext.error(yylvalpp->loc, "mismatched statements", "#elif", "");
            } 
            // this token is really a dont care, but we still need to eat the tokens
            token = currentInput->scan(this, currentInput, yylvalpp); 
            while (token != '\n')
                token = currentInput->scan(this, currentInput, yylvalpp);
            token = CPPelse(0, yylvalpp);
        } else if (yylvalpp->atom == endifAtom) {
            elsedepth[elsetracker] = 0;
            --elsetracker;
            if (! ifdepth)
                parseContext.error(yylvalpp->loc, "mismatched statements", "#endif", "");
            else
                --ifdepth;
        } else if (yylvalpp->atom == ifAtom) {
            token = CPPif (yylvalpp);
        } else if (yylvalpp->atom == ifdefAtom) {
            token = CPPifdef(1, yylvalpp);
        } else if (yylvalpp->atom == ifndefAtom) {
            token = CPPifdef(0, yylvalpp);
        } else if (yylvalpp->atom == lineAtom) {
            token = CPPline(yylvalpp);
        } else if (yylvalpp->atom == pragmaAtom) {
            token = CPPpragma(yylvalpp);
        } else if (yylvalpp->atom == undefAtom) {
            token = CPPundef(yylvalpp);
        } else if (yylvalpp->atom == errorAtom) {
            token = CPPerror(yylvalpp);
        } else if (yylvalpp->atom == versionAtom) {
            token = CPPversion(yylvalpp);
            isVersion = true;
        } else if (yylvalpp->atom == extensionAtom) {
            token = CPPextension(yylvalpp);
        } else {
            parseContext.error(yylvalpp->loc, "Invalid Directive", "#", GetStringOfAtom(&atomTable, yylvalpp->atom));
        }
    }
    while (token != '\n' && token != 0 && token != EOF) {
        token = currentInput->scan(this, currentInput, yylvalpp);
    }

    notAVersionToken = ! isVersion;

    return token;
} // readCPPline

void TPpContext::FreeMacro(MacroSymbol *s) {
    DeleteTokenStream(s->body);
}

static int eof_scan(TPpContext*, TPpContext::InputSrc* in, TPpToken* yylvalpp) { return -1; }
static void noop(TPpContext*, TPpContext::InputSrc* in, int ch, TPpToken* yylvalpp) { }

void TPpContext::PushEofSrc()
{
    InputSrc *in = (InputSrc*)malloc(sizeof(InputSrc));
    memset(in, 0, sizeof(InputSrc));
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
        free(in);
    }
}

TPpContext::TokenStream* TPpContext::PrescanMacroArg(TokenStream *a, TPpToken * yylvalpp)
{
    int token;
    TokenStream *n;
    RewindTokenStream(a);
    do {
        token = ReadToken(a, yylvalpp);
        if (token == CPP_IDENTIFIER && LookUpSymbol(macros, yylvalpp->atom))
            break;
    } while (token > 0);
    if (token <= 0) return a;
    n = NewTokenStream("macro arg", 0);
    PushEofSrc();
    ReadFromTokenStream(a, 0, 0);
    while ((token = currentInput->scan(this, currentInput, yylvalpp)) > 0) {
        if (token == CPP_IDENTIFIER && MacroExpand(yylvalpp->atom, yylvalpp, 0) == 1)
            continue;
        RecordToken(n, token, yylvalpp);
    }
    PopEofSrc();
    DeleteTokenStream(a);
    return n;
} // PrescanMacroArg

//
// These are called through function pointers
//

/* macro_scan ---
** return the next token for a macro expansion, handling macro args 
*/
int TPpContext::macro_scan(TPpContext* pp, TPpContext::InputSrc* inInput, TPpToken* yylvalpp) 
{
    TPpContext::MacroInputSrc* in = (TPpContext::MacroInputSrc*)inInput;

    int i;
    int token = pp->ReadToken(in->mac->body, yylvalpp);
    if (token == CPP_IDENTIFIER) {
        for (i = in->mac->argc-1; i>=0; i--)
            if (in->mac->args[i] == yylvalpp->atom) 
                break;
        if (i >= 0) {
            pp->ReadFromTokenStream(in->args[i], yylvalpp->atom, 0);

            return pp->currentInput->scan(pp, pp->currentInput, yylvalpp);
        }
    }

    if (token > 0) 
        return token;

    in->mac->busy = 0;
    pp->currentInput = in->base.prev;
    if (in->args) {
        for (i=in->mac->argc-1; i>=0; i--)
            pp->DeleteTokenStream(in->args[i]);
        free(in->args);
    }
    free(in);

    return pp->currentInput->scan(pp, pp->currentInput, yylvalpp);
} // macro_scan

// return a zero, for scanning a macro that was never defined
int TPpContext::zero_scan(TPpContext* pp, InputSrc *inInput, TPpToken* yylvalpp) 
{
    MacroInputSrc* in = (MacroInputSrc*)inInput;

    strcpy(yylvalpp->name, "0");
    yylvalpp->ival = 0;

    // pop input
    pp->currentInput = in->base.prev;
    free(in);

    return CPP_INTCONSTANT;
}

/* MacroExpand
** Check an identifier (atom) to see if it is a macro that should be expanded.
** If it is, push an InputSrc that will produce the appropriate expansion
** and return 1.
** If it is, but undefined, it should expand to 0, push an InputSrc that will 
** expand to 0 and return -1.
** Otherwise, return 0.
*/
int TPpContext::MacroExpand(int atom, TPpToken* yylvalpp, int expandUndef)
{
    Symbol *sym = LookUpSymbol(macros, atom);
    MacroInputSrc *in;
    int i, j, token;
    int depth = 0;

    if (atom == __LINE__Atom) {
        yylvalpp->ival = parseContext.currentLoc.line;
        sprintf(yylvalpp->name, "%d", yylvalpp->ival);
        UngetToken(CPP_INTCONSTANT, yylvalpp);

        return 1;
    }

    if (atom == __FILE__Atom) {
        yylvalpp->ival = parseContext.currentLoc.string;
        sprintf(yylvalpp->name, "%d", yylvalpp->ival);
        UngetToken(CPP_INTCONSTANT, yylvalpp);

        return 1;
    }

    if (atom == __VERSION__Atom) {
        yylvalpp->ival = parseContext.version;
        sprintf(yylvalpp->name, "%d", yylvalpp->ival);
        UngetToken(CPP_INTCONSTANT, yylvalpp);

        return 1;
    }

    // no recursive expansions
    if (sym && sym->details.mac.busy)
        return 0;

    // not expanding of undefined symbols
    if ((! sym || sym->details.mac.undef) && ! expandUndef)
        return 0;

    in = (MacroInputSrc*)malloc(sizeof(*in));
    memset(in, 0, sizeof(*in));
    in->base.line = currentInput->line;
    in->base.name = currentInput->name;

    if ((! sym || sym->details.mac.undef) && expandUndef) {
        // push input
        in->base.scan = zero_scan;
        in->base.prev = currentInput;
        currentInput = &in->base;

        return -1;
    }

    in->base.scan = macro_scan;
    in->mac = &sym->details.mac;
    if (sym->details.mac.args) {
        token = currentInput->scan(this, currentInput, yylvalpp);
        if (token != '(') {
            UngetToken(token, yylvalpp);
            yylvalpp->atom = atom;

            return 0;
        }
        in->args = (TokenStream**)malloc(in->mac->argc * sizeof(TokenStream *));
        for (i = 0; i < in->mac->argc; i++)
            in->args[i] = NewTokenStream("macro arg", 0);
        i = 0;
        j = 0;
        do {
            depth = 0;
            while (1) {
                token = currentInput->scan(this, currentInput, yylvalpp);
                if (token <= 0) {
                    parseContext.error(yylvalpp->loc, "EOF in macro", "preprocessor", GetStringOfAtom(&atomTable, atom));

                    return 1;
                }
                if ((in->mac->argc==0) && (token!=')')) break;
                if (depth == 0 && (token == ',' || token == ')')) break;
                if (token == '(') depth++;
                if (token == ')') depth--;
                RecordToken(in->args[i], token, yylvalpp);
                j=1;
            }
            if (token == ')') {
                if ((in->mac->argc==1) &&j==0)
                    break;
                i++;
                break;
            }
            i++;
        } while (i < in->mac->argc);

        if (i < in->mac->argc)
            parseContext.error(yylvalpp->loc, "Too few args in Macro", "preprocessor", GetStringOfAtom(&atomTable, atom));
        else if (token != ')') {
            depth=0;
            while (token >= 0 && (depth > 0 || token != ')')) {
                if (token == ')')
                    depth--;
                token = currentInput->scan(this, currentInput, yylvalpp);
                if (token == '(')
                    depth++;
            }

            if (token <= 0) {
                parseContext.error(yylvalpp->loc, "EOF in macro", "preprocessor", GetStringOfAtom(&atomTable, atom));

                return 1;
            }
            parseContext.error(yylvalpp->loc, "Too many args in Macro", "preprocessor", GetStringOfAtom(&atomTable, atom));
        }
        for (i = 0; i<in->mac->argc; i++) {
            in->args[i] = PrescanMacroArg(in->args[i], yylvalpp);
        }
    }
#if 0
    printf("  <%s:%d>found macro %s\n", GetAtomString(atable, loc.file),
        loc.line, GetAtomString(atable, atom));
    for (i = 0; i<in->mac->argc; i++) {
        printf("\targ %s = '", GetAtomString(atable, in->mac->args[i]));
        DumpTokenStream(stdout, in->args[i]);
        printf("'\n");
    }
#endif
    /*retain the input source*/
    in->base.prev = currentInput;
    sym->details.mac.busy = 1;
    RewindTokenStream(sym->details.mac.body);
    currentInput = &in->base;

    return 1;
} // MacroExpand

int TPpContext::ChkCorrectElseNesting()
{
    if (elsedepth[elsetracker] == 0) {
        elsedepth[elsetracker] = 1;

        return 1;
    }

    return 0;
}
