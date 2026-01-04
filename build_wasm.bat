@echo on
REM Build script for compiling RSA to WebAssembly (Windows)

REM Check if emcripten is available
where emcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Emscripten not found. Please install it: https://emscripten.org/docs/getting_started/downloads.html
    exit /b 1
)

echo Compiling RSA to WebAssembly...

emcc rsa_wrapper.cpp ^
    -o ../../public/wasm/rsa_demo.js ^
    -s WASM=1 ^
    -s MODULARIZE=1 ^
    -s EXPORT_ES6=0 ^
    -s EXPORT_NAME="RSAModule" ^
    -s EXPORTED_FUNCTIONS="[""_rsa_encrypt"",""_rsa_decrypt"",""_calculate_n"",""_calculate_lambda"",""_calculate_d"",""_is_prime"",""_validate_e_value"",""_allocate_memory"",""_free_memory""]" ^
    -s EXPORTED_RUNTIME_METHODS="[""ccall"",""cwrap""]" ^
    -s ALLOW_MEMORY_GROWTH=1 ^
    -std=c++11 ^
    -O3

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Output files: ../../public/wasm/rsa_demo.js and ../../public/wasm/rsa_demo.wasm
) else (
    echo Compilation failed with exit code %ERRORLEVEL%
    exit /b 1
)
