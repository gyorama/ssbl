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
    Function keywordArr[] = {push, pop, top, isEmpty, isFull, clear, add, subtract,
                           divide, multiply, dec, inc, loop, ifStatement, swap,
                           size, duplicate, print};

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

            case LOOP:
                fread(&val, sizeof(int), 1, source);

                ret = loop(stack, val, source);
                break;     

            case IF:
                fread(&val, sizeof(int8_t), 1, source);

                ifStatement(stack, source, val, ret);

                break;

            default:
                keywordArr[val](stack);
                break;
        }
    }
    fclose(source);

    return 0;
}
