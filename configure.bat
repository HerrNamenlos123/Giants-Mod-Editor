@echo off
cmake . -B build -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
