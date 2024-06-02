#!/bin/bash
# Pro Bash scriptin time 


# Make the library if not already compiled

gcc -c src/ssbl.c -o build/ssbl.o
ar rcs libr/libssbl.a build/ssbl.o

# Compile the interpreter
gcc -O3 -Llibr/ src/interpreter.c -o build/ssbl -lssbl

# Remove object file
rm build/ssbl.o