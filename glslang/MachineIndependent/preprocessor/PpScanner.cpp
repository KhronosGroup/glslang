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
// scanner.c
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PpContext.h"
#include "PpTokens.h"
#include "Scan.h"

namespace glslang {

int TPpContext::InitScanner(TPpContext *cpp)
{
    // Add various atoms needed by the CPP line scanner:
    if (!InitCPP())
        return 0;

    mostRecentToken = 0;
    currentInput = 0;
    previous_token = '\n';

    return 1;
}

int TPpContext::sourceGetCh(TPpContext* pp, StringInputSrc *in)
{
    int ch = in->input->get();

    if (ch == EOF)
        delete in;

    return ch;
}

void TPpContext::sourceUngetCh(TPpContext* pp, StringInputSrc *in, int ch, TPpToken *type)
{
    in->input->unget();
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Floating point constants: /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*
* lFloatConst() - Scan a single- or double-precision floating point constant.  Assumes that the scanner
*         has seen at least one digit, followed by either a decimal '.' or the
*         letter 'e', or a precision ending (e.g., F or LF).
*/

int TPpContext::lFloatConst(char* str, int len, int ch, TPpToken* ppToken)
{
    bool HasDecimalOrExponent = false;
    int declen, exp, ExpSign;
    int str_len;
    int isDouble = 0;

    declen = 0;
    exp = 0;

    str_len=len;
    if (ch == '.') {
        HasDecimalOrExponent = true;
        str[len++]=ch;
        ch = currentInput->getch(this, currentInput, ppToken);
        while (ch >= '0' && ch <= '9') {
            if (len < TPpToken::maxTokenLength) {
                declen++;
                if (len > 0 || ch != '0') {
                    str[len] = ch;
                    len++;str_len++;
                }
                ch = currentInput->getch(this, currentInput, ppToken);
            } else {
                parseContext.error(ppToken->loc, "float literal too long", "", "");
                len = 1,str_len=1;
            }
        }
    }

    // Exponent:

    if (ch == 'e' || ch == 'E') {
        HasDecimalOrExponent = true;
        if (len >= TPpToken::maxTokenLength) {
            parseContext.error(ppToken->loc, "float literal too long", "", "");
            len = 1,str_len=1;
        } else {
            ExpSign = 1;
            str[len++]=ch;
            ch = currentInput->getch(this, currentInput, ppToken);
            if (ch == '+') {
                str[len++]=ch;  
                ch = currentInput->getch(this, currentInput, ppToken);
            } else if (ch == '-') {
                ExpSign = -1;
                str[len++]=ch;
                ch = currentInput->getch(this, currentInput, ppToken);
            }
            if (ch >= '0' && ch <= '9') {
                while (ch >= '0' && ch <= '9') {
                    if (len < TPpToken::maxTokenLength) {
                        exp = exp*10 + ch - '0';
                        str[len++]=ch;
                        ch = currentInput->getch(this, currentInput, ppToken);
                    } else {
                        parseContext.error(ppToken->loc, "float literal too long", "", "");
                        len = 1,str_len=1;
                    }
                }
            } else {
                parseContext.error(ppToken->loc, "bad character in float exponent", "", "");
            }
            exp *= ExpSign;
        }
    }

    if (len == 0) {
        ppToken->dval = 0.0;
        strcpy(str, "0.0");
    } else {
        if (ch == 'l' || ch == 'L') {
            parseContext.doubleCheck(ppToken->loc, "double floating-point suffix");
            if (! HasDecimalOrExponent)
                parseContext.error(ppToken->loc, "float literal needs a decimal point or exponent", "", "");
            int ch2 = currentInput->getch(this, currentInput, ppToken);
            if (ch2 != 'f' && ch2 != 'F') {
                currentInput->ungetch(this, currentInput, ch2, ppToken);
                currentInput->ungetch(this, currentInput, ch, ppToken);
            } else {
                if (len < TPpToken::maxTokenLength) {
                    str[len++] = ch;
                    str[len++] = ch2;
                    isDouble = 1;
                } else {
                    parseContext.error(ppToken->loc, "float literal too long", "", "");
                    len = 1,str_len=1;
                }
            }
        } else if (ch == 'f' || ch == 'F') {
            parseContext.profileRequires(ppToken->loc,  EEsProfile, 300, 0, "floating-point suffix");
            parseContext.profileRequires(ppToken->loc, ~EEsProfile, 120, 0, "floating-point suffix");
            if (! HasDecimalOrExponent)
                parseContext.error(ppToken->loc, "float literal needs a decimal point or exponent", "", "");
            if (len < TPpToken::maxTokenLength)
                str[len++] = ch;
            else {
                parseContext.error(ppToken->loc, "float literal too long", "", "");
                len = 1,str_len=1;
            }
        } else 
            currentInput->ungetch(this, currentInput, ch, ppToken);

        str[len]='\0';

        ppToken->dval = strtod(str, 0);
    }
    // Suffix:
    strcpy(ppToken->name, str);

    if (isDouble)
        return CPP_DOUBLECONSTANT;
    else
        return CPP_FLOATCONSTANT;
}

//
// Scanner used to tokenize source stream.
//
int TPpContext::sourceScan(TPpContext* pp, InputSrc*, TPpToken* ppToken)
{
    char tokenText[TPpToken::maxTokenLength + 1];
    int AlreadyComplained = 0;
    int len, ch, ii;
    unsigned ival = 0;

    ppToken->ival = 0;
    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
    for (;;) {
        while (ch == ' ' || ch == '\t' || ch == '\r') {
            ppToken->ival = 1;
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
        }

        ppToken->loc = pp->parseContext.getCurrentLoc();
        len = 0;
        switch (ch) {
        default:
            return ch; // Single character token
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z': case '_':
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z': case '\\' :
            do {
                if (ch == '\\') {
                    // escaped character
                    pp->parseContext.lineContinuationCheck(ppToken->loc);
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    if (ch == '\r' || ch == '\n') {
                        int nextch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                        if (ch == '\r' && nextch == '\n')
                            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                        else
                            ch = nextch;
                    } else
                        pp->parseContext.error(ppToken->loc, "can only escape newlines", "\\", "");
                } else if (len < TPpToken::maxTokenLength) {
                    tokenText[len++] = ch;
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);					
                } else {
                    if (! AlreadyComplained) {
                        pp->parseContext.error(ppToken->loc, "name too long", "", "");
                        AlreadyComplained = 1;
                    }
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);					
                }
            } while ((ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z') ||
                (ch >= '0' && ch <= '9') ||
                ch == '_' ||
                ch == '\\');

            // line continuation with no token before or after makes len == 0, and need to start over skipping white space, etc.
            if (len == 0)
                continue;

            tokenText[len] = '\0';
            pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
            ppToken->atom = pp->LookUpAddString(tokenText);

            return CPP_IDENTIFIER;
        case '0':
            ppToken->name[len++] = ch;
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == 'x' || ch == 'X') {
                // must be hexidecimal

                bool isUnsigned = false;
                ppToken->name[len++] = ch;
                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                if ((ch >= '0' && ch <= '9') ||
                    (ch >= 'A' && ch <= 'F') ||
                    (ch >= 'a' && ch <= 'f'))
                {
                    ival = 0;
                    do {
                        if (ival <= 0x0fffffff) {
                            ppToken->name[len++] = ch;
                            if (ch >= '0' && ch <= '9') {
                                ii = ch - '0';
                            } else if (ch >= 'A' && ch <= 'F') {
                                ii = ch - 'A' + 10;
                            } else if (ch >= 'a' && ch <= 'f') {
                                ii = ch - 'a' + 10;
                            } else
                                pp->parseContext.error(ppToken->loc, "bad digit in hexidecimal literal", "", "");
                            ival = (ival << 4) | ii;
                        } else {
                            if (! AlreadyComplained) {
                                pp->parseContext.error(ppToken->loc, "hexidecimal literal too big", "", "");
                                AlreadyComplained = 1;
                            }
                            ival = 0xffffffff;
                        }
                        ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    } while ((ch >= '0' && ch <= '9') ||
                        (ch >= 'A' && ch <= 'F') ||
                        (ch >= 'a' && ch <= 'f'));
                } else {
                    pp->parseContext.error(ppToken->loc, "bad digit in hexidecimal literal", "", "");
                }
                if (ch == 'u' || ch == 'U') {
                    if (len < TPpToken::maxTokenLength)
                        ppToken->name[len++] = ch;
                    isUnsigned = true;
                } else
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                ppToken->name[len] = '\0';
                ppToken->ival = (int)ival;

                if (isUnsigned)
                    return CPP_UINTCONSTANT;
                else
                    return CPP_INTCONSTANT;
            } else {
                // could be octal integer or floating point, speculative pursue octal until it must be floating point

                bool isUnsigned = false;
                bool octalOverflow = false;
                bool nonOctal = false;
                ival = 0;

                // see how much octal-like stuff we can read
                while (ch >= '0' && ch <= '7') {
                    if (len < TPpToken::maxTokenLength)
                        ppToken->name[len++] = ch;
                    else if (! AlreadyComplained) {
                        pp->parseContext.error(ppToken->loc, "numeric literal too long", "", "");
                        AlreadyComplained = 1;
                    }
                    if (ival <= 0x1fffffff) {
                        ii = ch - '0';
                        ival = (ival << 3) | ii;
                    } else
                        octalOverflow = true;
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                }

                // could be part of a float...
                if (ch == '8' || ch == '9') {
                    nonOctal = true;
                    do {
                        if (len < TPpToken::maxTokenLength)
                            ppToken->name[len++] = ch;
                        else if (! AlreadyComplained) {
                            pp->parseContext.error(ppToken->loc, "numeric literal too long", "", "");
                            AlreadyComplained = 1;
                        }
                        ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    } while (ch >= '0' && ch <= '9');
                }
                if (ch == '.' || ch == 'e' || ch == 'f' || ch == 'E' || ch == 'F' || ch == 'l' || ch == 'L') 
                    return pp->lFloatConst(ppToken->name, len, ch, ppToken);
                
                // wasn't a float, so must be octal...
                if (nonOctal)
                    pp->parseContext.error(ppToken->loc, "octal literal digit too large", "", "");

                if (ch == 'u' || ch == 'U') {
                    if (len < TPpToken::maxTokenLength)
                        ppToken->name[len++] = ch;
                    isUnsigned = true;
                } else
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                ppToken->name[len] = '\0';

                if (octalOverflow)
                    pp->parseContext.error(ppToken->loc, "octal literal too big", "", "");

                ppToken->ival = (int)ival;

                if (isUnsigned)
                    return CPP_UINTCONSTANT;
                else
                    return CPP_INTCONSTANT;
            }
            break;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            // can't be hexidecimal or octal, is either decimal or floating point

            do {
                if (len < TPpToken::maxTokenLength)
                    ppToken->name[len++] = ch;
                else if (! AlreadyComplained) {
                    pp->parseContext.error(ppToken->loc, "numeric literal too long", "", "");
                    AlreadyComplained = 1;
                }
                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            } while (ch >= '0' && ch <= '9');
            if (ch == '.' || ch == 'e' || ch == 'f' || ch == 'E' || ch == 'F' || ch == 'l' || ch == 'L') {
                return pp->lFloatConst(ppToken->name, len, ch, ppToken);
            } else {
                // Finish handling signed and unsigned integers
                int numericLen = len;
                int uint = 0;
                if (ch == 'u' || ch == 'U') {
                    if (len < TPpToken::maxTokenLength)
                        ppToken->name[len++] = ch;
                    uint = 1;
                } else
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);

                ppToken->name[len] = '\0';				
                ival = 0;
                for (ii = 0; ii < numericLen; ii++) {
                    ch = ppToken->name[ii] - '0';
                    if ((ival > 429496729) || (ival == 429496729 && ch >= 6)) {
                        pp->parseContext.error(ppToken->loc, "numeric literal too big", "", "");
                        ival = -1;
                        break;
                    } else
                        ival = ival * 10 + ch;
                }
                ppToken->ival = (int)ival;

                if (uint)
                    return CPP_UINTCONSTANT;
                else
                    return CPP_INTCONSTANT;
            }
            break;
        case '-':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '-') {
                return CPP_DEC_OP;
            } else if (ch == '=') {
                return CPP_SUB_ASSIGN;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '-';
            }
        case '+':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '+') {
                return CPP_INC_OP;
            } else if (ch == '=') {
                return CPP_ADD_ASSIGN;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '+';
            }
        case '*':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '=') {
                return CPP_MUL_ASSIGN;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '*';
            }
        case '%':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '=') {
                return CPP_MOD_ASSIGN;
            } else if (ch == '>'){
                return CPP_RIGHT_BRACE;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '%';
            }
        case ':':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '>') {
                return CPP_RIGHT_BRACKET;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return ':';
            }
        case '^':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '^') {
                return CPP_XOR_OP;
            } else {
                if (ch == '=')
                    return CPP_XOR_ASSIGN;
                else{
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return '^';
                }
            }

        case '=':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '=') {
                return CPP_EQ_OP;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '=';
            }
        case '!':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '=') {
                return CPP_NE_OP;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '!';
            }
        case '|':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '|') {
                return CPP_OR_OP;
            } else {
                if (ch == '=')
                    return CPP_OR_ASSIGN;
                else{
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return '|';
                }
            }
        case '&':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '&') {
                return CPP_AND_OP;
            } else {
                if (ch == '=')
                    return CPP_AND_ASSIGN;
                else{
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return '&';
                }
            }
        case '<':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '<') {
                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                if (ch == '=')
                    return CPP_LEFT_ASSIGN;
                else{
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return CPP_LEFT_OP;
                }
            } else {
                if (ch == '=') {
                    return CPP_LE_OP;
                } else {
                    if (ch == '%')
                        return CPP_LEFT_BRACE;
                    else if (ch == ':')
                        return CPP_LEFT_BRACKET;
                    else{
                        pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                        return '<';
                    }
                }
            }
        case '>':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '>') {
                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                if (ch == '=')
                    return CPP_RIGHT_ASSIGN;
                else{
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return CPP_RIGHT_OP;
                }
            } else {
                if (ch == '=') {
                    return CPP_GE_OP;
                } else {
                    pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                    return '>';
                }
            }
        case '.':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch >= '0' && ch <= '9') {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return pp->lFloatConst(ppToken->name, 0, '.', ppToken);
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '.';
            }
        case '/':
            // TODO: preprocessor simplification: use the Scan.cpp comment scanner
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            if (ch == '/') {
                do {
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    if (ch == '\\') {
                        // allow an escaped newline, otherwise escapes in comments are meaningless
                        pp->parseContext.lineContinuationCheck(ppToken->loc);
                        ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                        if (ch == '\r' || ch == '\n') {
                            int nextch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                            if (ch == '\r' && nextch == '\n')
                                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                            else
                                ch = nextch;
                        }
                    } else if (ch > 0 && ! pp->languageCharacters[ch])
                        pp->parseContext.commentCharacterCheck(ppToken->loc, ch);
                } while (ch != '\n' && ch != EOF);
                if (ch == EOF)
                    return EOF;
                return '\n';
            } else if (ch == '*') {
                int nlcount = 0;
                ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                do {
                    while (ch != '*') {
                        if (ch == '\n')
                            nlcount++;
                        else if (ch == EOF) {
                            pp->parseContext.error(ppToken->loc, "EOF in comment", "comment", "");

                            return EOF;
                        } else if (! pp->languageCharacters[ch])
                            pp->parseContext.commentCharacterCheck(ppToken->loc, ch);
                        ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    }
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    if (ch == EOF) {
                        pp->parseContext.error(ppToken->loc, "EOF in comment", "comment", "");

                        return EOF;
                    } else if (! pp->languageCharacters[ch])
                        pp->parseContext.commentCharacterCheck(ppToken->loc, ch);
                } while (ch != '/');
                if (nlcount)
                    return '\n';
                // Go try it again...
            } else if (ch == '=') {
                return CPP_DIV_ASSIGN;
            } else {
                pp->currentInput->ungetch(pp, pp->currentInput, ch, ppToken);
                return '/';
            }
            break;
        case '"':
            ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
            while (ch != '"' && ch != '\n' && ch != EOF) {
                if (ch == '\\') {                    
                    pp->parseContext.lineContinuationCheck(ppToken->loc);
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                    if (ch == '\n' || ch == EOF) {
                        break;
                    }
                }
                if (len < TPpToken::maxTokenLength) {
                    tokenText[len] = ch;
                    len++;
                    ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
                } else
                    break;
            };
            tokenText[len] = '\0';
            if (ch == '"') {
                ppToken->atom = pp->LookUpAddString(tokenText);
                return CPP_STRCONSTANT;
            } else {
                pp->parseContext.error(ppToken->loc, "end of line in string", "string", "");
                return CPP_ERROR_SY;
            }
        }

        ppToken->ival = 0;
        ch = pp->currentInput->getch(pp, pp->currentInput, ppToken);
    }
}

//
// Return string pointer to next token.
// Return 0 when no more tokens.
//
const char* TPpContext::tokenize(TPpToken* ppToken)
{    
    int token = '\n';

    for(;;) {
        const char* tokenString = 0;
        token = currentInput->scan(this, currentInput, ppToken);
        ppToken->token = token;
        if (check_EOF(token))
            return 0;
        if (token == '#') {
            if (previous_token == '\n' || previous_token == 0) {
                token = readCPPline(ppToken);
                if (check_EOF(token))
                    return 0;
                continue;
            } else {
                parseContext.error(ppToken->loc, "preprocessor directive cannot be preceded by another token", "#", "");
                return 0;
            }
        }
        previous_token = token;

        if (token == '\n')
            continue;

        // expand macros
        if (token == CPP_IDENTIFIER && MacroExpand(ppToken->atom, ppToken, 0) == 1)
            continue;

        if (token == CPP_IDENTIFIER)
            tokenString = GetAtomString(ppToken->atom);
        else if (token == CPP_INTCONSTANT || token == CPP_UINTCONSTANT ||
                 token == CPP_FLOATCONSTANT || token == CPP_DOUBLECONSTANT)
            tokenString = ppToken->name;
        else if (token == CPP_STRCONSTANT) {
            parseContext.error(ppToken->loc, "string literals not supported", "\"\"", "");
            tokenString = 0;
        } else if (token == '\'') {
            parseContext.error(ppToken->loc, "character literals not supported", "\'", "");
            tokenString = 0;
        } else
            tokenString = GetAtomString(token);

        if (tokenString) {
            if (tokenString[0] != 0)
                parseContext.tokensBeforeEOF = 1;

            return tokenString;
        }
    }
}

//Checks if the token just read is EOF or not.
bool TPpContext::check_EOF(int token)
{
    if (token == EOF) {
        if (ifdepth > 0)
            parseContext.error(parseContext.getCurrentLoc(), "missing #endif", "", "");

        return true;
    }

    return false;
}

} // end namespace glslang
