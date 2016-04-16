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

#include <stack>
#include <unordered_map>

#include "../ParseHelper.h"

/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4127)
#endif

namespace glslang {

class TPpToken {
public:
    TPpToken() : token(0), space(false), ival(0), dval(0.0), atom(0)
    {
        loc.init(); 
        name[0] = 0;
    }

    bool operator==(const TPpToken& right)
    {
        return token == right.token && atom == right.atom &&
               ival == right.ival && dval == right.dval &&
               strcmp(name, right.name) == 0;
    }
    bool operator!=(const TPpToken& right) { return ! operator==(right); }

    TSourceLoc loc;
    int    token;
    bool   space;  // true if a space (for white space or a removed comment) should also be recognized, in front of the token returned
    int    ival;
    double dval;
    int    atom;
    char   name[MaxTokenLength + 1];
};

class TInputScanner;

// This class is the result of turning a huge pile of C code communicating through globals
// into a class.  This was done to allowing instancing to attain thread safety.
// Don't expect too much in terms of OO design.
class TPpContext {
public:
    TPpContext(TParseContextBase&, const std::string& rootFileName, TShader::Includer);
    virtual ~TPpContext();

    void setPreamble(const char* preamble, size_t length);

    const char* tokenize(TPpToken* ppToken);

    class tInput {
    public:
        tInput(TPpContext* p) : done(false), pp(p) { }
        virtual ~tInput() { }

        virtual int scan(TPpToken*) = 0;
        virtual int getch() = 0;
        virtual void ungetch() = 0;

        // Will be called when we start reading tokens from this instance
        virtual void notifyActivated() {}
        // Will be called when we do not read tokens from this instance anymore
        virtual void notifyDeleted() {}
    protected:
        bool done;
        TPpContext* pp;
    };

    void setInput(TInputScanner& input, bool versionWillBeError);

    void pushInput(tInput* in)
    {
        inputStack.push_back(in);
        in->notifyActivated();
    }
    void popInput()
    {
        inputStack.back()->notifyDeleted();
        delete inputStack.back();
        inputStack.pop_back();
    }

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
    typedef TMap<int, Symbol*> TSymbolMap;
    TSymbolMap symbols; // this has light use... just defined macros

protected:
    TPpContext(TPpContext&);
    TPpContext& operator=(TPpContext&);

    char*   preamble;               // string to parse, all before line 1 of string 0, it is 0 if no preamble
    int     preambleLength;
    char**  strings;                // official strings of shader, starting a string 0 line 1
    size_t* lengths;
    int     numStrings;             // how many official strings there are
    int     currentString;          // which string we're currently parsing  (-1 for preamble)

    // Scanner data:
    int previous_token;
    TParseContextBase& parseContext;

    // Get the next token from *stack* of input sources, popping input sources
    // that are out of tokens, down until an input sources is found that has a token.
    // Return EndOfInput when there are no more tokens to be found by doing this.
    int scanToken(TPpToken* ppToken)
    {
        int token = EndOfInput;

        while (! inputStack.empty()) {
            token = inputStack.back()->scan(ppToken);
            if (token != EndOfInput)
                break;
            popInput();
        }

        return token;
    }
    int  getChar() { return inputStack.back()->getch(); }
    void ungetChar() { inputStack.back()->ungetch(); }

    static const int maxMacroArgs = 64;
    static const int maxIfNesting = 64;

    int ifdepth;                  // current #if-#else-#endif nesting in the cpp.c file (pre-processor)    
    bool elseSeen[maxIfNesting];  // Keep a track of whether an else has been seen at a particular depth
    int elsetracker;              // #if-#else and #endif constructs...Counter.

    class tMacroInput : public tInput {
    public:
        tMacroInput(TPpContext* pp) : tInput(pp) { }
        virtual ~tMacroInput()
        {
            for (size_t i = 0; i < args.size(); ++i)
                delete args[i];
        }

        virtual int scan(TPpToken*);
        virtual int getch() { assert(0); return EndOfInput; }
        virtual void ungetch() { assert(0); }
        MacroSymbol *mac;
        TVector<TokenStream*> args;
    };

    class tMarkerInput : public tInput {
    public:
        tMarkerInput(TPpContext* pp) : tInput(pp) { }
        virtual int scan(TPpToken*)
        {
            if (done)
                return EndOfInput;
            done = true;

            return marker;
        }
        virtual int getch() { assert(0); return EndOfInput; }
        virtual void ungetch() { assert(0); }
        static const int marker = -3;
    };

    class tZeroInput : public tInput {
    public:
        tZeroInput(TPpContext* pp) : tInput(pp) { }
        virtual int scan(TPpToken*);
        virtual int getch() { assert(0); return EndOfInput; }
        virtual void ungetch() { assert(0); }
    };

    std::vector<tInput*> inputStack;
    bool errorOnVersion;
    bool versionSeen;

    //
    // from Pp.cpp
    //

    // Used to obtain #include content.
    TShader::Includer includer;

    int InitCPP();
    int CPPdefine(TPpToken * ppToken);
    int CPPundef(TPpToken * ppToken);
    int CPPelse(int matchelse, TPpToken * ppToken);
    int extraTokenCheck(int atom, TPpToken* ppToken, int token);
    int eval(int token, int precedence, bool shortCircuit, int& res, bool& err, TPpToken * ppToken);
    int evalToToken(int token, bool shortCircuit, int& res, bool& err, TPpToken * ppToken);
    int CPPif (TPpToken * ppToken); 
    int CPPifdef(int defined, TPpToken * ppToken);
    int CPPinclude(TPpToken * ppToken);
    int CPPline(TPpToken * ppToken); 
    int CPPerror(TPpToken * ppToken); 
    int CPPpragma(TPpToken * ppToken);
    int CPPversion(TPpToken * ppToken);
    int CPPextension(TPpToken * ppToken);
    int readCPPline(TPpToken * ppToken);
    TokenStream* PrescanMacroArg(TokenStream *a, TPpToken * ppToken, bool newLineOkay);
    int MacroExpand(int atom, TPpToken* ppToken, bool expandUndef, bool newLineOkay);

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
    void lUnreadByte(TokenStream *pTok);
    void RecordToken(TokenStream* pTok, int token, TPpToken* ppToken);
    void RewindTokenStream(TokenStream *pTok);
    int ReadToken(TokenStream* pTok, TPpToken* ppToken);
    void pushTokenStreamInput(TokenStream *ts);
    void UngetToken(int token, TPpToken* ppToken);
    
    class tTokenInput : public tInput {
    public:
        tTokenInput(TPpContext* pp, TokenStream* t) : tInput(pp), tokens(t) { }
        virtual int scan(TPpToken *);
        virtual int getch() { assert(0); return EndOfInput; }
        virtual void ungetch() { assert(0); }
    protected:
        TokenStream *tokens;
    };

    class tUngotTokenInput : public tInput {
    public:
        tUngotTokenInput(TPpContext* pp, int t, TPpToken* p) : tInput(pp), token(t), lval(*p) { }
        virtual int scan(TPpToken *);
        virtual int getch() { assert(0); return EndOfInput; }
        virtual void ungetch() { assert(0); }
    protected:
        int token;
        TPpToken lval;
    };

    //
    // From PpScanner.cpp
    //
    class tStringInput : public tInput {
    public:
        tStringInput(TPpContext* pp, TInputScanner& i) : tInput(pp), input(&i) { }
        virtual int scan(TPpToken*);

        // Scanner used to get source stream characters.
        //  - Escaped newlines are handled here, invisibly to the caller.
        //  - All forms of newline are handled, and turned into just a '\n'.
        int getch()
        {
            int ch = input->get();

            if (ch == '\\') {
                // Move past escaped newlines, as many as sequentially exist
                do {
                    if (input->peek() == '\r' || input->peek() == '\n') {
                        bool allowed = pp->parseContext.lineContinuationCheck(input->getSourceLoc(), pp->inComment);
                        if (! allowed && pp->inComment)
                            return '\\';

                        // escape one newline now
                        ch = input->get();
                        int nextch = input->get();
                        if (ch == '\r' && nextch == '\n')
                            ch = input->get();
                        else
                            ch = nextch;
                    } else
                        return '\\';
                } while (ch == '\\');
            }
    
            // handle any non-escaped newline
            if (ch == '\r' || ch == '\n') {
                if (ch == '\r' && input->peek() == '\n')
                    input->get();
                return '\n';
            }

            return ch;
        }

        // Scanner used to backup the source stream characters.  Newlines are
        // handled here, invisibly to the caller, meaning have to undo exactly
        // what getch() above does (e.g., don't leave things in the middle of a
        // sequence of escaped newlines).
        void ungetch()
        {
            input->unget();

            do {
                int ch = input->peek();
                if (ch == '\r' || ch == '\n') {
                    if (ch == '\n') {
                        // correct for two-character newline
                        input->unget();
                        if (input->peek() != '\r')
                            input->get();
                    }
                    // now in front of a complete newline, move past an escape character
                    input->unget();
                    if (input->peek() == '\\')
                        input->unget();
                    else {
                        input->get();
                        break;
                    }
                } else
                    break;
            } while (true);
        }

    protected:
        TInputScanner* input;
    };

    // Holds a reference to included file data, as well as a 
    // prologue and an epilogue string. This can be scanned using the tInput
    // interface and acts as a single source string.
    class TokenizableIncludeFile : public tInput {
    public:
        // Copies prologue and epilogue. The includedFile must remain valid
        // until this TokenizableIncludeFile is no longer used.
        TokenizableIncludeFile(const TSourceLoc& startLoc,
                          const std::string& prologue,
                          TShader::IncludeResult includedFile,
                          const std::string& epilogue,
                          TPpContext* pp)
            : tInput(pp),
              prologue_(prologue),
              includedFile_(std::move(includedFile)),
              epilogue_(epilogue),
              scanner(3, strings, lengths, names, 0, 0, true),
              prevScanner(nullptr),
              stringInput(pp, scanner)
        {
              strings[0] = prologue_.data();
              strings[1] = includedFile_->getFileContents();
              strings[2] = epilogue_.data();

              lengths[0] = prologue_.size();
              lengths[1] = includedFile_->getFileContentsSize();
              lengths[2] = epilogue_.size();

              scanner.setLine(startLoc.line);
              scanner.setString(startLoc.string);

              scanner.setFile(startLoc.name, 0);
              scanner.setFile(startLoc.name, 1);
              scanner.setFile(startLoc.name, 2);
        }

        // tInput methods:
        int scan(TPpToken* t) override { return stringInput.scan(t); }
        int getch() override { return stringInput.getch(); }
        void ungetch() override { stringInput.ungetch(); }

        void notifyActivated() override
        {
            prevScanner = pp->parseContext.getScanner();
            pp->parseContext.setScanner(&scanner);
            pp->push_include(std::move(includedFile_));
        }

        void notifyDeleted() override
        {
            pp->parseContext.setScanner(prevScanner);
            includedFile_ = pp->pop_include();
        }

    private:
        // Stores the prologue for this string.
        const std::string prologue_;

        // Stores the epilogue for this string.
        const std::string epilogue_;

        // Stores to the IncludeResult that this TokenizableIncludeFile represents.
        TShader::IncludeResult includedFile_;

        // Will point to prologue_, includedFile_->file_data and epilogue_
        // This is passed to scanner constructor.
        // These do not own the storage and it must remain valid until this
        // object has been destroyed.
        const char* strings[3];
        // Length of str_, passed to scanner constructor.
        size_t lengths[3];
        // String names
        const char* names[3];
        // Scans over str_.
        TInputScanner scanner;
        // The previous effective scanner before the scanner in this instance
        // has been activated.
        TInputScanner* prevScanner;
        // Delegate object implementing the tInput interface.
        tStringInput stringInput;
    };

    int InitScanner();
    int ScanFromString(char* s);
    void missingEndifCheck();
    int lFloatConst(int len, int ch, TPpToken* ppToken);

    void push_include(TShader::IncludeResult result)
    {
        currentSourceFile = result->getFullFilePath();
        includeStack.push(std::move(result));
    }

    TShader::IncludeResult pop_include()
    {
        TShader::IncludeResult include = std::move(includeStack.top());
        includeStack.pop();
        if (includeStack.empty()) {
            currentSourceFile = rootFileName;
        } else {
            currentSourceFile = includeStack.top()->getFullFilePath();
        }
        return std::move(include);
    }

    bool inComment;

    //
    // From PpAtom.cpp
    //
    typedef TUnorderedMap<TString, int> TAtomMap;
    typedef TVector<const TString*> TStringMap;

    TAtomMap atomMap;
    TStringMap stringMap;
    std::stack<TShader::IncludeResult> includeStack;
    std::string currentSourceFile;
    std::string rootFileName;
    int nextAtom;
    void InitAtomTable();
    void AddAtomFixed(const char* s, int atom);
    int LookUpAddString(const char* s);
    const char* GetAtomString(int atom);

    //
    // From PpMemory.cpp
    //
    MemoryPool *mem_CreatePool(size_t chunksize, unsigned align);
    void mem_FreePool(MemoryPool*);
    void *mem_Alloc(MemoryPool* p, size_t size);
    int mem_AddCleanup(MemoryPool* p, void (*fn)(void *, void*), void* arg1, void* arg2);
};

} // end namespace glslang

#endif  // PPCONTEXT_H
