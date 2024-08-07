#!/bin/bash
# Pro Bash scriptin time 

# Make sure ./libr exists

if [ ! -d ./libr ]; then
    mkdir libr
fi

# Make the library
gcc -c src/ssbl.c -o build/ssbl.o
ar rcs libr/libssbl.a build/ssbl.o

# Compile the interpreter and bytecode compiler
gcc -O3 -Llibr/ src/toRawInt.c -o build/sbfm
gcc -O3 -Llibr/ src/interpreter.c -o build/ssbl -lssbl

# Remove object file
rm build/ssbl.o