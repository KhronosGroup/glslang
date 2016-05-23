//
//Copyright (C) 2016 LunarG, Inc.
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

//
// Create strings that declare built-in definitions, add built-ins programmatically 
// that cannot be expressed in the strings, and establish mappings between
// built-in functions and operators.
//
// Where to put a built-in:
//   TBuiltInParseablesHlsl::initialize(version,profile) context-independent textual built-ins; add them to the right string
//   TBuiltInParseablesHlsl::initialize(resources,...)   context-dependent textual built-ins; add them to the right string
//   TBuiltInParseablesHlsl::identifyBuiltIns(...,symbolTable) context-independent programmatic additions/mappings to the symbol table,
//                                                including identifying what extensions are needed if a version does not allow a symbol
//   TBuiltInParseablesHlsl::identifyBuiltIns(...,symbolTable, resources) context-dependent programmatic additions/mappings to the
//                                                symbol table, including identifying what extensions are needed if a version does
//                                                not allow a symbol
//

#include "hlslParseables.h"

namespace glslang {

TBuiltInParseablesHlsl::TBuiltInParseablesHlsl()
{
    assert(0 && "Unimplemented TBuiltInParseablesHlsl::TBuiltInParseablesHlsl");
}

//
// Add all context-independent built-in functions and variables that are present
// for the given version and profile.  Share common ones across stages, otherwise
// make stage-specific entries.
//
// Most built-ins variables can be added as simple text strings.  Some need to
// be added programmatically, which is done later in IdentifyBuiltIns() below.
//
void TBuiltInParseablesHlsl::initialize(int version, EProfile profile, int spv, int vulkan)
{
    assert(0 && "Unimplemented TBuiltInParseablesHlsl::initialize");
}

//
// Add context-dependent built-in functions and variables that are present
// for the given version and profile.  All the results are put into just the
// commonBuiltins, because it is called for just a specific stage.  So,
// add stage-specific entries to the commonBuiltins, and only if that stage
// was requested.
//
void TBuiltInParseablesHlsl::initialize(const TBuiltInResource &resources, int version, EProfile profile, int spv,
                                        int vulkan, EShLanguage language)
{
    assert(0 && "Unimplemented TBuiltInParseablesHlsl::initialize");
}


//
// Finish adding/processing context-independent built-in symbols.
// 1) Programmatically add symbols that could not be added by simple text strings above.
// 2) Map built-in functions to operators, for those that will turn into an operation node
//    instead of remaining a function call.
// 3) Tag extension-related symbols added to their base version with their extensions, so
//    that if an early version has the extension turned off, there is an error reported on use.
//
void TBuiltInParseablesHlsl::identifyBuiltIns(int version, EProfile profile, int spv, int vulkan, EShLanguage language,
                                              TSymbolTable& symbolTable)
{
    assert(0 && "Unimplemented TBuiltInParseablesHlsl::identifyBuiltIns");
}

//
// Add context-dependent (resource-specific) built-ins not handled by the above.  These
// would be ones that need to be programmatically added because they cannot 
// be added by simple text strings.  For these, also
// 1) Map built-in functions to operators, for those that will turn into an operation node
//    instead of remaining a function call.
// 2) Tag extension-related symbols added to their base version with their extensions, so
//    that if an early version has the extension turned off, there is an error reported on use.
//
void TBuiltInParseablesHlsl::identifyBuiltIns(int version, EProfile profile, int spv, int /*vulkan*/, EShLanguage language,
                                              TSymbolTable& symbolTable, const TBuiltInResource &resources)
{
    assert(0 && "Unimplemented TBuiltInParseablesHlsl::identifyBuiltIns");
}


} // end namespace glslang
