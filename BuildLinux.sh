#! /bin/bash

rm -f StandAlone/glsangValidator
rm -f glslang/MachineIndependent/lib/libglslang.so

# build the StandAlone app and all it's dependencies
make -C StandAlone

# so we can find the shared library
LD_LIBRARY_PATH=`pwd`/glslang/MachineIndependent/lib
export LD_LIBRARY_PATH

# run using test data
cd Test
../StandAlone/glslangValidator -i sample.vert sample.frag
