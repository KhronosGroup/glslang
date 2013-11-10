//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2013 LunarG, Inc.
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
#ifndef _GLSLANG_SCAN_INCLUDED_
#define _GLSLANG_SCAN_INCLUDED_

#include "Versions.h"

namespace glslang {

//
// A character scanner that seamlessly, on read-only strings, reads across an
// array of strings without assuming null termination.
//
class TInputScanner {
public:
    TInputScanner(int n, const char* const s[], size_t L[], int b = 0, int f = 0) : 
        numSources(n), sources(s), lengths(L), currentSource(0), currentChar(0), stringBias(b), finale(f)
    {
        loc = new TSourceLoc[numSources];
        loc[currentSource].string = -stringBias;
        loc[currentSource].line = 1;
    }
    virtual ~TInputScanner()
    {
        delete [] loc;
    }

    // return of -1 means end of strings,
    // anything else is the next character

    // retrieve the next character and advance one character
    char get()
    {
        if (currentSource >= numSources)
            return -1;

        char ret = sources[currentSource][currentChar];
        if (ret == '\n')
            ++loc[currentSource].line;
        advance();

        return ret;
    }

    // retrieve the next character, no advance
    char peek()
    {
        if (currentSource >= numSources)
            return -1;

        return sources[currentSource][currentChar];
    }

    // go back one character
    void unget()
    {
        if (currentChar > 0)
            --currentChar;
        else {
            do {
                --currentSource;
            } while (currentSource > 0 && lengths[currentSource] == 0);
            currentChar = lengths[currentSource] - 1;
            if (currentChar < 0)
                currentChar = 0;
        }
        if (peek() == '\n')
            --loc[currentSource].line;
    }

    // for #line override
    void setLine(int newLine) { loc[currentSource].line = newLine; }
    void setString(int newString) { loc[currentSource].string = newString; }

    const TSourceLoc& getSourceLoc() const { return loc[std::max(0, std::min(currentSource, numSources - finale - 1))]; }

    void consumeWhiteSpace(bool& foundNonSpaceTab);
    bool consumeComment();
    void consumeWhitespaceComment(bool& foundNonSpaceTab);
    bool scanVersion(int& version, EProfile& profile);

protected:

    // advance one character
    void advance()
    {
        ++currentChar;
        if (currentChar >= static_cast<int>(lengths[currentSource])) {
            ++currentSource;
            if (currentSource < numSources) {
                loc[currentSource].string = loc[currentSource - 1].string + 1;
                loc[currentSource].line = 1;
            }
            while (currentSource < numSources && lengths[currentSource] == 0) {
                ++currentSource;
                if (currentSource < numSources) {
                    loc[currentSource].string = loc[currentSource - 1].string + 1;
                    loc[currentSource].line = 1;
                }
            }
            currentChar = 0;
        }
    }

    int numSources;             // number of strings in source
    const char* const *sources; // array of strings
    const size_t *lengths;      // length of each string
    int currentSource;
    int currentChar;

    // This is for reporting what string/line an error occurred on, and can be overridden by #line.
    // It remembers the last state of each source string as it is left for the next one, so unget() 
    // can restore that state.
    TSourceLoc* loc;  // an array

    int stringBias;   // the first string that is the user's string number 0
    int finale;       // number of internal strings after user's last string
};

} // end namespace glslang

#endif // _GLSLANG_SCAN_INCLUDED_
