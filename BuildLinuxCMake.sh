#!/bin/bash
rm -rf linux_build
mkdir linux_build
pushd linux_build
cmake ..
make
./StandAlone/glslangValidator -i ../Test/sample.vert ../Test/sample.frag
popd
