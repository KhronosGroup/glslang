//
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

#ifndef PPCONTEXT_H
#define PPCONTEXT_H

#include "../ParseHelper.h"

namespace glslang {

class TPpToken {
public:
    TPpToken() : token(0), ival(0), dval(0.0), atom(0)
    { 
        loc.line = 0; 
        loc.string = 0; 
        name[0] = 0;
    }

    bool operator==(const TPpToken& right)
    {
        return token == right.token && atom == right.atom &&
               ival == right.ival && dval == right.dval &&
               strcmp(name, right.name) == 0;
    }
    bool operator!=(const TPpToken& right) { return ! operator==(right); }

    static const int maxTokenLength = 1024;

    TSourceLoc loc;
    int    token;
    int    ival;
    double dval;
    int    atom;
    char   name[maxTokenLength+1];
};

class TInputScanner;

// This class is the result of turning a huge pile of C code communicating through globals
// into a class.  This was done to allowing instancing to attain thread safety.
// Don't expect too much in terms of OO design.
class TPpContext {
public:
    TPpContext(TParseContext&);
    virtual ~TPpContext();

    void setPreamble(const char* preamble, size_t length);
    void setInput(TInputScanner& input, bool versionWillBeError);

    const char* tokenize(TPpToken* ppToken);

    // TODO: preprocessor simplification: this should be a base class, not a set of function pointers
    struct InputSrc {
        InputSrc() : prev(0), scan(0), getch(0), ungetch(0) { }
        struct InputSrc	*prev;
        int			(*scan)(TPpContext*, struct InputSrc *, TPpToken *);
        int			(*getch)(TPpContext*, struct InputSrc *, TPpToken *);
        void		(*ungetch)(TPpContext*, struct InputSrc *, int, TPpToken *);
    };

    struct TokenStream {
        TokenStream() : current(0) { }
        TVector<unsigned char> data;
        size_t current;
    };

    struct MemoryPool {
        struct chunk        *next;
        uintptr_t           free, end;
        size_t              chunksize;
        uintptr_t           alignmask;
        struct cleanup      *cleanup;
    };

    //
    // From Pp.cpp
    //

    struct MacroSymbol {
        MacroSymbol() : argc(0), args(0), body(0), busy(0), undef(0) { }
        int argc;
        int *args;
        TokenStream *body;
        unsigned busy:1;
        unsigned undef:1;
    };

    struct Symbol {
        int atom;
        MacroSymbol mac;
    };

    struct SymbolList {
        struct SymbolList_Rec *next;
        Symbol *symb;
    };

    MemoryPool *pool;
    typedef std::map<int, Symbol*> TSymbolMap;
    TSymbolMap symbols; // this has light use... just defined macros

protected:
    char*   preamble;               // string to parse, all before line 1 of string 0, it is 0 if no preamble
    int     preambleLength;
    char**  strings;                // official strings of shader, starting a string 0 line 1
    size_t* lengths;
    int     numStrings;             // how many official strings there are
    int     currentString;          // which string we're currently parsing  (-1 for preamble)

    // Scanner data:
    int mostRecentToken;        // Most recent token seen by the scanner
    int previous_token;
    TParseContext& parseContext;

    static const int maxMacroArgs = 64;
    static const int maxIfNesting = 64;

    int ifdepth;                  // current #if-#else-#endif nesting in the cpp.c file (pre-processor)    
    bool elseSeen[maxIfNesting];  // Keep a track of whether an else has been seen at a particular depth
    int elsetracker;              // #if-#else and #endif constructs...Counter.
    const char *ErrMsg;

    struct MacroInputSrc : public InputSrc {
        MacroInputSrc() : mac(0) { }
        virtual ~MacroInputSrc()
        {
            for (size_t i = 0; i < args.size(); ++i)
                delete args[i];
        }
        MacroSymbol *mac;
        TVector<TokenStream*> args;
    };

    InputSrc *currentInput;
    bool errorOnVersion;

    bool languageCharacters[256];

    //
    // from Pp.cpp
    //
    int bindAtom;
    int constAtom;
    int defaultAtom;
    int defineAtom;
    int definedAtom;
    int elseAtom;
    int elifAtom;
    int endifAtom;
    int ifAtom;
    int ifdefAtom;
    int ifndefAtom;
    int includeAtom;
    int lineAtom;
    int pragmaAtom;
    int texunitAtom;
    int undefAtom;
    int errorAtom;
    int __LINE__Atom;
    int __FILE__Atom;
    int __VERSION__Atom;
    int versionAtom;
    int coreAtom;
    int compatibilityAtom;
    int esAtom;
    int extensionAtom;
    TSourceLoc ifloc; /* outermost #if */

    int InitCPP();
    int CPPdefine(TPpToken * ppToken);
    int CPPundef(TPpToken * ppToken);
    int CPPelse(int matchelse, TPpToken * ppToken);
    int extraTokenCheck(int atom, TPpToken* ppToken, int token);
    int eval(int token, int precedence, int& res, bool& err, TPpToken * ppToken);
    int CPPif (TPpToken * ppToken); 
    int CPPifdef(int defined, TPpToken * ppToken);
    int CPPline(TPpToken * ppToken); 
    int CPPerror(TPpToken * ppToken); 
    int CPPpragma(TPpToken * ppToken);
    int CPPversion(TPpToken * ppToken);
    int CPPextension(TPpToken * ppToken);
    int readCPPline(TPpToken * ppToken);
    void PushEofSrc();
    void PopEofSrc();
    TokenStream* PrescanMacroArg(TokenStream *a, TPpToken * ppToken);
    static int macro_scan(TPpContext* pp, InputSrc *inInput, TPpToken * ppToken); 
    static int zero_scan(TPpContext* pp, InputSrc *inInput, TPpToken * ppToken); 
    int MacroExpand(int atom, TPpToken* ppToken, int expandUndef);

    //
    // from PpSymbols.cpp
    //
    Symbol *NewSymbol(int name);
    Symbol *AddSymbol(int atom);
    Symbol *LookUpSymbol(int atom);

    //
    // From PpTokens.cpp
    //
    void lAddByte(TokenStream *fTok, unsigned char fVal);
    int lReadByte(TokenStream *pTok);
    void RecordToken(TokenStream* pTok, int token, TPpToken* ppToken);
    void RewindTokenStream(TokenStream *pTok);
    int ReadToken(TokenStream* pTok, TPpToken* ppToken);
    int ReadFromTokenStream(TokenStream *ts, int name, int (*final)(TPpContext *));
    void UngetToken(int token, TPpToken* ppToken);
    struct TokenInputSrc : public InputSrc {
        TokenStream *tokens;
        int (*final)(TPpContext *);
    };
    static int scan_token(TPpContext*, TokenInputSrc *in, TPpToken * ppToken);
    struct UngotToken : public InputSrc {
        int token;
        TPpToken lval;
    };
    static int reget_token(TPpContext *, UngotToken *t, TPpToken * ppToken);

    //
    // From PpScanner.cpp
    //
    struct StringInputSrc : public InputSrc {
        TInputScanner* input;
    };
    int InitScanner(TPpContext *cpp);
    static int sourceGetCh(TPpContext*, StringInputSrc *in);
    static void sourceUngetCh(TPpContext*, StringInputSrc *in, int ch, TPpToken *type);
    int ScanFromString(char *s);
    bool check_EOF(int token);
    int lFloatConst(char *str, int len, int ch, TPpToken * ppToken);
    static int sourceScan(TPpContext*, InputSrc *in, TPpToken * ppToken);

    //
    // From PpAtom.cpp
    //
    typedef std::map<const TString, int> TAtomMap;
    typedef TVector<const TString*> TStringMap;
    TAtomMap atomMap;
    TStringMap stringMap;
    int nextAtom;
    void InitAtomTable();
    int AddAtomFixed(const char *s, int atom);
    int LookUpAddString(const char *s);
    const char *GetAtomString(int atom);

    //
    // From PpMemory.cpp
    //
    MemoryPool *mem_CreatePool(size_t chunksize, unsigned align);
    void mem_FreePool(MemoryPool *);
    void *mem_Alloc(MemoryPool *p, size_t size);
    int mem_AddCleanup(MemoryPool *p, void (*fn)(void *, void*), void *arg1, void* arg2);
};

} // end namespace glslang

#endif  // PPCONTEXT_H
