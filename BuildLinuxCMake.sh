#!/bin/bash
rm -rf build
mkdir build
pushd build
cmake ..
cmake ..
make
make install
install/bin/glslangValidator -i ../Test/sample.vert ../Test/sample.frag
popd
