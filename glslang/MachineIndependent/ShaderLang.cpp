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

#include "SymbolTable.h"
#include "ParseHelper.h"

#include "../Include/ShHandle.h"
#include "InitializeDll.h"

#define SH_EXPORTING
#include "../Public/ShaderLang.h"
#include "Initialize.h"

namespace { // anonymous namespace for file-local functions and symbols

int MapVersionToIndex(int version)
{
        switch(version) {
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
        default:  //      |
            return  0; // |
        }         //      |
}                 //      V
const int VersionCount = 12;

//
// A symbol table per version per profile per language.  This will be sparsely
// populated, so they will only only be generated as needed.
// 
// Each has a different set of built-ins, and we want to preserve that from
// compile to compile.
//
// TODO: thread safety: ensure the built-in symbol table levels are reado only.
TSymbolTable* SharedSymbolTables[VersionCount][EProfileCount][EShLangCount] = {};

TPoolAllocator* PerProcessGPA = 0;

bool InitializeSymbolTable(TBuiltInStrings* BuiltInStrings, int version, EProfile profile, EShLanguage language, TInfoSink& infoSink, 
                           const TBuiltInResource* resources, TSymbolTable* symbolTables)
{
    TIntermediate intermediate(infoSink, version, profile);	
    TSymbolTable* symbolTable;
	
	if (resources)
		symbolTable = symbolTables;
	else
		symbolTable = &symbolTables[language];

    TParseContext parseContext(*symbolTable, intermediate, version, profile, language, infoSink);

    GlobalParseContext = &parseContext;
    
    assert(symbolTable->isEmpty() || symbolTable->atSharedBuiltInLevel());
       
    //
    // Parse the built-ins.  This should only happen once per
    // language symbol table when no 'resources' are passed in.
    //
    // Push the symbol table to give it an initial scope.  This
    // push should not have a corresponding pop, so that built-ins
    // are preserved, and the test for an empty table fails.
    //

    symbolTable->push();

    
    //Initialize the Preprocessor
    int ret = InitPreprocessor();
    if (ret) {
        infoSink.info.message(EPrefixInternalError,  "Unable to intialize the Preprocessor");
        return false;
    }

    ResetFlex();
    
    for (TBuiltInStrings::iterator i  = BuiltInStrings[parseContext.language].begin();
                                   i != BuiltInStrings[parseContext.language].end();    ++i) {
        const char* builtInShaders[1];
        int builtInLengths[1];

        builtInShaders[0] = (*i).c_str();
        builtInLengths[0] = (int) (*i).size();

        if (PaParseStrings(const_cast<char**>(builtInShaders), builtInLengths, 1, parseContext) != 0) {
            infoSink.info.message(EPrefixInternalError, "Unable to parse built-ins");

            return false;
        }
    }
    FinalizePreprocessor();

	if (resources) {
		IdentifyBuiltIns(version, profile, parseContext.language, *symbolTable, *resources);
	} else {
		IdentifyBuiltIns(version, profile, parseContext.language, *symbolTable);
	}
    return true;
}

bool GenerateBuiltInSymbolTable(TInfoSink& infoSink, TSymbolTable* symbolTables, int version, EProfile profile)
{
    TBuiltIns builtIns;
    
	builtIns.initialize(version, profile);
	InitializeSymbolTable(builtIns.getBuiltInStrings(), version, profile, EShLangVertex, infoSink, 0, symbolTables);
	InitializeSymbolTable(builtIns.getBuiltInStrings(), version, profile, EShLangFragment, infoSink, 0, symbolTables);

    return true;
}

bool AddContextSpecificSymbols(const TBuiltInResource* resources, TInfoSink& infoSink, TSymbolTable* symbolTables, int version, EProfile profile, EShLanguage language)
{
    TBuiltIns builtIns;
    
	builtIns.initialize(*resources, version, profile, language);
    InitializeSymbolTable(builtIns.getBuiltInStrings(), version, profile, language, infoSink, resources, symbolTables);

    return true;
}

//
// Driver must call this first, once, before doing any other
// compiler/linker operations.
//

void SetupBuiltinSymbolTable(int version, EProfile profile)
{
    TInfoSink infoSink;

    // This function is for lazy setup.  See if already done.
    int versionIndex = MapVersionToIndex(version);
    if (SharedSymbolTables[versionIndex][profile][EShLangVertex])
        return;

    TPoolAllocator& savedGPA = GetGlobalPoolAllocator();
    TPoolAllocator *builtInPoolAllocator = new TPoolAllocator(true);
    SetGlobalPoolAllocatorPtr(*builtInPoolAllocator);

    TSymbolTable symTables[EShLangCount];
    GenerateBuiltInSymbolTable(infoSink, symTables, version, profile);

    SetGlobalPoolAllocatorPtr(*PerProcessGPA);

    SharedSymbolTables[versionIndex][profile][EShLangVertex] = new TSymbolTable;
    SharedSymbolTables[versionIndex][profile][EShLangVertex]->copyTable(symTables[EShLangVertex]);
    SharedSymbolTables[versionIndex][profile][EShLangFragment] = new TSymbolTable;
    SharedSymbolTables[versionIndex][profile][EShLangFragment]->copyTable(symTables[EShLangFragment]);
        
    symTables[EShLangVertex].pop(0);
    symTables[EShLangFragment].pop(0);

    builtInPoolAllocator->popAll();
    delete builtInPoolAllocator;

    SetGlobalPoolAllocatorPtr(savedGPA);
}

// returns true if something whas consumed
bool ConsumeWhitespaceComment(const char*& s)
{
    const char* startPoint = s;

    // first, skip white space    
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') {
        ++s;
    }

    // then, check for a comment
    if (*s == '/') {
        if (*(s+1) == '/') {
            s += 2;
            do {
                while (*s && *s != '\\' && *s != '\n')
                    ++s;

                if (*s == '\n' || *s == 0) {
                    if (*s == '\n') {
                        ++s;
                        if (*s == '\r')
                            ++s;
                    }  // else it's 0, end of string

                    // we reached the end of the comment
                    break;
                } else {
                    // it's a '\', so we need to keep going, after skipping what's escaped
                    ++s;
                    if (*s == '\n') {
                        ++s;
                        if (*s == '\r')
                            ++s;
                    } else {
                        // skip the escaped character
                        if (*s)
                            ++s;
                    }
                }
            } while (true);
        } else if (*(s+1) == '*') {
            s += 2;
            do {
                while (*s && *s != '*')
                    ++s;
                if (*s == '*') {
                    ++s;
                    if (*s == '/') {
                        ++s;
                        break;
                    } // else not end of comment, keep going
                } else // end of string
                    break;
            } while (true);
        } // else it's not a comment
    } // else it's not a comment

    return startPoint != s;
}

void ScanVersion(const char* const shaderStrings[], int numStrings, int& version, EProfile& profile)
{
    // This function doesn't have to get all the semantics correct, 
    // just find the #version if there is a correct one present.
    // The CPP will have the responsibility of getting all the semantics right.

    version = 0;  // means not found
    profile = ENoProfile;

    const char* s = &shaderStrings[0][0];

    // TODO: ES error check: #version must be on first line

    while (ConsumeWhitespaceComment(s))
        ;

    // #
    if (*s != '#')
        return;
    ++s;

    // whitespace
    while (*s == ' ' || *s == '\t') {
        ++s;
    }

    // version
    if (strncmp(s, "version", 7) != 0)
        return;

    // whitespace
    s += 7;
    while (*s == ' ' || *s == '\t') {
        ++s;
    }

    // version number
    while (*s >= '0' && *s <= '9') {
        version = 10 * version + (*s - '0');
        ++s;
    }
    if (version == 0)
        return;
    
    // whitespace
    while (*s == ' ' || *s == '\t') {
        ++s;
    }

    // profile
    const char* end = s;
    while (*end != ' ' && *end != '\t' && *end != '\n') {
        if (*end == 0)
            return;
        ++end;
    }
    int profileLength = end - s;
    if (profileLength == 2 && strncmp(s, "es", profileLength) == 0)
        profile = EEsProfile;
    else if (profileLength == 4 && strncmp(s, "core", profileLength) == 0)
        profile = ECoreProfile;
    else if (profileLength == 13 && strncmp(s, "compatibility", profileLength) == 0)
        profile = ECompatibilityProfile;
}

bool DeduceProfile(TInfoSink& infoSink, int version, EProfile& profile)
{
    const int FirstProfileVersion = 150;

    if (profile == ENoProfile) {
        if (version == 300) {
            infoSink.info.message(EPrefixError, "#version: version 300 requires specifying the 'es' profile");
            profile = EEsProfile;
            
            return false;
        } else if (version == 100)
            profile = EEsProfile;
        else if (version >= FirstProfileVersion)
            profile = ECoreProfile;
        else
            profile = ENoProfile;
    } else {
        // a profile was provided...
        if (version < 150) {
            infoSink.info.message(EPrefixError, "#version: versions before 150 do not allow a profile token");
            if (version == 100)
                profile = EEsProfile;
            else
                profile = ENoProfile;

            return false;
        } else if (version == 300) {
            if (profile != EEsProfile) {
                infoSink.info.message(EPrefixError, "#version: version 300 supports only the es profile");

                return false;
            }
            profile = EEsProfile;
        } else {
            if (profile == EEsProfile) {
                infoSink.info.message(EPrefixError, "#version: only version 300 supports the es profile");
                if (version >= FirstProfileVersion)
                    profile = ECoreProfile;
                else
                    profile = ENoProfile;

                return false;
            } 
            // else: typical desktop case... e.g., "#version 410 core"
        }
    }

    return true;
}


}; // end anonymous namespace for local functions

int ShInitialize()
{
    if (! InitProcess())
        return 0;

    // TODO: Thread safety:
    // This method should be called once per process. If it's called by multiple threads, then 
    // we need to have thread synchronization code around the initialization of per process
    // global pool allocator
    if (! PerProcessGPA) { 
        PerProcessGPA = new TPoolAllocator(true);
    }
    
    return true;
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
        for (int p = 0; p < EProfileCount; ++p)
            for (int lang = 0; lang < EShLangCount; ++lang)
                delete SharedSymbolTables[version][p][lang];

    if (PerProcessGPA) {
        PerProcessGPA->popAll();
        delete PerProcessGPA;
    }
    return 1;
}

//
// Do an actual compile on the given strings.  The result is left 
// in the given compile object.
//
// Return:  The return value of ShCompile is really boolean, indicating
// success or failure.
//
int ShCompile(
    const ShHandle handle,
    const char* const shaderStrings[],
    const int numStrings,
    const EShOptimizationLevel optLevel,
    const TBuiltInResource* resources,
    int debugOptions,
    int defaultVersion,        // use 100 for ES environment, 110 for desktop
    bool forwardCompatible,    // give errors for use of deprecated features
    EShMessages messages       // warnings/errors
    )
{
    if (!InitThread())
        return 0;

    if (handle == 0)
        return 0;
    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TCompiler* compiler = base->getAsCompiler();
    if (compiler == 0)
        return 0;

    GlobalPoolAllocator.push();
    compiler->infoSink.info.erase();
    compiler->infoSink.debug.erase();

    if (numStrings == 0)
        return 1;

    int version;
    EProfile profile;
    ScanVersion(shaderStrings, numStrings, version, profile);
    if (version == 0)
        version = defaultVersion;
    bool goodProfile = DeduceProfile(compiler->infoSink, version, profile);

    TIntermediate intermediate(compiler->infoSink, version, profile);
    
    SetupBuiltinSymbolTable(version, profile);
    TSymbolTable symbolTable(*SharedSymbolTables[MapVersionToIndex(version)]
                                                [profile]
                                                [compiler->getLanguage()]); 
    
    // Add built-in symbols that are potentially context dependent;
    // they get popped again further down.
    AddContextSpecificSymbols(resources, compiler->infoSink, &symbolTable, version, profile, compiler->getLanguage());

    TParseContext parseContext(symbolTable, intermediate, version, profile, compiler->getLanguage(), compiler->infoSink, forwardCompatible, messages);
    
    if (! goodProfile)
        parseContext.error(1, "incorrect", "#version", "");

    parseContext.initializeExtensionBehavior();

    GlobalParseContext = &parseContext;
    
    ResetFlex();
    InitPreprocessor();

    //
    // Parse the application's shaders.  All the following symbol table
    // work will be throw-away, so push a new allocation scope that can
    // be thrown away, then push a scope for the current shader's globals.
    //
    bool success = true;
    
    symbolTable.push();
    if (! symbolTable.atGlobalLevel())
        parseContext.infoSink.info.message(EPrefixInternalError, "Wrong symbol table level");

    if (parseContext.insertBuiltInArrayAtGlobalLevel())
        success = false;

    int ret = PaParseStrings(const_cast<char**>(shaderStrings), 0, numStrings, parseContext);
    if (ret)
        success = false;

    if (success && parseContext.treeRoot) {
        if (optLevel == EShOptNoGeneration)
            parseContext.infoSink.info.message(EPrefixNone, "No errors.  No code generation or linking was requested.");
        else {
            success = intermediate.postProcess(parseContext.treeRoot, parseContext.language);

            if (success) {

                if (debugOptions & EDebugOpIntermediate)
                    intermediate.outputTree(parseContext.treeRoot);

                //
                // Call the machine dependent compiler
                //
                if (! compiler->compile(parseContext.treeRoot))
                    success = false;
            }
        }
    } else if (! success) {
        parseContext.infoSink.info.prefix(EPrefixError);
        parseContext.infoSink.info << parseContext.numErrors << " compilation errors.  No code generated.\n\n";
        success = false;
        if (debugOptions & EDebugOpIntermediate)
            intermediate.outputTree(parseContext.treeRoot);
    }

    intermediate.remove(parseContext.treeRoot);

    //
    // Ensure symbol table is returned to the built-in level,
    // throwing away all but the built-ins.
    //
    while (! symbolTable.atSharedBuiltInLevel())
        symbolTable.pop(0);

    FinalizePreprocessor();
    //
    // Throw away all the temporary memory used by the compilation process.
    //
    GlobalPoolAllocator.pop();

    return success ? 1 : 0;
}

//
// Do an actual link on the given compile objects.
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
    GlobalPoolAllocator.push();
    returnValue = ShLinkExt(linkHandle, compHandles, numHandles);
    GlobalPoolAllocator.pop();

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
