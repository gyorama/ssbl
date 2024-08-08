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

    int32_t stack[MAX_INDEX + 1]; // The stack, which is really just an array
    stack[0] = 0;

    FILE *source = fopen(argv[1], "rb");
    int8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                 0xAA, 0x55, 0xBA, 0xBE, 0x03};
    int8_t signatureCheck[9];
    uint8_t keyword;
    int32_t val;
    bool ret;

    // Array of functions that the language can do
    // Ignore "incompatible pointer" warnings, it's already handled
    Function keywordArr[20] = {push, pop, top, isEmpty, isFull, clear, add,
                               subtract, multiply, divide, loop, ifStatement, swap,
                               dec, inc, size, duplicate, cmpEq0, cmpL0, cmpG0};

    if (!source) {
        perror("Could not open file");
        return 1;
    }

    fread(&signatureCheck, sizeof(signatureCheck), 1, source);

    if (!arrncmp(signatureCheck, magicFileSignature, 9)) {
        puts("Invalid file format");
        return 1;
    }

    while (fread(&keyword, sizeof(uint8_t), 1, source)) {
        // Special cases
        if (keyword == PUSH) {
            fread(&val, sizeof(int32_t), 1, source);

            ret = push(stack, val);

            if (ret) {
                fclose(source);
                perror("Err");
                return 1;
            }
        } else if (keyword == IF) {
            fread(&val, sizeof(bool), 1, source);

            ifStatement(stack, source, keywordArr, val, ret);
            
        } else if (keyword == LOOP) {
            fread(&val, sizeof(int32_t), 1, source);

            loop(stack, val, source, keywordArr);

            if (ret) {
                fclose(source);
                perror("Err");
                return 1;
            }
        } else if (keyword == END) {
            continue;
        } else {
            // Every other function
            keywordArr[keyword](stack);
        }
    }
    fclose(source);

    return 0;
}
