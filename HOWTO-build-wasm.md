Build as usual (see `README.md`), but:
  * Need `emsdk` in your *PATH*
    + Instructions located
      [here](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install)
  * Do not checkout SPIRV-Tools into External/
    + Does not work correctly with emscripten out of the box and we don't want
      it in the build anyway.
    + *TBD* Add flag to disable SPIRV-Tool inclusion even if directory is
      present.
  * Wrap call to `cmake` using `emconfigure`:
    + e.g. `emconfigure cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_GLSLANG_WEB=ON
    -DENABLE_HLSL=OFF -DCMAKE_INSTALL_PREFIX="$(pwd)/install" ..`
    + To get a 'true' size, make sure to use `brotli` to compress the .js and .wasm files

