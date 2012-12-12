OpenGL Shading Language source readme for Window and Linux

Version: Sept 20, 2005


Source Copyright
----------------


Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Changes since June 2005 Release
-------------------------------
- Some infrastructure is simplified, improved, and cleaned up.  Details follow.

- TPublicType is easier to setup and extend.

- Constant values know their own types. Methods are added to set the 
constant values as the data members are now protected instead of public.
Lots of code was cleaned up because of that. 

- Added support for an array object extension. Array constructors are 
allowed. Constant arrays can be declared and parse time constant folding 
and propagation is done through array objects. Extension GL_3DL_array_objects 
must be enabled to use the array objects.

- Arrays and structures are handled more uniformly. Sizing is simplified and improved.

- Changed the implementation of the way constants values were stored in 
the parse tree. Constants are now always flattened out. Constructors with 
constant values are represented with constant values directly. Example mat2(1) 
is stored as a constant node with values 1.0, 0.0, 0.0, 1.0. Earlier this
was stored as an aggregate node with correct operator and a single constant 
value 1.0. This change caused a lot of code to be cleaned up and simplified.

- Renamed ARB texture rectangle functions to match the final version of the specification.


Changes since Feb 2005 Release
------------------------------
- Source now compiles on gcc 3.4.4.
- Fixed constant folding for ternary operator.
- Non-dereferenced arrays not allowed in constructors. Other semantic 
error checking on arrays such as ++array, array1 = array2.
- Max allowed index for gl_TexCoord is gl_MaxTextureCoords - 1.
- Raise an error when one of the string passed to the parser is a NULL 
pointer.
- Parser code tested to be portable on STLport stl.
- Detect error when preprocessor directives does not begin at the start 
of the line.

Please feel free to submit any fixes to the parser code.


Changes since Jan 2005 Release
------------------------------
- Relaxed grammar rules for ?: (ternary operator) to allow assignment 
expressions after the ':'.
- Fixed the correct parsing of empty shader source string.
- No longer raise an error when gl_Position is not written in a vertex 
shader. This is link time functionality.
- Added some basic support for MSVC++6.0 to the extent that C++ standards 
are not violated.


Changes since Sept 2004 Release
-------------------------------
- Memory usage by builtIn symbol table level is reduced to 1/4th of what 
was used earlier.
- Built In symbol table level is split into two, the first level contains 
symbols that do not change and the second level is constructed per compile, 
based on the resource values specified by the driver. This required ShCompile
method to take in a pointer to the resource values.
- Correct handling of pragmas.
- Fixed defects such as comma operator folding, swizzling allowed only with 
offsets from same set, texture look up functions appropriately split between 
vertex and fragment shaders, ternary operator type checking, preprocessor 
directives etc.
- Linux build now use flex version 2.5.4 that comes with Redhat 9.0


Changes since July 2004 Release
-------------------------------
- Structures when initialized both as a constant and a non constant were broken.


Changes Since Apr 2004 Release
-------------------------------
- Added support for #extension and #version preprocessor directives.
- Removed printf statements and instead dump messages on InfoSink.
- Most of the source code is now thread safe except for some of the 
preprocessor code. Also For Linux, the per thread data clean up is yet to be
implemented as it is not exactly known when the thread exits.
- Fixed comma operator when used with constant initializer.
- Added folding when constructors are called with constant values.
- Correctly updated builtIn names for texture functions from 
texture{1|2}DShadow[Proj][Lod] to shadow{1|2}D[Proj][Lod].
- Updated the built-in constant names as per latest GL2 specs.
- Portable across more platforms.


Changes Since Oct 2003 Release
-------------------------------
- Added new reserved keywords.  Also reserved %=.
- Fixed some bugs and memory leaks in the preprocessor.
- Fixed name mangling for function names.  Names also now include array sizes.
- Fixed implementation of unsized arrays.
- Constructors: Disallow matrices constructed from matrices, and unused 
arguments.
   Also fixed some cases like float(vec2) that were not working right.
- TILDA -> TILDE.
- Fixed structure qualifier semantics:  they apply to variables declared, 
not the structure definition.


Changes since May 2003 Release
-------------------------------

- Corrected some bugs in preprocessor.
- Keeping track of maximum size of the array used in the source code.
- Parameter passing during function call and keeping track of inout and out 
parameters.
- Added some more built in functions.
- Portability to Linux


Changes Since April 2002 Release
--------------------------------

* Semantic changes to bring the implementation and spec closer together,
  and support issue resolution.

* Some minor functionality completeness.  

  - User function calls are more complete, 
  - added the ^^ operator (logical exclusive or)
  - fixed variable scoping in if-else
  - no declarations in if-conditions
  - improved typing of field selectors
  - removed suffixes from literal constants
  - many smaller semantic changes to be in line with the current spec
  - added preprocessor
  - added non-scalar constants
  - added structures


Changes since July 2002 Release
-------------------------------

Brought up to date with version 1.051 of the OpenGL Shading Language 
Specification.  It is now almost complete.  The list of detailed 
changes would be long, as the specification has changed extensively, 
and all missing functionality has been added.


Procedure to Build on Windows
-----------------------------

Put this project in a path name without spaces.

procedure To build using MS visual studio .Net.  

It has two projects.
The glslang project must be compiled first, followed by the
StandAlone project.

1.  The solution is StandAlone.sln.  The two necessary
projects are glslang.vcproj and StandAlone.vcproj,
which devstudio will automatically open.

2.  You may have a missing header file, unistd.h.  Create an empty one in
some standard devstudio or SDK system include directory.  (Bison/flex
generate a #include <unistd.h>, this makes them happy.)

3.  Build the glslang project (in devstudio, right click the glslang project
and build).  This creates the glslang.dll and glslang.lib files needed to
make the StandAlone compiler run.  It leaves them in the StandAlone
directory.

4.  Build the StandAlone project if you want to run the tests or run the
compiler stand-alone.


Running Stand Alone on Windows
------------------------------

The build process should create glslang.dll and StandAlone.exe.  glslang.dll
has an interface suitable for integration with an ICD.  StandAlone.exe uses
this interface to create a version of the compiler that can run outside
the ICD environment.

The stand-alone compiler is a Win32 console application, best executed 
from a command prompt.  

“cd” into the StandAlone directory, or a directory you've installed
StandAlone.exe, the OglBuiltIns subdirectory, and glslang.dll into.

The normal case will be to compile and link a pair of shaders like this:

    StandAlone -i <vertex-file>.vert  <fragment-file>.frag

    where the following command line options are possible for StandAlone:
    i - dump parse tree
    m - dump linker output (nothing dumped in the source code provided)
    a - dump assembly code (nothing dumped in the source code provided)

The applied compilation-language is based on the file extension.  
Give the full name of the files containing the shader source code.  
The output from running this will contain compile and link errors, as
well as a textual version of the intermediate representation.


Procedure to build and run on Linux
-----------------------------------

A simple bash script "BuildLinux.sh" is provided to do the build and run the test
cases, or you may run the steps manually as described below:

"cd" into StandAlone directory and run make. It will build all the dependency 
directories also. You can also go to the specific directories and do a make for each 
directory individually. Make sure that there exists a lib directory at the given 
path: glslang/MachineIndependent/lib where libglslang.so is stored.

To compile glslang.l, flex version 2.5.31 is required. An executable of flex is 
provided in tools directory. To compile glslang.y, bison version 1.35 or higher is 
required. Most versions of Red Hat comes with bison 1.35.

Once the executable is generated, it needs to be dynamically linked with the 
shared object created in lib directory. To achieve that, we need to "cd" to 
StandAlone directory to update the LD_LIBRARY_PATH as follows

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./../glslang/MachineIndependent/lib

You can also update LD_LIBRARY_PATH in the .cshrc or .bashrc file, depending on 
the shell you are using. You will need to give the complete path of "lib" directory
in .cshrc or .bashrc files.

The normal case will be to compile and link a pair of shaders like this:

    ./StandAlone -i <vertex-file>.vert  <fragment-file>.frag

    where the following command line options are possible for StandAlone:
    i - dump parse tree
    m - dump linker output (nothing dumped in the source code provided)
    a - dump assembly code (nothing dumped in the source code provided)

The applied compilation-language is based on the file extension.  
Give the full name of the files containing the shader source code.  
The output from running this will contain compile and link errors, as
well as a textual version of the intermediate representation.

To generate the dependencies, you can run "make depend".
This step has already been done and need not be done again by the user.

To clean the ".o"s, ".a"s and ".so" generated by make, you can use "make clean".


Notes for Understanding/Modifying the Code
------------------------------------------

* This is completely machine independent code.  We have a working
  back-end card-specific compiler that is not present.  Instead, a trivial
  back-end compiler is in the directory GenericCodeGen.

* The main directory for parsing and intermediate representation is 
  MachineIndependent.

* Header files shared between machine independent parsing and the
  machine dependent compiling and linking are in include.

* Header files shared between the compiler and an ICD are in public.

* Merging with future updates will be easiest if initially you confine
  your changes to the GenericCodeGen directory.

* To write a back-end compiler, see the next section on Basic Design.


Basic Design
------------

1.  Code is parsed by flex/bison, with the aid of a symbol table and an 
    intermediate representation.  The symbol table is not passed on to
    the back-end; the intermediate representation stands on its own.

2.  The intermediate representation is very high-level, and represented
    as an in-memory tree.   This serves to lose no information from the
    original program, and to have efficient transfer of the result from
    parsing to the back-end.  In the intermediate representation,
    constants are propogated and folded, and some dead code is eliminated.

3.  The primary algorithm of the back-end compiler is to traverse the 
    tree (high-level intermediate representation), and create an internal
    object code representation.  There is a query in the compiler interface
    to the ICD for retrieval of this object code.

4.  Reduction of the tree to a linear byte-code style low-level intermediate
    representation is likely a good way to generate fully optimized code.
    There is some possibility of standardizing such a byte code.

See these files to get started:

* IntermOut.cpp:  this shows traversing the tree to generate output.
* CodeGen.cpp:    this shows the basic interface to the back-end compiler.
* Link.cpp:       this shows the basic interface to the linker.
* Intermediate.h: to see the data structures backing the tree.

