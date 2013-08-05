This directory contains linux binaries for the glslang validator.  The main 
executable is glslangValidator, which requires use of the shared object
file libglsang.so.

Installation: Executing the ./install script will copy these to /usr/local/* 
so that they may be executed from any directory.  

Alternatively, you may put them where you wish, but will then need to use 
something like:

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<path to libglslang.so>

Usage:  Execute glslangValidator with no arguments to get a usage statement.
