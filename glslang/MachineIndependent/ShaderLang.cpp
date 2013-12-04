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

//
// Implement the top-level of interface to the compiler/linker,
// as defined in ShaderLang.h
// This is the platform independent interface between an OGL driver
// and the shading language compiler/linker.
//
#include <string.h>
#include "SymbolTable.h"
#include "ParseHelper.h"
#include "Scan.h"
#include "ScanContext.h"

#include "../Include/ShHandle.h"
#include "InitializeDll.h"

#include "preprocessor/PpContext.h"

#define SH_EXPORTING
#include "../Public/ShaderLang.h"
#include "reflection.h"
#include "Initialize.h"

namespace { // anonymous namespace for file-local functions and symbols

using namespace glslang;

// Local mapping functions for making arrays of symbol tables....

int MapVersionToIndex(int version)
{
        switch (version) {
        case 100: return  0;
        case 110: return  1;
        case 120: return  2;
        case 130: return  3;
        case 140: return  4;
        case 150: return  5;
        case 300: return  6;
        case 330: return  7;
        case 400: return  8;
        case 410: return  9;
        case 420: return 10;
        case 430: return 11;
        case 440: return 12;
        default:       // |
            return  0; // |
        }              // |
}                      // V
const int VersionCount = 13;  // number of case statements above

int MapProfileToIndex(EProfile profile)
{
    switch (profile) {
    case ENoProfile:             return 0;
    case ECoreProfile:           return 1;
    case ECompatibilityProfile:  return 2;
    case EEsProfile:             return 3;
    default:                         // |
        return 0;                    // |
    }                                // |
}                                    // V
const int ProfileCount                = 4;   // number of case statements above

// only one of these needed for non-ES; ES needs 2 for different precision defaults of built-ins
enum EPrecisionClass {
    EPcGeneral,
    EPcFragment,
    EPcCount
};

// A process-global symbol table per version per profile for built-ins common 
// to multiple stages (languages), and a process-global symbol table per version 
// per profile per stage for built-ins unique to each stage.  They will be sparsely
// populated, so they will only only be generated as needed.
// 
// Each has a different set of built-ins, and we want to preserve that from
// compile to compile.
//
TSymbolTable* CommonSymbolTable[VersionCount][ProfileCount][EPcCount] = {};
TSymbolTable* SharedSymbolTables[VersionCount][ProfileCount][EShLangCount] = {};

TPoolAllocator* PerProcessGPA = 0;

//
// Parse and add to the given symbol table the content of the given shader string.
//
bool InitializeSymbolTable(const TString& builtIns, int version, EProfile profile, EShLanguage language, TInfoSink& infoSink, 
                           TSymbolTable& symbolTable)
{
    TIntermediate intermediate(language, version, profile);
	
    TParseContext parseContext(symbolTable, intermediate, true, version, profile, language, infoSink);
    TPpContext ppContext(parseContext);
    TScanContext scanContext(parseContext);
    parseContext.setScanContext(&scanContext);
    parseContext.setPpContext(&ppContext);
    
    //
    // Push the symbol table to give it an initial scope.  This
    // push should not have a corresponding pop, so that built-ins
    // are preserved, and the test for an empty table fails.
    //

    symbolTable.push();

    const char* builtInShaders[2];
    size_t builtInLengths[2];
    builtInShaders[0] = builtIns.c_str();
    builtInLengths[0] = builtIns.size();

    TInputScanner input(1, builtInShaders, builtInLengths);
    if (! parseContext.parseShaderStrings(ppContext, input) != 0) {
        infoSink.info.message(EPrefixInternalError, "Unable to parse built-ins");
        printf("Unable to parse built-ins\n%s\n", infoSink.info.c_str());

        return false;
    }

    return true;
}

int CommonIndex(EProfile profile, EShLanguage language)
{
    return (profile == EEsProfile && language == EShLangFragment) ? EPcFragment : EPcGeneral;
}

//
// To initialize per-stage shared tables, with the common table already complete.
//
void InitializeStageSymbolTable(TBuiltIns& builtIns, int version, EProfile profile, EShLanguage language, TInfoSink& infoSink, TSymbolTable** commonTable, TSymbolTable** symbolTables)
{
    (*symbolTables[language]).adoptLevels(*commonTable[CommonIndex(profile, language)]);
    InitializeSymbolTable(builtIns.getStageString(language), version, profile, language, infoSink, *symbolTables[language]);
    IdentifyBuiltIns(version, profile, language, *symbolTables[language]);
    if (profile == EEsProfile && version >= 300)
        (*symbolTables[language]).setNoBuiltInRedeclarations();
}

//
// Initialize the full set of shareable symbol tables;
// The common (cross-stage) and those sharable per-stage.
//
bool InitializeSymbolTables(TInfoSink& infoSink, TSymbolTable** commonTable,  TSymbolTable** symbolTables, int version, EProfile profile)
{
    TBuiltIns builtIns;
	builtIns.initialize(version, profile);

    // do the common tables
    InitializeSymbolTable(builtIns.getCommonString(), version, profile, EShLangVertex, infoSink, *commonTable[EPcGeneral]);
    if (profile == EEsProfile)
        InitializeSymbolTable(builtIns.getCommonString(), version, profile, EShLangFragment, infoSink, *commonTable[EPcFragment]);

    // do the per-stage tables
    InitializeStageSymbolTable(builtIns, version, profile, EShLangVertex, infoSink, commonTable, symbolTables);
    InitializeStageSymbolTable(builtIns, version, profile, EShLangFragment, infoSink, commonTable, symbolTables);
    if (profile != EEsProfile && version >= 400) {
        InitializeStageSymbolTable(builtIns, version, profile, EShLangTessControl, infoSink, commonTable, symbolTables);
        InitializeStageSymbolTable(builtIns, version, profile, EShLangTessEvaluation, infoSink, commonTable, symbolTables);
    }
    if (profile != EEsProfile && version >= 150)
        InitializeStageSymbolTable(builtIns, version, profile, EShLangGeometry, infoSink, commonTable, symbolTables);
    if (profile != EEsProfile && version >= 430)
        InitializeStageSymbolTable(builtIns, version, profile, EShLangCompute, infoSink, commonTable, symbolTables);

    return true;
}

bool AddContextSpecificSymbols(const TBuiltInResource* resources, TInfoSink& infoSink, TSymbolTable& symbolTable, int version, EProfile profile, EShLanguage language)
{
    TBuiltIns builtIns;
    
	builtIns.initialize(*resources, version, profile, language);
    InitializeSymbolTable(builtIns.getCommonString(), version, profile, language, infoSink, symbolTable);
	IdentifyBuiltIns(version, profile, language, symbolTable, *resources);

    return true;
}

//
// To do this on the fly, we want to leave the current state of our thread's 
// pool allocator intact, so:
//  - Switch to a new pool for parsing the built-ins
//  - Do the parsing, which builds the symbol table, using the new pool
//  - Switch to the process-global pool to save a copy the resulting symbol table
//  - Free up the new pool used to parse the built-ins
//  - Switch back to the original thread's pool
//
// This only gets done the first time any thread needs a particular symbol table
// (lazy evaluation).
//
void SetupBuiltinSymbolTable(int version, EProfile profile)
{
    TInfoSink infoSink;

    // Make sure only one thread tries to do this at a time
    glslang::GetGlobalLock();

    // See if it's already been done for this version/profile combination
    int versionIndex = MapVersionToIndex(version);
    int profileIndex = MapProfileToIndex(profile);
    if (CommonSymbolTable[versionIndex][profileIndex][EPcGeneral]) {
        glslang::ReleaseGlobalLock();

        return;
    }

    // Switch to a new pool
    TPoolAllocator& previousAllocator = GetThreadPoolAllocator();
    TPoolAllocator* builtInPoolAllocator = new TPoolAllocator();
    SetThreadPoolAllocator(*builtInPoolAllocator);

    // Dynamically allocate the local symbol tables so we can control when they are deallocated WRT when the pool is popped.
    TSymbolTable* commonTable[EPcCount];
    TSymbolTable* stageTables[EShLangCount];
    for (int precClass = 0; precClass < EPcCount; ++precClass)
        commonTable[precClass] = new TSymbolTable;
    for (int stage = 0; stage < EShLangCount; ++stage)
        stageTables[stage] = new TSymbolTable;

    // Generate the local symbol tables using the new pool
    InitializeSymbolTables(infoSink, commonTable, stageTables, version, profile);

    // Switch to the process-global pool
    SetThreadPoolAllocator(*PerProcessGPA);

    // Copy the local symbol tables from the new pool to the global tables using the process-global pool
    for (int precClass = 0; precClass < EPcCount; ++precClass) {
        if (! commonTable[precClass]->isEmpty()) {
            CommonSymbolTable[versionIndex][profileIndex][precClass] = new TSymbolTable;
            CommonSymbolTable[versionIndex][profileIndex][precClass]->copyTable(*commonTable[precClass]);
            CommonSymbolTable[versionIndex][profileIndex][precClass]->readOnly();
        }
    }
    for (int stage = 0; stage < EShLangCount; ++stage) {
        if (! stageTables[stage]->isEmpty()) {
            SharedSymbolTables[versionIndex][profileIndex][stage] = new TSymbolTable;
            SharedSymbolTables[versionIndex][profileIndex][stage]->adoptLevels(*CommonSymbolTable[versionIndex][profileIndex][CommonIndex(profile, (EShLanguage)stage)]);
            SharedSymbolTables[versionIndex][profileIndex][stage]->copyTable(*stageTables[stage]);
            SharedSymbolTables[versionIndex][profileIndex][stage]->readOnly();
        }    
    }

    // Clean up the local tables before deleting the pool they used.
    for (int precClass = 0; precClass < EPcCount; ++precClass)
        delete commonTable[precClass];
    for (int stage = 0; stage < EShLangCount; ++stage)
        delete stageTables[stage];

    delete builtInPoolAllocator;
    SetThreadPoolAllocator(previousAllocator);

    glslang::ReleaseGlobalLock();
}

bool DeduceVersionProfile(TInfoSink& infoSink, EShLanguage stage, bool versionNotFirst, int defaultVersion, int& version, EProfile& profile)
{
    const int FirstProfileVersion = 150;
    bool correct = true;

    // Get a good version...
    if (version == 0) {
        version = defaultVersion;
        // infoSink.info.message(EPrefixWarning, "#version: statement missing; use #version on first line of shader");
    }

    // Get a good profile...
    if (profile == ENoProfile) {
        if (version == 300) {
            correct = false;
            infoSink.info.message(EPrefixError, "#version: version 300 requires specifying the 'es' profile");
            profile = EEsProfile;
        } else if (version == 100)
            profile = EEsProfile;
        else if (version >= FirstProfileVersion)
            profile = ECoreProfile;
        else
            profile = ENoProfile;
    } else {
        // a profile was provided...
        if (version < 150) {
            correct = false;
            infoSink.info.message(EPrefixError, "#version: versions before 150 do not allow a profile token");
            if (version == 100)
                profile = EEsProfile;
            else
                profile = ENoProfile;
        } else if (version == 300) {
            if (profile != EEsProfile) {
                correct = false;
                infoSink.info.message(EPrefixError, "#version: version 300 supports only the es profile");
            }
            profile = EEsProfile;
        } else {
            if (profile == EEsProfile) {
                correct = false;
                infoSink.info.message(EPrefixError, "#version: only version 300 supports the es profile");
                if (version >= FirstProfileVersion)
                    profile = ECoreProfile;
                else
                    profile = ENoProfile;
            } 
            // else: typical desktop case... e.g., "#version 410 core"
        }
    }

    // Correct for stage type...
    switch (stage) {
    case EShLangGeometry:
        if (version < 150 || (profile != ECoreProfile && profile != ECompatibilityProfile)) {
            correct = false;
            infoSink.info.message(EPrefixError, "#version: geometry shaders require non-es profile and version 150 or above");
            version = 150;
            profile = ECoreProfile;
        }
        break;
    case EShLangTessControl:
    case EShLangTessEvaluation:
        if (version < 400 || (profile != ECoreProfile && profile != ECompatibilityProfile)) {
            correct = false;
            infoSink.info.message(EPrefixError, "#version: tessellation shaders require non-es profile and version 400 or above");
            version = 400;
            profile = ECoreProfile;
        }
        break;
    case EShLangCompute:
        if (version < 430 || (profile != ECoreProfile && profile != ECompatibilityProfile)) {
            correct = false;
            infoSink.info.message(EPrefixError, "#version: compute shaders require non-es profile and version 430 or above");
            version = 430;
            profile = ECoreProfile;
        }
        break;
    default:
        break;
    }

    if (profile == EEsProfile && version >= 300 && versionNotFirst) {
        correct = false;
        infoSink.info.message(EPrefixError, "#version: statement must appear first in es-profile shader; before comments or newlines");
    }

    // A metecheck on the condition the compiler itself...
    switch(version) {
    case 100:
    case 300:

    case 110:
    case 120:
        // versions are complete
        break;
    case 130:
    case 140:
        infoSink.info << "Warning, version " << version << " is not yet complete; most features are present, but a few are missing.\n";
        break;
    default:
        infoSink.info << "Warning, version " << version << " is not yet complete; some version-specific features are present, but many are missing.\n";
        break;
    }

    return correct;
}

//
// Do a partial compile on the given strings for a single compilation unit
// for a potential deferred link into a single stage (and deferred full compile of that
// stage through machine-dependent compilation).
//
// All preprocessing, parsing, semantic checks, etc. for a single compilation unit
// are done here.
//
// Return:  The tree and other information is filled into the intermediate argument, 
//          and true is returned by the function for success.
//
bool CompileDeferred(
    TCompiler* compiler,
    const char* const shaderStrings[],
    const int numStrings,
    const int* inputLengths,
    const EShOptimizationLevel optLevel,
    const TBuiltInResource* resources,
    int defaultVersion,         // use 100 for ES environment, 110 for desktop
    bool forwardCompatible,     // give errors for use of deprecated features
    EShMessages messages,       // warnings/errors/AST; things to print out
    TIntermediate& intermediate // returned tree, etc.
    )
{
    if (! InitThread())
        return false;

    // This must be undone (.pop()) by the caller, after it finishes consuming the created tree.
    GetThreadPoolAllocator().push();

    if (numStrings == 0)
        return true;
    
    // Move to length-based strings, rather than null-terminated strings.
    // Also, add strings to include the preamble and to ensure the shader is not null,
    // which lets the grammar accept what was a null (post preprocessing) shader.
    //
    // Shader will look like
    //   string 0:                preamble
    //   string 1...numStrings:   user's shader
    //   string numStrings+1:     "int;"
    //
    size_t* lengths = new size_t[numStrings + 2];
    const char** strings = new const char*[numStrings + 2];
    for (int s = 0; s < numStrings; ++s) {
        strings[s + 1] = shaderStrings[s];
        if (inputLengths == 0 || inputLengths[s] < 0)
            lengths[s + 1] = strlen(shaderStrings[s]);
        else
            lengths[s + 1] = inputLengths[s];
    }

    // First, without using the preprocessor or parser, find the #version, so we know what
    // symbol tables, processing rules, etc. to set up.  This does not need the extra strings
    // outlined above, just the user shader.
    int version;
    EProfile profile;
    glslang::TInputScanner userInput(numStrings, &strings[1], &lengths[1]);  // no preamble
    bool versionNotFirst = userInput.scanVersion(version, profile);
    bool versionNotFound = version == 0;
    bool goodVersion = DeduceVersionProfile(compiler->infoSink, compiler->getLanguage(), versionNotFirst, defaultVersion, version, profile);
    bool versionWillBeError = (versionNotFound || (profile == EEsProfile && version >= 300 && versionNotFirst));
    
    intermediate.setVersion(version);
    intermediate.setProfile(profile);
    SetupBuiltinSymbolTable(version, profile);
    
    TSymbolTable* cachedTable = SharedSymbolTables[MapVersionToIndex(version)]
                                                  [MapProfileToIndex(profile)]
                                                  [compiler->getLanguage()];
    
    // Dynamically allocate the symbol table so we can control when it is deallocated WRT the pool.
    TSymbolTable* symbolTableMemory = new TSymbolTable;
    TSymbolTable& symbolTable = *symbolTableMemory;
    if (cachedTable)
        symbolTable.adoptLevels(*cachedTable);
    
    // Add built-in symbols that are potentially context dependent;
    // they get popped again further down.
    AddContextSpecificSymbols(resources, compiler->infoSink, symbolTable, version, profile, compiler->getLanguage());
    
    //
    // Now we can process the full shader under proper symbols and rules.
    //

    TParseContext parseContext(symbolTable, intermediate, false, version, profile, compiler->getLanguage(), compiler->infoSink, forwardCompatible, messages);
    glslang::TScanContext scanContext(parseContext);
    TPpContext ppContext(parseContext);
    parseContext.setScanContext(&scanContext);
    parseContext.setPpContext(&ppContext);
    parseContext.setLimits(*resources);
    if (! goodVersion)
        parseContext.addError();

    parseContext.initializeExtensionBehavior();

    bool success = true;
    
    // Fill in the strings as outlined above.
    strings[0] = parseContext.getPreamble();
    lengths[0] = strlen(strings[0]);
    strings[numStrings + 1] = "\n int;";
    lengths[numStrings + 1] = strlen(strings[numStrings + 1]);
    TInputScanner fullInput(numStrings + 2, strings, lengths, 1, 1);

    // Push a new symbol allocation scope that will get used for the shader's globals.
    symbolTable.push();

    // Parse the full shader.
    if (! parseContext.parseShaderStrings(ppContext, fullInput, versionWillBeError))
        success = false;
    intermediate.addSymbolLinkageNodes(parseContext.linkage, parseContext.language, symbolTable);

    // Clean up the symbol table. The AST is self-sufficient now.
    delete symbolTableMemory;

    if (success && intermediate.getTreeRoot()) {
        if (optLevel == EShOptNoGeneration)
            parseContext.infoSink.info.message(EPrefixNone, "No errors.  No code generation or linking was requested.");
        else
            success = intermediate.postProcess(intermediate.getTreeRoot(), parseContext.language);
    } else if (! success) {
        parseContext.infoSink.info.prefix(EPrefixError);
        parseContext.infoSink.info << parseContext.getNumErrors() << " compilation errors.  No code generated.\n\n";
    }

    if (messages & EShMsgAST)
        intermediate.outputTree(parseContext.infoSink);

    delete [] lengths;
    delete [] strings;

    return success;
}

} // end anonymous namespace for local functions


//
// ShInitialize() should be called exactly once per process, not per thread.
//
int ShInitialize()
{
    glslang::InitGlobalLock();

    if (! InitProcess())
        return 0;

    if (! PerProcessGPA)
        PerProcessGPA = new TPoolAllocator();
    
    glslang::TScanContext::fillInKeywordMap();

    return 1;
}

//
// Driver calls these to create and destroy compiler/linker
// objects.
//

ShHandle ShConstructCompiler(const EShLanguage language, int debugOptions)
{
    if (!InitThread())
        return 0;

    TShHandleBase* base = static_cast<TShHandleBase*>(ConstructCompiler(language, debugOptions));
    
    return reinterpret_cast<void*>(base);
}

ShHandle ShConstructLinker(const EShExecutable executable, int debugOptions)
{
    if (!InitThread())
        return 0;

    TShHandleBase* base = static_cast<TShHandleBase*>(ConstructLinker(executable, debugOptions));

    return reinterpret_cast<void*>(base);
}

ShHandle ShConstructUniformMap()
{
    if (!InitThread())
        return 0;

    TShHandleBase* base = static_cast<TShHandleBase*>(ConstructUniformMap());

    return reinterpret_cast<void*>(base);
}

void ShDestruct(ShHandle handle)
{
    if (handle == 0)
        return;

    TShHandleBase* base = static_cast<TShHandleBase*>(handle);

    if (base->getAsCompiler())
        DeleteCompiler(base->getAsCompiler());
    else if (base->getAsLinker())
        DeleteLinker(base->getAsLinker());
    else if (base->getAsUniformMap())
        DeleteUniformMap(base->getAsUniformMap());
}

//
// Cleanup symbol tables
//
int __fastcall ShFinalize()
{
    for (int version = 0; version < VersionCount; ++version)
        for (int p = 0; p < ProfileCount; ++p)
            for (int lang = 0; lang < EShLangCount; ++lang)
                delete SharedSymbolTables[version][p][lang];

    if (PerProcessGPA) {
        PerProcessGPA->popAll();
        delete PerProcessGPA;
    }

    return 1;
}

//
// Do a full compile on the given strings for a single compilation unit
// forming a complete stage.  The result of the machine dependent compilation
// is left in the provided compile object.
//
// Return:  The return value is really boolean, indicating
// success (1) or failure (0).
//
int ShCompile(
    const ShHandle handle,
    const char* const shaderStrings[],
    const int numStrings,
    const int* inputLengths,
    const EShOptimizationLevel optLevel,
    const TBuiltInResource* resources,
    int debugOptions,          // currently unused
    int defaultVersion,        // use 100 for ES environment, 110 for desktop
    bool forwardCompatible,    // give errors for use of deprecated features
    EShMessages messages       // warnings/errors/AST; things to print out
    )
{
    // Map the generic handle to the C++ object
    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TCompiler* compiler = base->getAsCompiler();
    if (compiler == 0)
        return 0;

    compiler->infoSink.info.erase();
    compiler->infoSink.debug.erase();

    TIntermediate intermediate(compiler->getLanguage());
    bool success = CompileDeferred(compiler, shaderStrings, numStrings, inputLengths, optLevel, resources, defaultVersion, forwardCompatible, messages, intermediate);

    //
    // Call the machine dependent compiler
    //
    if (success && intermediate.getTreeRoot() && optLevel != EShOptNoGeneration)
        success = compiler->compile(intermediate.getTreeRoot(), intermediate.getVersion(), intermediate.getProfile());

    intermediate.removeTree();

    // Throw away all the temporary memory used by the compilation process.
    // The push was done in the CompileDeferred() call above.
    GetThreadPoolAllocator().pop();

    return success ? 1 : 0;
}

//
// Link the given compile objects.
//
// Return:  The return value of is really boolean, indicating
// success or failure.
//
int ShLink(
    const ShHandle linkHandle,
    const ShHandle compHandles[],
    const int numHandles,
    ShHandle uniformMapHandle,
    short int** uniformsAccessed,
    int* numUniformsAccessed)

{
    if (!InitThread())
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(linkHandle);
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());
    if (linker == 0)
        return 0;

    int returnValue;
    GetThreadPoolAllocator().push();
    returnValue = ShLinkExt(linkHandle, compHandles, numHandles);
    GetThreadPoolAllocator().pop();

    if (returnValue)
        return 1;

    return 0;
}
//
// This link method will be eventually used once the ICD supports the new linker interface
//
int ShLinkExt(
    const ShHandle linkHandle,
    const ShHandle compHandles[],
    const int numHandles)
{
    if (linkHandle == 0 || numHandles == 0)
        return 0;

    THandleList cObjects;

    for (int i = 0; i < numHandles; ++i) {
        if (compHandles[i] == 0)
            return 0;
        TShHandleBase* base = reinterpret_cast<TShHandleBase*>(compHandles[i]);
        if (base->getAsLinker()) {
            cObjects.push_back(base->getAsLinker());
        }
        if (base->getAsCompiler())
            cObjects.push_back(base->getAsCompiler());
    
    
        if (cObjects[i] == 0)
            return 0;
    }

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(linkHandle);
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());

    if (linker == 0)
        return 0;

    linker->infoSink.info.erase();

    for (int i = 0; i < numHandles; ++i) {
        if (cObjects[i]->getAsCompiler()) {
            if (! cObjects[i]->getAsCompiler()->linkable()) {
                linker->infoSink.info.message(EPrefixError, "Not all shaders have valid object code.");                
                return 0;
            }
        }
    }

    bool ret = linker->link(cObjects);

    return ret ? 1 : 0;
}

//
// ShSetEncrpytionMethod is a place-holder for specifying
// how source code is encrypted.
//
void ShSetEncryptionMethod(ShHandle handle)
{
    if (handle == 0)
        return;
}

//
// Return any compiler/linker/uniformmap log of messages for the application.
//
const char* ShGetInfoLog(const ShHandle handle)
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;

    TShHandleBase* base = static_cast<TShHandleBase*>(handle);
    TInfoSink* infoSink;

    if (base->getAsCompiler())
        infoSink = &(base->getAsCompiler()->getInfoSink());
    else if (base->getAsLinker())
        infoSink = &(base->getAsLinker()->getInfoSink());

    infoSink->info << infoSink->debug.c_str();
    return infoSink->info.c_str();
}

//
// Return the resulting binary code from the link process.  Structure
// is machine dependent.
//
const void* ShGetExecutable(const ShHandle handle)
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());
    if (linker == 0)
        return 0;

    return linker->getObjectCode();
}

//
// Let the linker know where the application said it's attributes are bound.
// The linker does not use these values, they are remapped by the ICD or
// hardware.  It just needs them to know what's aliased.
//
// Return:  The return value of is really boolean, indicating
// success or failure.
//
int ShSetVirtualAttributeBindings(const ShHandle handle, const ShBindingTable* table)
{    
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());

    if (linker == 0)
        return 0;
   
    linker->setAppAttributeBindings(table);

    return 1;
}

//
// Let the linker know where the predefined attributes have to live.
//
int ShSetFixedAttributeBindings(const ShHandle handle, const ShBindingTable* table)
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());

    if (linker == 0)
        return 0;

    linker->setFixedAttributeBindings(table);
    return 1;
}

//
// Some attribute locations are off-limits to the linker...
//
int ShExcludeAttributes(const ShHandle handle, int *attributes, int count)
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TLinker* linker = static_cast<TLinker*>(base->getAsLinker());
    if (linker == 0)
        return 0;

    linker->setExcludedAttributes(attributes, count);

    return 1;
}

//
// Return the index for OpenGL to use for knowing where a uniform lives.
//
// Return:  The return value of is really boolean, indicating
// success or failure.
//
int ShGetUniformLocation(const ShHandle handle, const char* name)
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return -1;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TUniformMap* uniformMap= base->getAsUniformMap();
    if (uniformMap == 0)
        return -1;

    return uniformMap->getLocation(name);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// Deferred-Lowering C++ Interface
// -----------------------------------
//
// Below is a new alternate C++ interface that might potentially replace the above
// opaque handle-based interface.
//    
// See more detailed comment in ShaderLang.h
//

namespace glslang {

#include "../Include/revision.h"

const char* GetEsslVersionString()
{
    return "OpenGL ES GLSL 3.00 glslang LunarG Khronos." GLSLANG_REVISION " " GLSLANG_DATE;
}

const char* GetGlslVersionString()
{
    return "4.20 glslang LunarG Khronos." GLSLANG_REVISION " " GLSLANG_DATE;
}

bool InitializeProcess()
{
    return ShInitialize() != 0;
}

void FinalizeProcess()
{
    ShFinalize();
}

class TDeferredCompiler : public TCompiler {
public:
    TDeferredCompiler(EShLanguage s, TInfoSink& i) : TCompiler(s, i) { }
    virtual bool compile(TIntermNode* root, int version = 0, EProfile profile = ENoProfile) { return true; }
};

TShader::TShader(EShLanguage s) 
    : pool(0), stage(s)
{
    infoSink = new TInfoSink;
    compiler = new TDeferredCompiler(stage, *infoSink);
    intermediate = new TIntermediate(s);
}

TShader::~TShader()
{
    delete infoSink;
    delete compiler;
    delete intermediate;
    delete pool;
}

//
// Turn the shader strings into a parse tree in the TIntermediate.
//
// Returns true for success.
//
bool TShader::parse(const TBuiltInResource* builtInResources, int defaultVersion, bool forwardCompatible, EShMessages messages)
{
    if (! InitThread())
        return false;
    
    pool = new TPoolAllocator();
    SetThreadPoolAllocator(*pool);

    return CompileDeferred(compiler, strings, numStrings, 0, EShOptNone, builtInResources, defaultVersion, forwardCompatible, messages, *intermediate);
}

const char* TShader::getInfoLog()
{
    return infoSink->info.c_str();
}

const char* TShader::getInfoDebugLog()
{
    return infoSink->debug.c_str();
}

TProgram::TProgram() : pool(0), reflection(0), linked(false)
{
    infoSink = new TInfoSink;
    for (int s = 0; s < EShLangCount; ++s) {
        intermediate[s] = 0;
        newedIntermediate[s] = false;
    }
}

TProgram::~TProgram()
{
    delete infoSink;
    delete reflection;

    for (int s = 0; s < EShLangCount; ++s)
        if (newedIntermediate[s])
            delete intermediate[s];

    delete pool;
}

//
// Merge the compilation units within each stage into a single TIntermediate.
// All starting compilation units need to be the result of calling TShader::parse().
//
// Return true for success.
//
bool TProgram::link(EShMessages messages)
{
    if (linked)
        return false;
    linked = true;

    bool error = false;
    
    pool = new TPoolAllocator();
    SetThreadPoolAllocator(*pool);

    for (int s = 0; s < EShLangCount; ++s) {
        if (! linkStage((EShLanguage)s, messages))
            error = true;
    }

    // TODO: Link: cross-stage error checking

    return ! error;
}

//
// Merge the compilation units within the given stage into a single TIntermediate.
//
// Return true for success.
//
bool TProgram::linkStage(EShLanguage stage, EShMessages messages)
{
    if (stages[stage].size() == 0)
        return true;

    //
    // Be efficient for the common single compilation unit per stage case,
    // reusing it's TIntermediate instead of merging into a new one.
    //
    if (stages[stage].size() == 1)
        intermediate[stage] = stages[stage].front()->intermediate;
    else {
        intermediate[stage] = new TIntermediate(stage);
        newedIntermediate[stage] = true;
    }

    infoSink->info << "\nLinked " << StageName(stage) << " stage:\n\n";

    if (stages[stage].size() > 1) {
        std::list<TShader*>::const_iterator it;
        for (it = stages[stage].begin(); it != stages[stage].end(); ++it)
            intermediate[stage]->merge(*infoSink, *(*it)->intermediate);

        if (messages & EShMsgAST)
            intermediate[stage]->outputTree(*infoSink);
    }

    intermediate[stage]->errorCheck(*infoSink);

    return intermediate[stage]->getNumErrors() == 0;
}

const char* TProgram::getInfoLog()
{
    return infoSink->info.c_str();
}

const char* TProgram::getInfoDebugLog()
{
    return infoSink->debug.c_str();
}

//
// Reflection implementation.
//

bool TProgram::buildReflection()
{    
    if (! linked || reflection)
        return false;

    reflection = new TReflection;

    for (int s = 0; s < EShLangCount; ++s) {
        if (intermediate[s]) {
            if (! reflection->addStage((EShLanguage)s, *intermediate[s]))
                return false;
        }
    }

    return true;
}

int TProgram::getNumLiveUniformVariables()           { return reflection->getNumUniforms(); }
int TProgram::getNumLiveUniformBlocks()              { return reflection->getNumUniformBlocks(); }
const char* TProgram::getUniformName(int index)      { return reflection->getUniform(index).name.c_str(); }
const char* TProgram::getUniformBlockName(int index) { return reflection->getUniformBlock(index).name.c_str(); }
int TProgram::getUniformBlockSize(int index)         { return reflection->getUniformBlock(index).size; }
int TProgram::getUniformIndex(const char* name)      { return reflection->getIndex(name); }
int TProgram::getUniformBlockIndex(int index)        { return reflection->getUniform(index).index; }
int TProgram::getUniformType(int index)              { return reflection->getUniform(index).glDefineType; }
int TProgram::getUniformBufferOffset(int index)      { return reflection->getUniform(index).offset; }
int TProgram::getUniformArraySize(int index)         { return reflection->getUniform(index).size; }

void TProgram::dumpReflection()                      { reflection->dump(); }

} // end namespace glslang
