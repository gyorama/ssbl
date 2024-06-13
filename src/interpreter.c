#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ssbl.h"
#include <stdbool.h>
#include <stdint.h>


bool arrncmp(int8_t arr1[], int8_t arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false; // Arrays are different
        }
    }
    return true; // Arrays are the same
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        puts("USAGE:"
             "\tssbl [BINARY FILE]");
        return 1;
    }

    int stack[101]; // The stack, which is really just an array
    stack[0] = 0;

    FILE *source = fopen(argv[1], "rb");
    int8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                 0xAA, 0x55, 0xBA, 0xBE, 0x03};
    int8_t signatureCheck[9];
    int keyword;
    int val;
    bool ret;    

    if (!source) {
        perror("Could not open file");
        return 1;
    }

    fread(&signatureCheck, sizeof(signatureCheck), 1, source);

    if (!arrncmp(signatureCheck, magicFileSignature, 9)) {
        puts("Invalid file format");
        return 1;
    }

    while (fread(&keyword, sizeof(int16_t), 1, source)) {
        switch (keyword) {
            case PUSH:
                fread(&val, sizeof(int), 1, source);

                ret = push(stack, val);
                break;
        
            case POP:
                ret = pop(stack);
                if (ret) {
                    return 1;
                }
                break;

            case TOP:
                
                ret = top(stack);
                if (ret) {
                    return 1;
                }
                break;

            case IS_EMPTY:
                ret = isEmpty(stack);
                break;
            
            case IS_FULL:
                ret = isFull(stack);
                break;
        
            case CLEAR:
                ret = clear(stack);
                
                break;

            case ADD:
                ret = add(stack);
                if (ret) {
                    return 1;
                }
                break;
            
            case SUBTRACT:
                ret = subtract(stack);
                if (ret) {
                    return 1;
                }
                break;

            case MULTIPLY:
                ret = multiply(stack);
                if (ret) {
                    return 1;
                }
                break;

            case DIVIDE:
                ret = divide(stack);
                if (ret) {
                    return 1;
                }
                break;

            case LOOP:
                fread(&val, sizeof(int), 1, source);

                ret = loop(stack, val, source);
                break;     

            case IF:
                fread(&val, sizeof(int8_t), 1, source);

                ifStatement(stack, source, val, ret);

                break;

            case SWAP:
                ret = swap(stack);
                if (ret) {
                    return 1;
                }
                break;
            case DEC:
                ret = dec(stack);
                if (ret) {
                    return 1;
                }
                break;

            case INC:
                ret = inc(stack);
                if (ret) {
                    return 1;
                }
                break;

            case SIZE:
                ret = size(stack);
                
                break;
            
            case DUPLICATE:
                ret = duplicate(stack);
                if (ret) {
                    return 1;
                }
                break;

            default:
                break;
        }
    }
    fclose(source);

    return 0;
}
