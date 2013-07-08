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

class TPpToken {
public:
    static const int maxTokenLength = 1024;

    TSourceLoc loc;
    int    ppToken;
    int    ival;
    double dval;
    int    atom;
    char   name[maxTokenLength+1];
};

// This class is the result of turning a huge pile of C code communicating through globals
// into a class.  This was done to allowing instancing to attain thread safety.
// Don't expect too much in terms of OO design.
class TPpContext {
public:
    TPpContext(TParseContext&);
    virtual ~TPpContext();

    void setPreamble(const char* preamble, int length);
    void setShaderStrings(char* strings[], int lengths[], int numStrings);

    const char* tokenize(TPpToken* yylvalpp);

    struct InputSrc {
        struct InputSrc	*prev;
        int			(*scan)(TPpContext*, struct InputSrc *, TPpToken *);
        int			(*getch)(TPpContext*, struct InputSrc *, TPpToken *);
        void		(*ungetch)(TPpContext*, struct InputSrc *, int, TPpToken *);
        int			name;  /* atom */
        int			line;
    };

    struct TokenBlock {
        TokenBlock *next;
        int current;
        int count;
        int max;
        unsigned char *data;
    };

    struct TokenStream {
        TokenStream *next;
        char *name;
        TokenBlock *head;
        TokenBlock *current;
    };

    struct MemoryPool {
        struct chunk        *next;
        uintptr_t           free, end;
        size_t              chunksize;
        uintptr_t           alignmask;
        struct cleanup      *cleanup;
    };

    //
    // From PpAtom.cpp
    //
    struct StringTable {
        char *strings;
        int nextFree;
        int size;
    };
    typedef struct HashEntry_Rec {
        int index;      // String table offset of string representation
        int value;      // Atom (symbol) value
    } HashEntry;

    static const int hashTableMaxCollisions = 3;

    typedef struct HashTable_Rec {
        HashEntry *entry;
        int size;
        int entries;
        int counts[hashTableMaxCollisions + 1];
    } HashTable;
    struct AtomTable {
        StringTable stable; // String table.
        HashTable htable;   // Hashes string to atom number and token value.  Multiple strings can
        // have the same token value but each unique string is a unique atom.
        int *amap;          // Maps atom value to offset in string table.  Atoms all map to unique
        // strings except for some undefined values in the lower, fixed part
        // of the atom table that map to "<undefined>".  The lowest 256 atoms
        // correspond to single character ASCII values except for alphanumeric
        // characters and '_', which can be other tokens.  Next come the
        // language tokens with their atom values equal to the token value.
        // Then come predefined atoms, followed by user specified identifiers.
        int *arev;          // Reversed atom for symbol table use.
        int nextFree;
        int size;
    };

    struct MacroSymbol {
        int argc;
        int *args;
        TokenStream *body;
        unsigned busy:1;
        unsigned undef:1;
    };

    typedef enum symbolkind {
        MACRO_S
    } symbolkind;

    struct Symbol {
        Symbol *left, *right;
        Symbol *next;
        int name;       // Name atom
        TSourceLoc loc;
        symbolkind kind;
        union {
            MacroSymbol mac;
        } details;
    };

    typedef struct SymbolList {
        struct SymbolList_Rec *next;
        Symbol *symb;
    };

    struct Scope {
        Scope *next, *prev;     // doubly-linked list of all scopes
        Scope *parent;
        Scope *funScope;        // Points to base scope of enclosing function
        MemoryPool *pool;       // pool used for allocation in this scope
        Symbol *symbols;

        int level;              // 0 = super globals, 1 = globals, etc.

        // Only used at global scope (level 1):
        SymbolList *programs;   // List of programs for this compilation.
    };

protected:
    char*  preamble;               // string to parse, all before line 1 of string 0, it is 0 if no preamble
    int    preambleLength;
    char** strings;                // official strings of shader, starting a string 0 line 1
    int*   lengths;
    int    numStrings;             // how many official strings there are
    int    currentString;          // which string we're currently parsing  (-1 for preamble)

    // Scanner data:
    int mostRecentToken;        // Most recent token seen by the scanner
    int previous_token;
    bool notAVersionToken;      // used to make sure that #version is the first token seen in the file, if present
    TParseContext& parseContext;

    static const int maxMacroArgs = 64;
    static const int maxIfNesting = 64;

    int ifdepth;                 // current #if-#else-#endif nesting in the cpp.c file (pre-processor)    
    int elsedepth[maxIfNesting]; // Keep a track of #if depth..Max allowed is 64.   
    int elsetracker;             // #if-#else and #endif constructs...Counter.
    const char *ErrMsg;

    typedef struct MacroInputSrc {
        InputSrc    base;
        MacroSymbol *mac;
        TokenStream **args;
    } MacroInputSrc;

    InputSrc *currentInput;

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
    Scope *macros;
    TSourceLoc ifloc; /* outermost #if */

    int InitCPP();
    int FreeCPP();
    int FinalCPP();
    int CPPdefine(TPpToken * yylvalpp);
    int CPPundef(TPpToken * yylvalpp);
    int CPPelse(int matchelse, TPpToken * yylvalpp);
    int eval(int token, int prec, int *res, int *err, TPpToken * yylvalpp);
    int CPPif (TPpToken * yylvalpp); 
    int CPPifdef(int defined, TPpToken * yylvalpp);
    int CPPline(TPpToken * yylvalpp); 
    int CPPerror(TPpToken * yylvalpp); 
    int CPPpragma(TPpToken * yylvalpp);
    int CPPversion(TPpToken * yylvalpp);
    int CPPextension(TPpToken * yylvalpp);
    int readCPPline(TPpToken * yylvalpp);
    void FreeMacro(MacroSymbol *s);
    void PushEofSrc();
    void PopEofSrc();
    TokenStream* PrescanMacroArg(TokenStream *a, TPpToken * yylvalpp);
    static int macro_scan(TPpContext* pp, InputSrc *inInput, TPpToken * yylvalpp); 
    static int zero_scan(TPpContext* pp, InputSrc *inInput, TPpToken * yylvalpp); 
    int MacroExpand(int atom, TPpToken* yylvalpp, int expandUndef);
    int ChkCorrectElseNesting();

    //
    // from PpSymbols.cpp
    //
    Scope *ScopeList;
    Scope *CurrentScope;
    Scope *GlobalScope;

    Scope *NewScopeInPool(MemoryPool *pool);
    void PushScope(Scope *fScope);
    Scope *PopScope(void);
    Symbol *NewSymbol(TSourceLoc *loc, Scope *fScope, int name, symbolkind kind);
    void lAddToTree(Symbol **fSymbols, Symbol *fSymb, AtomTable *atable);
    Symbol *AddSymbol(TSourceLoc *loc, Scope *fScope, int atom, symbolkind kind);
    Symbol *LookUpLocalSymbol(Scope *fScope, int atom);
    Symbol *LookUpSymbol(Scope *fScope, int atom);

    //
    // From PpTokens.cpp
    //
    char* idstr(const char *fstr, MemoryPool *pool);
    TPpContext::TokenBlock* lNewBlock(TokenStream *fTok, MemoryPool *pool);
    void lAddByte(TokenStream *fTok, unsigned char fVal);
    int lReadByte(TokenStream *pTok);
    TokenStream *NewTokenStream(const char *name, MemoryPool *pool);
    void DeleteTokenStream(TokenStream *pTok);
    void RecordToken(TokenStream *pTok, int token, TPpToken * yylvalpp);
    void RewindTokenStream(TokenStream *pTok);
    int ReadToken(TokenStream *pTok, TPpToken * yylvalpp);
    int ReadFromTokenStream(TokenStream *ts, int name, int (*final)(TPpContext *));
    void UngetToken(int token, TPpToken * yylvalpp);
    void DumpTokenStream(FILE *fp, TokenStream *s, TPpToken * yylvalpp);
    struct TokenInputSrc {
        InputSrc            base;
        TokenStream         *tokens;
        int                 (*final)(TPpContext *);
    };
    static int scan_token(TPpContext*, TokenInputSrc *in, TPpToken * yylvalpp);
    struct UngotToken {
        InputSrc    base;
        int         token;
        TPpToken     lval;
    };
    static int reget_token(TPpContext *, UngotToken *t, TPpToken * yylvalpp);

    //
    // From PpScanner.cpp
    //
    struct StringInputSrc {
        InputSrc base;
        char *p;
    };
    int InitScanner(TPpContext *cpp);
    int FreeScanner(void);
    static int str_getch(TPpContext*, StringInputSrc *in);
    static void str_ungetch(TPpContext*, StringInputSrc *in, int ch, TPpToken *type);
    int ScanFromString(char *s);
    int check_EOF(int token);
    int lFloatConst(char *str, int len, int ch, TPpToken * yylvalpp);
    static int byte_scan(TPpContext*, InputSrc *in, TPpToken * yylvalpp);

    //
    // From PpAtom.cpp
    //
    AtomTable atomTable;
    int InitAtomTable(AtomTable *atable, int htsize);
    void FreeAtomTable(AtomTable *atable);
    int AddAtom(AtomTable *atable, const char *s);
    int AddAtomFixed(AtomTable *atable, const char *s, int atom);
    void PrintAtomTable(AtomTable *atable);
    int IncreaseHashTableSize(TPpContext::AtomTable *atable);
    int LookUpAddStringHash(AtomTable *atable, const char *s);
    int LookUpAddString(AtomTable *atable, const char *s);
    const char *GetAtomString(AtomTable *atable, int atom);
    int GetReversedAtom(AtomTable *atable, int atom);
    char* GetStringOfAtom(AtomTable *atable, int atom);

    //
    // From PpMemory.cpp
    //
    MemoryPool *mem_CreatePool(size_t chunksize, unsigned align);
    void mem_FreePool(MemoryPool *);
    void *mem_Alloc(MemoryPool *p, size_t size);
    int mem_AddCleanup(MemoryPool *p, void (*fn)(void *, void*), void *arg1, void* arg2);
};

#endif  // PPCONTEXT_H

