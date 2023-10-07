#!/bin/bash

# add compile_commands as clangd reference
cd ./build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cd ..
ln -s $PWD/build/compile_commands.json $PWD
