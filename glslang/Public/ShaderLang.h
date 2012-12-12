//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
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
#ifndef _COMPILER_INTERFACE_INCLUDED_
#define _COMPILER_INTERFACE_INCLUDED_

#include "../Include/ResourceLimits.h"

#ifdef _WIN32
#define C_DECL __cdecl
#ifdef SH_EXPORTING
    #define SH_IMPORT_EXPORT __declspec(dllexport)
#else
    #define SH_IMPORT_EXPORT __declspec(dllimport)
#endif
#else
#define SH_IMPORT_EXPORT
#define __fastcall
#define C_DECL
#endif

//
// This is the platform independent interface between an OGL driver
// and the shading language compiler/linker.
//

#ifdef __cplusplus
    extern "C" {
#endif
//
// Driver must call this first, once, before doing any other
// compiler/linker operations.
//
SH_IMPORT_EXPORT int ShInitialize();
//
// Driver should call this at shutdown.
//
SH_IMPORT_EXPORT int __fastcall ShFinalize();
//
// Types of languages the compiler can consume.
//
typedef enum {
	EShLangVertex,
	EShLangFragment,
	EShLangPack,
    EShLangUnpack,
    EShLangCount,
} EShLanguage;

//
// Types of output the linker will create.
//
typedef enum {
    EShExVertexFragment,
    EShExPackFragment,
    EShExUnpackFragment,
    EShExFragment
} EShExecutable;

//
// Optimization level for the compiler.
//
typedef enum {
    EShOptNoGeneration,
    EShOptNone,
    EShOptSimple,       // Optimizations that can be done quickly
    EShOptFull,         // Optimizations that will take more time
} EShOptimizationLevel;

//
// Build a table for bindings.  This can be used for locating
// attributes, uniforms, globals, etc., as needed.
//
typedef struct {
    char* name;
    int binding;
} ShBinding;

typedef struct {
    int numBindings;
	ShBinding* bindings;  // array of bindings
} ShBindingTable;

//
// ShHandle held by but opaque to the driver.  It is allocated,
// managed, and de-allocated by the compiler/linker. It's contents 
// are defined by and used by the compiler and linker.  For example,
// symbol table information and object code passed from the compiler 
// to the linker can be stored where ShHandle points.
//
// If handle creation fails, 0 will be returned.
//
typedef void* ShHandle;

//
// Driver calls these to create and destroy compiler/linker
// objects.
//
SH_IMPORT_EXPORT ShHandle ShConstructCompiler(const EShLanguage, int debugOptions);  // one per shader
SH_IMPORT_EXPORT ShHandle ShConstructLinker(const EShExecutable, int debugOptions);  // one per shader pair
SH_IMPORT_EXPORT ShHandle ShConstructUniformMap();                 // one per uniform namespace (currently entire program object)
SH_IMPORT_EXPORT void ShDestruct(ShHandle);

//
// The return value of ShCompile is boolean, indicating
// success or failure.
//
// The info-log should be written by ShCompile into 
// ShHandle, so it can answer future queries.
//
SH_IMPORT_EXPORT int ShCompile(
    const ShHandle,
    const char* const shaderStrings[],
    const int numStrings,
    const EShOptimizationLevel,
    const TBuiltInResource *resources,
    int debugOptions
    );


//
// Similar to ShCompile, but accepts an opaque handle to an
// intermediate language structure.
//
SH_IMPORT_EXPORT int ShCompileIntermediate(
    ShHandle compiler,
    ShHandle intermediate,
    const EShOptimizationLevel,
    int debuggable           // boolean
    );

SH_IMPORT_EXPORT int ShLink(
    const ShHandle,               // linker object
    const ShHandle h[],           // compiler objects to link together
    const int numHandles,
    ShHandle uniformMap,          // updated with new uniforms
    short int** uniformsAccessed,  // returned with indexes of uniforms accessed
    int* numUniformsAccessed); 	

SH_IMPORT_EXPORT int ShLinkExt(
    const ShHandle,               // linker object
    const ShHandle h[],           // compiler objects to link together
    const int numHandles);

//
// ShSetEncrpytionMethod is a place-holder for specifying
// how source code is encrypted.
//
SH_IMPORT_EXPORT void ShSetEncryptionMethod(ShHandle);

//
// All the following return 0 if the information is not
// available in the object passed down, or the object is bad.
//
SH_IMPORT_EXPORT const char* ShGetInfoLog(const ShHandle);
SH_IMPORT_EXPORT const void* ShGetExecutable(const ShHandle);
SH_IMPORT_EXPORT int ShSetVirtualAttributeBindings(const ShHandle, const ShBindingTable*);   // to detect user aliasing
SH_IMPORT_EXPORT int ShSetFixedAttributeBindings(const ShHandle, const ShBindingTable*);     // to force any physical mappings
SH_IMPORT_EXPORT int ShGetPhysicalAttributeBindings(const ShHandle, const ShBindingTable**); // for all attributes
//
// Tell the linker to never assign a vertex attribute to this list of physical attributes
//
SH_IMPORT_EXPORT int ShExcludeAttributes(const ShHandle, int *attributes, int count);

//
// Returns the location ID of the named uniform.
// Returns -1 if error.
//
SH_IMPORT_EXPORT int ShGetUniformLocation(const ShHandle uniformMap, const char* name);

enum TDebugOptions {
	EDebugOpNone               = 0x000,
	EDebugOpIntermediate       = 0x001,
	EDebugOpAssembly           = 0x002,
    EDebugOpObjectCode         = 0x004,
	EDebugOpLinkMaps           = 0x008
};
#ifdef __cplusplus
    }
#endif

#endif // _COMPILER_INTERFACE_INCLUDED_
