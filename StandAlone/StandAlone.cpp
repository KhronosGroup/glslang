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
#include "./../glslang/Include/ShHandle.h"
#include "./../glslang/Public/ShaderLang.h"
#include <string.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#endif

extern "C" {
    SH_IMPORT_EXPORT void ShOutputHtml();
}

//#define MEASURE_MEMORY

//
// Return codes from main.
//
enum TFailCode {
    ESuccess = 0,
    EFailUsage,
    EFailCompile,
    EFailLink,
    EFailCompilerCreate,
    EFailLinkerCreate
};

//
// Just placeholders for testing purposes.  The stand-alone environment
// can't actually do a full link without something specifying real
// attribute bindings.
//
ShBinding FixedAttributeBindings[] = { 
    { "gl_Vertex", 15 },
    { "gl_Color", 10 },
    { "gl_Normal", 7 },
};

ShBindingTable FixedAttributeTable = { 3, FixedAttributeBindings };

static EShLanguage FindLanguage(char *lang);
bool CompileFile(char *fileName, ShHandle, int, const TBuiltInResource*);
void usage();
void FreeFileData(char **data);
char** ReadFileData(char *fileName);
void InfoLogMsg(char* msg, const char* name, const int num);
int ShOutputMultipleStrings(char ** );
//Added to accomodate the multiple strings.
int OutputMultipleStrings = 1;

//
// Set up the per compile resources
//
void GenerateResources(TBuiltInResource& resources)
{    
    resources.maxLights = 32;
    resources.maxClipPlanes = 6;
    resources.maxTextureUnits = 32;
    resources.maxTextureCoords = 32;
    resources.maxVertexAttribs = 64;
    resources.maxVertexUniformComponents = 4096;
    resources.maxVaryingFloats = 64;
    resources.maxVertexTextureImageUnits = 32;
    resources.maxCombinedTextureImageUnits = 32;
    resources.maxTextureImageUnits = 32;
    resources.maxFragmentUniformComponents = 4096;
    resources.maxDrawBuffers = 32;
}

int C_DECL main(int argc, char* argv[])
{
    bool delay = false;
    int numCompilers = 0;
    bool compileFailed = false;
    bool linkFailed = false;
    int debugOptions = 0;
    int i;
    
    ShHandle    linker = 0;
    ShHandle    uniformMap = 0;
    ShHandle    compilers[EShLangCount];

    ShInitialize();

#ifdef _WIN32
    __try {
#endif
        argc--;
        argv++;    
        for (; argc >= 1; argc--, argv++) {
            if (argv[0][0] == '-' || argv[0][0] == '/') {
                switch (argv[0][1]) {
                case 'd': delay    = true;                           break;

#ifdef MEASURE_MEMORY
                case 'i': break;
                case 'a': break;
                case 'h': break;
#else
                case 'i': debugOptions |= EDebugOpIntermediate;       break;
                case 'a': debugOptions |= EDebugOpAssembly;           break;
#endif
                case 'c': if(!ShOutputMultipleStrings(++argv))
                                                         return EFailUsage; 
                          --argc;                                    break;
                case 'm': debugOptions |= EDebugOpLinkMaps;           break;
                default:  usage();                       return EFailUsage;
                }
            } else {
                compilers[numCompilers] = ShConstructCompiler(FindLanguage(argv[0]), debugOptions);
                if (compilers[numCompilers] == 0)
                    return EFailCompilerCreate;
                ++numCompilers;

                TBuiltInResource resources;
                GenerateResources(resources);
                if (! CompileFile(argv[0], compilers[numCompilers-1], debugOptions, &resources))
                    compileFailed = true;                
            }
        }

        if (!numCompilers) {
            usage();
            return EFailUsage;
        }

        linker = ShConstructLinker(EShExVertexFragment, debugOptions);
        if (linker == 0)
            return EFailLinkerCreate;

        uniformMap = ShConstructUniformMap();
        if (uniformMap == 0)
            return EFailLinkerCreate;

        if (numCompilers > 0) {
            ShSetFixedAttributeBindings(linker, &FixedAttributeTable);
            if (! ShLink(linker, compilers, numCompilers, uniformMap, 0, 0))
                linkFailed = true;
        }

        for (i = 0; i < numCompilers; ++i) {
            InfoLogMsg("BEGIN", "COMPILER", i);
            puts(ShGetInfoLog(compilers[i]));
            InfoLogMsg("END", "COMPILER", i);
        }

        InfoLogMsg("BEGIN", "LINKER", -1);
        puts(ShGetInfoLog(linker));
        InfoLogMsg("END", "LINKER", -1);
    
#ifdef _WIN32
    } __finally {    
#endif    
        for (i = 0; i < numCompilers; ++i)
            ShDestruct(compilers[i]);

        ShDestruct(linker);
        ShDestruct(uniformMap);

#ifdef _WIN32
        if (delay)
            Sleep(1000000);

    }
#endif

    if (compileFailed)
        return EFailCompile;
    if (linkFailed)
        return EFailLink;

    return 0;
}

//
//   Deduce the language from the filename.  Files must end in one of the
//   following extensions:
//
//   .frag*    = fragment programs
//   .vert*    = vertex programs
//   .pack*    = pack programs
//   .unpa*    = unpack pragrams
//
static EShLanguage FindLanguage(char *name)
{
    if (!name)
        return EShLangFragment;

    char *ext = strrchr(name, '.');

    if (ext && strcmp(ext, ".sl") == 0)
        for (; ext > name && ext[0] != '.'; ext--);
    
    if (ext = strrchr(name, '.')) {
        if (strncmp(ext, ".frag", 4) == 0) return EShLangFragment;
        if (strncmp(ext, ".vert", 4) == 0) return EShLangVertex;
        if (strncmp(ext, ".pack", 4) == 0) return EShLangPack;
        if (strncmp(ext, ".unpa", 4) == 0) return EShLangUnpack;
    }

    return EShLangFragment;
}


//
//   Read a file's data into a string, and compile it using ShCompile
//
bool CompileFile(char *fileName, ShHandle compiler, int debugOptions, const TBuiltInResource *resources)
{
    int ret;
    char **data = ReadFileData(fileName);

#ifdef MEASURE_MEMORY
    PROCESS_MEMORY_COUNTERS counters;
#endif

    if (!data)
        return false;

#ifdef MEASURE_MEMORY
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
#endif
            ret = ShCompile(compiler, data, OutputMultipleStrings, EShOptNone, resources, debugOptions);
#ifdef MEASURE_MEMORY

        GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters));
    }
#endif

    FreeFileData(data);

    return ret ? true : false;
}


//
//   print usage to stdout
//
void usage()
{
    printf("Usage: standalone [-i -a -c -m -d -h] file1 file2 ...\n"
           "Where: filename = filename ending in .frag* or .vert*\n");
}


//
//   Malloc a string of sufficient size and read a string into it.
//
# define MAX_SOURCE_STRINGS 5
char** ReadFileData(char *fileName) 
{
    FILE *in    = fopen(fileName, "r");
    char *fdata;
    int count = 0;
    char**return_data=(char**)malloc(MAX_SOURCE_STRINGS+1);

    //return_data[MAX_SOURCE_STRINGS]=NULL;
	if (!in) {
        printf("Error: unable to open input file: %s\n", fileName);
        return 0;
    }
    
    while (fgetc(in) != EOF)
        count++;

	fseek(in, 0, SEEK_SET);
	
	
	if (!(fdata = (char *)malloc(count+2))) {
            printf("Error allocating memory\n");
            return 0;
    }
	if (fread(fdata,1,count, in)!=count) {
            printf("Error reading input file: %s\n", fileName);
            return 0;
    }
    fdata[count] = '\0';
    fclose(in);
    if(count==0){
        return_data[0]=(char*)malloc(count+2);
        return_data[0][0]='\0';
        OutputMultipleStrings=0;
        return return_data;       
    }

	int len = (int)(ceil)((float)count/(float)OutputMultipleStrings);
    int ptr_len=0,i=0;
	while(count>0){
		return_data[i]=(char*)malloc(len+2);
		memcpy(return_data[i],fdata+ptr_len,len);
		return_data[i][len]='\0';
		count-=(len);
		ptr_len+=(len);
		if(count<len){
            if(count==0){
               OutputMultipleStrings=(i+1);
               break;
            }
           len = count;
		}  
		++i;
	}
    return return_data;
}



void FreeFileData(char **data)
{
    for(int i=0;i<OutputMultipleStrings;i++)
        free(data[i]);
}



void InfoLogMsg(char* msg, const char* name, const int num)
{
    printf(num >= 0 ? "#### %s %s %d INFO LOG ####\n" :
           "#### %s %s INFO LOG ####\n", msg, name, num);
}

int ShOutputMultipleStrings(char **argv)
{
	if(!(abs(OutputMultipleStrings = atoi(*argv)))||((OutputMultipleStrings >5 || OutputMultipleStrings < 1)? 1:0)){
	   printf("Invalid Command Line Argument after -c option.\n"
              "Usage: -c <integer> where integer =[1,5]\n"
              "This option must be specified before the input file path\n");
       return 0;
	}
    return 1;
}
