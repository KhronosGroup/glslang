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

#include <cstdlib>
#include <cstring>

#include "PpContext.h"
#include "PpTokens.h"
#include "../Scan.h"

namespace glslang {

int TPpContext::InitScanner()
{
    // Add various atoms needed by the CPP line scanner:
    if (!InitCPP())
        return 0;

    previous_token = '\n';

    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Floating point constants: /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*
* lFloatConst() - Scan a single- or double-precision floating point constant.  Assumes that the scanner
*         has seen at least one digit, followed by either a decimal '.' or the
*         letter 'e', or a precision ending (e.g., F or LF).
*/

int TPpContext::lFloatConst(int len, int ch, TPpToken* ppToken)
{
    bool HasDecimalOrExponent = false;
    int declen;
    int str_len;
    int isDouble = 0;

    declen = 0;

    str_len=len;
    char* str = ppToken->name;
    if (ch == '.') {
        HasDecimalOrExponent = true;
        str[len++] = (char)ch;
        ch = getChar();
        while (ch >= '0' && ch <= '9') {
            if (len < MaxTokenLength) {
                declen++;
                if (len > 0 || ch != '0') {
                    str[len] = (char)ch;
                    len++;
                    str_len++;
                }
                ch = getChar();
            } else {
                parseContext.ppError(ppToken->loc, "float literal too long", "", "");
                len = 1;
                str_len = 1;
            }
        }
    }

    // Exponent:

    if (ch == 'e' || ch == 'E') {
        HasDecimalOrExponent = true;
        if (len >= MaxTokenLength) {
            parseContext.ppError(ppToken->loc, "float literal too long", "", "");
            len = 1;
            str_len = 1;
        } else {
            str[len++] = (char)ch;
            ch = getChar();
            if (ch == '+') {
                str[len++] = (char)ch;
                ch = getChar();
            } else if (ch == '-') {
                str[len++] = (char)ch;
                ch = getChar();
            }
            if (ch >= '0' && ch <= '9') {
                while (ch >= '0' && ch <= '9') {
                    if (len < MaxTokenLength) {
                        str[len++] = (char)ch;
                        ch = getChar();
                    } else {
                        parseContext.ppError(ppToken->loc, "float literal too long", "", "");
                        len = 1;
                        str_len = 1;
                    }
                }
            } else {
                parseContext.ppError(ppToken->loc, "bad character in float exponent", "", "");
            }
        }
    }

    if (len == 0) {
        ppToken->dval = 0.0;
        strcpy(str, "0.0");
    } else {
        if (ch == 'l' || ch == 'L') {
            parseContext.doubleCheck(ppToken->loc, "double floating-point suffix");
            if (! HasDecimalOrExponent)
                parseContext.ppError(ppToken->loc, "float literal needs a decimal point or exponent", "", "");
            int ch2 = getChar();
            if (ch2 != 'f' && ch2 != 'F') {
                ungetChar();
                ungetChar();
            } else {
                if (len < MaxTokenLength) {
                    str[len++] = (char)ch;
                    str[len++] = (char)ch2;
                    isDouble = 1;
                } else {
                    parseContext.ppError(ppToken->loc, "float literal too long", "", "");
                    len = 1,str_len=1;
                }
            }
        } else if (ch == 'f' || ch == 'F') {
            parseContext.profileRequires(ppToken->loc,  EEsProfile, 300, nullptr, "floating-point suffix");
            if (! parseContext.relaxedErrors())
                parseContext.profileRequires(ppToken->loc, ~EEsProfile, 120, nullptr, "floating-point suffix");
            if (! HasDecimalOrExponent)
                parseContext.ppError(ppToken->loc, "float literal needs a decimal point or exponent", "", "");
            if (len < MaxTokenLength)
                str[len++] = (char)ch;
            else {
                parseContext.ppError(ppToken->loc, "float literal too long", "", "");
                len = 1,str_len=1;
            }
        } else 
            ungetChar();

        str[len]='\0';

        ppToken->dval = strtod(str, nullptr);
    }

    if (isDouble)
        return PpAtomConstDouble;
    else
        return PpAtomConstFloat;
}

//
// Scanner used to tokenize source stream.
//
int TPpContext::tStringInput::scan(TPpToken* ppToken)
{
    char* tokenText = ppToken->name;
    int AlreadyComplained = 0;
    int len = 0;
    int ch = 0;
    int ii = 0;
    unsigned long long ival = 0;
    bool enableInt64 = pp->parseContext.version >= 450 && pp->parseContext.extensionTurnedOn(E_GL_ARB_gpu_shader_int64);

    ppToken->ival = 0;
    ppToken->i64val = 0;
    ppToken->space = false;
    ch = getch();
    for (;;) {
        while (ch == ' ' || ch == '\t') {
            ppToken->space = true;
            ch = getch();
        }

        ppToken->loc = pp->parseContext.getCurrentLoc();
        len = 0;
        switch (ch) {
        default:
            // Single character token, including EndOfInput, '#' and '\' (escaped newlines are handled at a lower level, so this is just a '\' token)
            return ch;

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
        case 'z':
            do {
                if (len < MaxTokenLength) {
                    tokenText[len++] = (char)ch;
                    ch = getch();
                } else {
                    if (! AlreadyComplained) {
                        pp->parseContext.ppError(ppToken->loc, "name too long", "", "");
                        AlreadyComplained = 1;
                    }
                    ch = getch();
                }
            } while ((ch >= 'a' && ch <= 'z') ||
                     (ch >= 'A' && ch <= 'Z') ||
                     (ch >= '0' && ch <= '9') ||
                     ch == '_');

            // line continuation with no token before or after makes len == 0, and need to start over skipping white space, etc.
            if (len == 0)
                continue;

            tokenText[len] = '\0';
            ungetch();
            ppToken->atom = pp->LookUpAddString(tokenText);
            return PpAtomIdentifier;
        case '0':
            ppToken->name[len++] = (char)ch;
            ch = getch();
            if (ch == 'x' || ch == 'X') {
                // must be hexadecimal

                bool isUnsigned = false;
                bool isInt64 = false;
                ppToken->name[len++] = (char)ch;
                ch = getch();
                if ((ch >= '0' && ch <= '9') ||
                    (ch >= 'A' && ch <= 'F') ||
                    (ch >= 'a' && ch <= 'f')) {

                    ival = 0;
                    do {
                        if (ival <= 0x0fffffff || (enableInt64 && ival <= 0x0fffffffffffffffull)) {
                            ppToken->name[len++] = (char)ch;
                            if (ch >= '0' && ch <= '9') {
                                ii = ch - '0';
                            } else if (ch >= 'A' && ch <= 'F') {
                                ii = ch - 'A' + 10;
                            } else if (ch >= 'a' && ch <= 'f') {
                                ii = ch - 'a' + 10;
                            } else
                                pp->parseContext.ppError(ppToken->loc, "bad digit in hexadecimal literal", "", "");
                            ival = (ival << 4) | ii;
                        } else {
                            if (! AlreadyComplained) {
                                pp->parseContext.ppError(ppToken->loc, "hexadecimal literal too big", "", "");
                                AlreadyComplained = 1;
                            }
                            ival = 0xffffffffffffffffull;
                        }
                        ch = getch();
                    } while ((ch >= '0' && ch <= '9') ||
                             (ch >= 'A' && ch <= 'F') ||
                             (ch >= 'a' && ch <= 'f'));
                } else {
                    pp->parseContext.ppError(ppToken->loc, "bad digit in hexadecimal literal", "", "");
                }
                if (ch == 'u' || ch == 'U') {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isUnsigned = true;

                    if (enableInt64) {
                        int nextCh = getch();
                        if ((ch == 'u' && nextCh == 'l') || (ch == 'U' && nextCh == 'L')) {
                            if (len < MaxTokenLength)
                                ppToken->name[len++] = (char)nextCh;
                            isInt64 = true;
                        } else
                            ungetch();
                    }
                }
                else if (enableInt64 && (ch == 'l' || ch == 'L')) {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isInt64 = true;
                } else
                    ungetch();
                ppToken->name[len] = '\0';

                if (isInt64) {
                    ppToken->i64val = ival;
                    return isUnsigned ? PpAtomConstUint64 : PpAtomConstInt64;
                } else {
                    ppToken->ival = (int)ival;
                    return isUnsigned ? PpAtomConstUint : PpAtomConstInt;
                }
            } else {
                // could be octal integer or floating point, speculative pursue octal until it must be floating point

                bool isUnsigned = false;
                bool isInt64 = false;
                bool octalOverflow = false;
                bool nonOctal = false;
                ival = 0;

                // see how much octal-like stuff we can read
                while (ch >= '0' && ch <= '7') {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    else if (! AlreadyComplained) {
                        pp->parseContext.ppError(ppToken->loc, "numeric literal too long", "", "");
                        AlreadyComplained = 1;
                    }
                    if (ival <= 0x1fffffff || (enableInt64 && ival <= 0x1fffffffffffffffull)) {
                        ii = ch - '0';
                        ival = (ival << 3) | ii;
                    } else
                        octalOverflow = true;
                    ch = getch();
                }

                // could be part of a float...
                if (ch == '8' || ch == '9') {
                    nonOctal = true;
                    do {
                        if (len < MaxTokenLength)
                            ppToken->name[len++] = (char)ch;
                        else if (! AlreadyComplained) {
                            pp->parseContext.ppError(ppToken->loc, "numeric literal too long", "", "");
                            AlreadyComplained = 1;
                        }
                        ch = getch();
                    } while (ch >= '0' && ch <= '9');
                }
                if (ch == '.' || ch == 'e' || ch == 'f' || ch == 'E' || ch == 'F')
                    return pp->lFloatConst(len, ch, ppToken);

                // wasn't a float, so must be octal...
                if (nonOctal)
                    pp->parseContext.ppError(ppToken->loc, "octal literal digit too large", "", "");

                if (ch == 'u' || ch == 'U') {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isUnsigned = true;

                    if (enableInt64) {
                        int nextCh = getch();
                        if ((ch == 'u' && nextCh == 'l') || (ch == 'U' && nextCh == 'L')) {
                            if (len < MaxTokenLength)
                                ppToken->name[len++] = (char)nextCh;
                            isInt64 = true;
                        } else
                            ungetch();
                    }
                }
                else if (enableInt64 && (ch == 'l' || ch == 'L')) {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isInt64 = true;
                } else
                    ungetch();
                ppToken->name[len] = '\0';

                if (octalOverflow)
                    pp->parseContext.ppError(ppToken->loc, "octal literal too big", "", "");

                if (isInt64) {
                    ppToken->i64val = ival;
                    return isUnsigned ? PpAtomConstUint64 : PpAtomConstInt64;
                } else {
                    ppToken->ival = (int)ival;
                    return isUnsigned ? PpAtomConstUint : PpAtomConstInt;
                }
            }
            break;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            // can't be hexadecimal or octal, is either decimal or floating point

            do {
                if (len < MaxTokenLength)
                    ppToken->name[len++] = (char)ch;
                else if (! AlreadyComplained) {
                    pp->parseContext.ppError(ppToken->loc, "numeric literal too long", "", "");
                    AlreadyComplained = 1;
                }
                ch = getch();
            } while (ch >= '0' && ch <= '9');
            if (ch == '.' || ch == 'e' || ch == 'f' || ch == 'E' || ch == 'F') {
                return pp->lFloatConst(len, ch, ppToken);
            } else {
                // Finish handling signed and unsigned integers
                int numericLen = len;
                bool isUnsigned = false;
                bool isInt64 = false;
                if (ch == 'u' || ch == 'U') {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isUnsigned = true;

                    if (enableInt64) {
                        int nextCh = getch();
                        if ((ch == 'u' && nextCh == 'l') || (ch == 'U' && nextCh == 'L')) {
                            if (len < MaxTokenLength)
                                ppToken->name[len++] = (char)nextCh;
                            isInt64 = true;
                        } else
                            ungetch();
                    }
                } else if (enableInt64 && (ch == 'l' || ch == 'L')) {
                    if (len < MaxTokenLength)
                        ppToken->name[len++] = (char)ch;
                    isInt64 = true;
                } else
                    ungetch();

                ppToken->name[len] = '\0';
                ival = 0;
                const unsigned oneTenthMaxInt  = 0xFFFFFFFFu / 10;
                const unsigned remainderMaxInt = 0xFFFFFFFFu - 10 * oneTenthMaxInt;
                const unsigned long long oneTenthMaxInt64  = 0xFFFFFFFFFFFFFFFFull / 10;
                const unsigned long long remainderMaxInt64 = 0xFFFFFFFFFFFFFFFFull - 10 * oneTenthMaxInt64;
                for (int i = 0; i < numericLen; i++) {
                    ch = ppToken->name[i] - '0';
                    if ((enableInt64 == false && ((ival > oneTenthMaxInt) || (ival == oneTenthMaxInt && (unsigned)ch > remainderMaxInt))) ||
                        (enableInt64 && ((ival > oneTenthMaxInt64) || (ival == oneTenthMaxInt64 && (unsigned long long)ch > remainderMaxInt64)))) {
                        pp->parseContext.ppError(ppToken->loc, "numeric literal too big", "", "");
                        ival = 0xFFFFFFFFFFFFFFFFull;
                        break;
                    } else
                        ival = ival * 10 + ch;
                }

                if (isInt64) {
                    ppToken->i64val = ival;
                    return isUnsigned ? PpAtomConstUint64 : PpAtomConstInt64;
                } else {
                    ppToken->ival = (int)ival;
                    return isUnsigned ? PpAtomConstUint : PpAtomConstInt;
                }
            }
            break;
        case '-':
            ch = getch();
            if (ch == '-') {
                return PpAtomDecrement;
            } else if (ch == '=') {
                return PpAtomSub;
            } else {
                ungetch();
                return '-';
            }
        case '+':
            ch = getch();
            if (ch == '+') {
                return PpAtomIncrement;
            } else if (ch == '=') {
                return PpAtomAdd;
            } else {
                ungetch();
                return '+';
            }
        case '*':
            ch = getch();
            if (ch == '=') {
                return PpAtomMul;
            } else {
                ungetch();
                return '*';
            }
        case '%':
            ch = getch();
            if (ch == '=') {
                return PpAtomMod;
            } else {
                ungetch();
                return '%';
            }
        case '^':
            ch = getch();
            if (ch == '^') {
                return PpAtomXor;
            } else {
                if (ch == '=')
                    return PpAtomXorAssign;
                else{
                    ungetch();
                    return '^';
                }
            }

        case '=':
            ch = getch();
            if (ch == '=') {
                return PpAtomEQ;
            } else {
                ungetch();
                return '=';
            }
        case '!':
            ch = getch();
            if (ch == '=') {
                return PpAtomNE;
            } else {
                ungetch();
                return '!';
            }
        case '|':
            ch = getch();
            if (ch == '|') {
                return PpAtomOr;
            } else if (ch == '=') {
                return PpAtomOrAssign;
            } else {
                ungetch();
                return '|';
            }
        case '&':
            ch = getch();
            if (ch == '&') {
                return PpAtomAnd;
            } else if (ch == '=') {
                return PpAtomAndAssign;
            } else {
                ungetch();
                return '&';
            }
        case '<':
            ch = getch();
            if (ch == '<') {
                ch = getch();
                if (ch == '=')
                    return PpAtomLeftAssign;
                else {
                    ungetch();
                    return PpAtomLeft;
                }
            } else if (ch == '=') {
                return PpAtomLE;
            } else {
                ungetch();
                return '<';
            }
        case '>':
            ch = getch();
            if (ch == '>') {
                ch = getch();
                if (ch == '=')
                    return PpAtomRightAssign;
                else {
                    ungetch();
                    return PpAtomRight;
                }
            } else if (ch == '=') {
                return PpAtomGE;
            } else {
                ungetch();
                return '>';
            }
        case '.':
            ch = getch();
            if (ch >= '0' && ch <= '9') {
                ungetch();
                return pp->lFloatConst(0, '.', ppToken);
            } else {
                ungetch();
                return '.';
            }
        case '/':
            ch = getch();
            if (ch == '/') {
                pp->inComment = true;
                do {
                    ch = getch();
                } while (ch != '\n' && ch != EndOfInput);
                ppToken->space = true;
                pp->inComment = false;

                return ch;
            } else if (ch == '*') {
                ch = getch();
                do {
                    while (ch != '*') {
                        if (ch == EndOfInput) {
                            pp->parseContext.ppError(ppToken->loc, "End of input in comment", "comment", "");
                            return ch;
                        }
                        ch = getch();
                    }
                    ch = getch();
                    if (ch == EndOfInput) {
                        pp->parseContext.ppError(ppToken->loc, "End of input in comment", "comment", "");
                        return ch;
                    }
                } while (ch != '/');
                ppToken->space = true;
                // loop again to get the next token...
                break;
            } else if (ch == '=') {
                return PpAtomDiv;
            } else {
                ungetch();
                return '/';
            }
            break;
        case '"':
            ch = getch();
            while (ch != '"' && ch != '\n' && ch != EndOfInput) {
                if (len < MaxTokenLength) {
                    tokenText[len] = (char)ch;
                    len++;
                    ch = getch();
                } else
                    break;
            };
            tokenText[len] = '\0';
            if (ch != '"') {
                ungetch();
                pp->parseContext.ppError(ppToken->loc, "End of line in string", "string", "");
            }
            return PpAtomConstString;
        }

        ch = getch();
    }
}

//
// The main functional entry-point into the preprocessor, which will
// scan the source strings to figure out and return the next processing token.
//
// Return string pointer to next token.
// Return 0 when no more tokens.
//
const char* TPpContext::tokenize(TPpToken* ppToken)
{
    int token = '\n';

    for(;;) {
        token = scanToken(ppToken);
        ppToken->token = token;
        if (token == EndOfInput) {
            missingEndifCheck();
            return nullptr;
        }
        if (token == '#') {
            if (previous_token == '\n') {
                token = readCPPline(ppToken);
                if (token == EndOfInput) {
                    missingEndifCheck();
                    return nullptr;
                }
                continue;
            } else {
                parseContext.ppError(ppToken->loc, "preprocessor directive cannot be preceded by another token", "#", "");
                return nullptr;
            }
        }
        previous_token = token;

        if (token == '\n')
            continue;

        // expand macros
        if (token == PpAtomIdentifier && MacroExpand(ppToken->atom, ppToken, false, true) != 0)
            continue;

        const char* tokenString = nullptr;
        switch (token) {
        case PpAtomIdentifier:
        case PpAtomConstInt:
        case PpAtomConstUint:
        case PpAtomConstFloat:
        case PpAtomConstInt64:
        case PpAtomConstUint64:
        case PpAtomConstDouble:
            tokenString = ppToken->name;
            break;
        case PpAtomConstString:
            parseContext.ppError(ppToken->loc, "string literals not supported", "\"\"", "");
            break;
        case '\'':
            parseContext.ppError(ppToken->loc, "character literals not supported", "\'", "");
            break;
        default:
            tokenString = GetAtomString(token);
            break;
        }

        if (tokenString) {
            if (tokenString[0] != 0)
                parseContext.tokensBeforeEOF = 1;

            return tokenString;
        }
    }
}

// Checks if we've seen balanced #if...#endif
void TPpContext::missingEndifCheck()
{
    if (ifdepth > 0)
        parseContext.ppError(parseContext.getCurrentLoc(), "missing #endif", "", "");
}

} // end namespace glslang
