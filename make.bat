@echo off
REM Pro Batch scriptin time

REM Make sure .\libr exists
if not exist libr mkdir libr

REM Make the library
gcc -c src\ssbl.c -o build\ssbl.o
ar rcs libr\libssbl.a build\ssbl.o

REM Compile the interpreter and bytecode compiler
gcc -O3 src\toRawInt.c -o build\sbfm
gcc -O3 -Llibr\ src\interpreter.c -o build\ssbl -lssbl

REM Remove object file
del build\ssbl.o
