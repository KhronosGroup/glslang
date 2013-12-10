An OpenGL and OpenGL ES shader front end and validator.

There are two components:

1) A front-end library for programmatic parsing of GLSL/ESSL into an AST.

2) A standalone wrapper, glslangValidator, that can be used as a shader 
   validation tool. 

How to add a feature protected by a version/extension/stage/profile:  See the
comment in glslang/MachineIndependent/Versions.cpp.

Things left to do:  See Todo.txt

Execution of Standalone Wrapper
-------------------------------

There are binaries in the Install/Windows and Install/Linux directories.

To use the standalone binary form, execute glslangValidator, and it will print
a usage statement.  Basic operation is to give it a file containing a shader,
and it will print out warnings/errors and optionally an AST.

The applied stage-specific rules are based on the file extension:
    .vert for a vertex shader
    .tesc for a tessellation control shader
    .tese for a tessellation evaluation shader
    .geom for a geometry shader
    .frag for a fragment shader
    .comp for a compute shader

There is also a non-shader extension
    .conf for a configuration file of limits, see usage statement for example

Source: Build and run on Linux
-------------------------------

A simple bash script "BuildLinux.sh" is provided at the root directory
to do the build and run a test cases.  You will need a recent version of
bison installed.

Once the executable is generated, it needs to be dynamically linked with the 
shared object created in lib directory. To achieve that, "cd" to 
StandAlone directory to update the LD_LIBRARY_PATH as follows

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./../glslang/MachineIndependent/lib

You can also update LD_LIBRARY_PATH in the .cshrc or .bashrc file, depending on 
the shell you are using. You will need to give the complete path of "lib" directory
in .cshrc or .bashrc files.

Source: Build and run on Windows
--------------------------------

Current development is with Visual Studio verion 11 (2012).  The solution
file is in the project's root directory Standalone.sln.  

Building the StandAlone project (the default) will create glslangValidate.exe and
copy it into the Test directory and Install directory.  This allows local
test scripts to use either the debug or release version, whichever was
built last.

Windows execution and testing is generally done from within a cygwin
shell.

Note: Despite appearances, the use of a DLL is currently disabled; it
simply makes a standalone executable from a statically linked library.

Programmatic Interfaces
-----------------------

Another piece of software can programmatically translate shaders to an AST 
using one of two different interfaces: 
    - A new C++ class-oriented interface, or
    - The original C functional interface

The main() in StandAlone/StandAlone.cpp shows examples using both styles.

C++ Class Interface (new, preferred):

    This interface is in roughly the last 1/3 of ShaderLang.h.  It is in the 
    glslang namespace and contains the following.

        const char* GetEsslVersionString();
        const char* GetGlslVersionString();
        bool InitializeProcess();
        void FinalizeProcess();

        class TShader
            bool parse(...);
            void setStrings(...);
            const char* getInfoLog();

        class TProgram
            void addShader(...);
            bool link(...);
            const char* getInfoLog();
            Reflection queries

    See ShaderLang.h and the usage of it in StandAlone/StandAlone.cpp for more
    details.
            
C Functional Interface (orginal):

    This interface is in roughly the first 2/3 of ShaderLang.h, and referred to
    as the Sh*() interface, as all the entry points start "Sh".

    The Sh*() interface takes a "compiler" call-back object, which it calls after 
    building call back that is passed the AST and can then execute a backend on it.

    The following is a simplified resulting run-time call stack:

        ShCompile(shader, compiler) -> compiler(AST) -> <back end>

    In practice, ShCompile() takes shader strings, default version, and
    warning/error and other options for controling compilation.

Testing
-------

"Test" is an active test directory that contains test input and a
subdirectory baseResults that contains the expected results of the
tests.  Both the tests and baseResults are under source-code control.
Executing the script ./runtests will generate current results in 
the localResults directory and diff them against the baseResults.
When you want to update the tracked test results, they need to be
copied from localResults to baseResults

There are some tests borrowed from LunarGLASS.  If LunarGLASS is
missing, those tests just won't run.

Basic Internal Operation
------------------------

 -  Initial lexical analysis is done by the preprocessor in
    MachineIndependent/Preprocessor, and then refined by a GLSL scanner
    in MachineIndependent/Scan.cpp.  There is currently no use of flex.

 -  Code is parsed using bison on MachineIndependent/glslang.y with the 
    aid of a symbol table and an AST.  The symbol table is not passed on to
    the back-end; the intermediate representation stands on its own.
    The tree is built by the grammar productions, many of which are 
    offloaded into ParseHelper.cpp, and by Intermediate.cpp.

 -  The intermediate representation is very high-level, and represented
    as an in-memory tree.   This serves to lose no information from the
    original program, and to have efficient transfer of the result from
    parsing to the back-end.  In the AST, constants are propogated and 
    folded, and a very small amount of dead code is eliminated.

    To aid linking and reflection, the last top-level branch in the AST 
    lists all global symbols.

 -  The primary algorithm of the back-end compiler is to traverse the 
    tree (high-level intermediate representation), and create an internal
    object code representation.  There is an example of how to do this
    in MachineIndependent/intermOut.cpp.

 -  Reduction of the tree to a linear byte-code style low-level intermediate
    representation is likely a good way to generate fully optimized code.

 -  There is currently some dead old-style linker-type code still lying around.

 - Memory pool: parsing uses types derived from C++ std types, using a 
   custom allocator that puts them in a memory pool.  This makes allocation
   of individual container/contents just few cycles and deallocation free.
   This pool is popped after the AST is made and processed.

   The use is simple: if you are going to call "new", there are three cases:

    - the object comes from the pool (its base class has the macro
      POOL_ALLOCATOR_NEW_DELETE in it) and you do not have to call delete

    - it is a TString, in which case call NewPoolTString(), which gets 
      it from the pool, and there is no corresponding delete

    - the object does not come from the pool, and you have to do normal
      C++ memory management of what you 'new'
