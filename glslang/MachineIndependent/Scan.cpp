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

#include <string.h>

#include "Scan.h"

namespace glslang {
    
// read past any white space
void ConsumeWhiteSpace(TInputScanner& input, bool& foundNonSpaceTab)
{
    char c = input.peek();  // don't accidentally consume anything other than whitespace
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        if (c == '\r' || c == '\n')
            foundNonSpaceTab = true;
        input.get();
        c = input.peek();
    }
}

// return true if a comment was actually consumed
bool ConsumeComment(TInputScanner& input)
{
    if (input.peek() != '/')
        return false;

    input.get();  // consume the '/'
    char c = input.peek();
    if (c == '/') {

        // a '//' style comment
        input.get();  // consume the second '/'
        c = input.get();
        do {
            while (c > 0 && c != '\\' && c != '\r' && c != '\n')
                c = input.get();

            if (c <= 0 || c == '\r' || c == '\n') {
                while (c == '\r' || c == '\n')
                    c = input.get();

                // we reached the end of the comment
                break;
            } else {
                // it's a '\', so we need to keep going, after skipping what's escaped
                    
                // read the skipped character
                c = input.get();

                // if it's a two-character newline, skip both characters
                if (c == '\r' && input.peek() == '\n')
                    input.get();
                c = input.get();
            }
        } while (true);

        // put back the last non-comment character
        if (c > 0)
            input.unget();

        return true;
    } else if (c == '*') {

        // a '/*' style comment
        input.get();  // consume the '*'
        c = input.get();
        do {
            while (c > 0 && c != '*')
                c = input.get();
            if (c == '*') {
                c = input.get();
                if (c == '/')
                    break;  // end of comment
                // not end of comment
            } else // end of input
                break;
        } while (true);

        return true;
    } else {
        // it's not a comment, put the '/' back
        input.unget();

        return false;
    }
}

// skip whitespace, then skip a comment, rinse, repeat
void ConsumeWhitespaceComment(TInputScanner& input, bool& foundNonSpaceTab)
{
    do {
        ConsumeWhiteSpace(input, foundNonSpaceTab);
 
        // if not starting a comment now, then done
        char c = input.peek();
        if (c != '/' || c < 0)
            return;

        // skip potential comment 
        foundNonSpaceTab = true;
        if (! ConsumeComment(input))
            return;

    } while (true);
}

// Returns true if there was non-white space (e.g., a comment, newline) before the #version;
// otherwise, returns true.
//
// N.B. does not attempt to leave input in any particular known state
bool ScanVersion(TInputScanner& input, int& version, EProfile& profile)
{
    // This function doesn't have to get all the semantics correct, 
    // just find the #version if there is a correct one present.
    // The preprocessor will have the responsibility of getting all the semantics right.

    version = 0;  // means not found
    profile = ENoProfile;

    bool foundNonSpaceTab = false;
    ConsumeWhitespaceComment(input, foundNonSpaceTab);

    // #
    if (input.get() != '#')
        return true;

    // whitespace
    char c;
    do {
        c = input.get();
    } while (c == ' ' || c == '\t');

    if (          c != 'v' ||
        input.get() != 'e' ||
        input.get() != 'r' ||
        input.get() != 's' ||
        input.get() != 'i' ||
        input.get() != 'o' ||
        input.get() != 'n')
        return true;

    // whitespace
    do {
        c = input.get();
    } while (c == ' ' || c == '\t');

    // version number
    while (c >= '0' && c <= '9') {
        version = 10 * version + (c - '0');
        c = input.get();
    }
    if (version == 0)
        return true;
    
    // whitespace
    while (c == ' ' || c == '\t')
        c = input.get();

    // profile
    const int maxProfileLength = 13;  // not including any 0
    char profileString[maxProfileLength];
    int profileLength;
    for (profileLength = 0; profileLength < maxProfileLength; ++profileLength) {
        if (c < 0 || c == ' ' || c == '\t' || c == '\n' || c == '\r')
            break;
        profileString[profileLength] = c;
        c = input.get();
    }
    if (c > 0 && c != ' ' && c != '\t' && c != '\n' && c != '\r')
        return true;

    if (profileLength == 2 && strncmp(profileString, "es", profileLength) == 0)
        profile = EEsProfile;
    else if (profileLength == 4 && strncmp(profileString, "core", profileLength) == 0)
        profile = ECoreProfile;
    else if (profileLength == 13 && strncmp(profileString, "compatibility", profileLength) == 0)
        profile = ECompatibilityProfile;

    return foundNonSpaceTab;
}

}; // end glslang namespace
