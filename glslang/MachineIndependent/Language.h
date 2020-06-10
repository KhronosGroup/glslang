//
// Copyright (C) 2020 Google, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
#ifndef _GLSLANG_LANGUAGE_INCLUDED_
#define _GLSLANG_LANGUAGE_INCLUDED_

#include "Initialize.h"

namespace glslang {

class TParseContextBase;

// Language is an interface implemented by a source language.
// Languages are registered by source (EShSource).
class Language {
public:
    virtual ~Language() {}

    // Register() registers the language.
    static void Register(Language*);

    // Get() returns the registered language for the given source type.
    static Language* Get(EShSource source);

    // InitializeAll() initializes all the registered languages.
    static void InitializeAll();

    // TerminateAll() terminates all the registered languages.
    static void TerminateAll();

    // Initialize() initializes the language.
    // Must be called, once, before any other method (with exception to Source()).
    virtual void Initialize() = 0;

    // Terminate() terminates the language.
    // Must be called, once, before process termination.
    // No method may be called after calling.
    virtual void Terminate() = 0;

    // Source() returns the EShSource that this language implements.
    virtual EShSource Source() const = 0;

    // CreateBuiltInParseables() constructs and returns the parseable strings
    // for the given language.
    virtual TBuiltInParseables* CreateBuiltInParseables(TInfoSink& infoSink) = 0;

    // CreateParseContext() constructs and returns the parse context for the
    // given language.
    virtual TParseContextBase* CreateParseContext(TSymbolTable& symbolTable, TIntermediate& intermediate,
                                      int version, EProfile profile,
                                      EShLanguage language, TInfoSink& infoSink,
                                      SpvVersion spvVersion, bool forwardCompatible, EShMessages messages,
                                      bool parsingBuiltIns, std::string sourceEntryPointName) = 0;
};

} // end namespace glslang

#endif // _GLSLANG_LANGUAGE_INCLUDED_
