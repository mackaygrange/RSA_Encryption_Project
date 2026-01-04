#!/bin/bash
# Build script for compiling RSA to WebAssembly (Linux/macOS)

# Check if emscripten is available
if ! command -v emcc &> /dev/null; then
    echo "Emscripten not found. Please install it: https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
fi

echo "Compiling RSA to WebAssembly..."

emcc rsa_wrapper.cpp \
    -o public/rsa_demo.js \
    -s WASM=1 \
    -s 'EXPORTED_FUNCTIONS=["_rsa_encrypt","_rsa_decrypt","_calculate_n","_calculate_lambda","_calculate_d","_is_prime","_validate_e_value","_allocate_memory","_free_memory"]' \
    -s 'EXPORTED_RUNTIME_METHODS=["ccall","cwrap"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -std=c++11 \
    -fno-exceptions \
    -O3

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Output files: public/rsa_demo.js and public/rsa_demo.wasm"
else
    echo "Compilation failed"
    exit 1
fi
