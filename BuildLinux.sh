#! /bin/bash

rm StandAlone/StandAlone

# build the StandAlone app and all it's dependencies
make -C StandAlone

# so we can find the shared library
LD_LIBRARY_PATH=`pwd`/glslang/MachineIndependent/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH

# run using test data
cd Test
../StandAlone/StandAlone -i sample.vert sample.frag


