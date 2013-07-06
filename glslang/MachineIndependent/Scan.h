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

#include "Versions.h"

namespace glslang {
    
//
// A character scanner that seamlessly, on read-only strings, reads across an
// array of strings without assuming null termination.
//
class TInputScanner {
public:
    TInputScanner(int n, const char* const i[], int L[]) : numSources(n), sources(i), lengths(L), currentSource(0), currentChar(0) { }

    // return of -1 means end of strings,
    // anything else is the next character

    // retrieve the next character and advance one character
    char get()
    {
        if (currentSource >= numSources)
            return -1;

        char ret = sources[currentSource][currentChar];
        advance();

        return ret;
    }

    // advance one character
    void advance()
    {
        ++currentChar;
        if (currentChar >= lengths[currentSource]) {
            ++currentSource;
            currentChar = 0;
            while (currentSource < numSources && lengths[currentSource] == 0)
                ++currentSource;
        }
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
    }

protected:
    int numSources;             // number of strings in source
    const char* const *sources; // array of strings
    const int *lengths;         // length of each string
    int currentSource;
    int currentChar;
};

// TODO: The location of these is still pending a grand design for going to a singular
// scanner for version finding, preprocessing, and tokenizing:
void ConsumeWhiteSpace(TInputScanner& input, bool& foundNonSpaceTab);
bool ConsumeComment(TInputScanner& input);
void ConsumeWhitespaceComment(TInputScanner& input, bool& foundNonSpaceTab);
bool ScanVersion(TInputScanner& input, int& version, EProfile& profile);

}; // end glslang namespace
