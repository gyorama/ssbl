#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../include/ssbl.h"


int main(int argc, const char *argv[]) {
    if (argc < 3) {
        puts("USAGE:"
             "\tsbcm [SOURCE FILE] [BYTECODE FILE]");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    FILE *target = fopen(argv[2], "wb");

    if (!source || !target) {
        perror("Could not open file");
        return 1;
    }

    char valStr[20];
    int val;
    char *endPtr;
    bool ret;
    char command[200];
    int8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                    0xAA, 0x55, 0xBA, 0xBE, 0x03};
    enum keywords keyword;

    // Write ssbl signature so that the interpreter can't run random binary files
    // What are the chances the 1st 9 bytes in a random file are the exact same as this one anyway
    fwrite(&magicFileSignature, sizeof(int8_t), 9, target);

    while (fscanf(source, "%s", command) != EOF) {

        // This is atrocious
        if (strcasecmp(command, "push") == 0) {
            keyword = PUSH;

            fscanf(source, "%s", valStr);
            val = strtol(valStr, &endPtr, 10);
            
            if (*endPtr == '\0') {
                fwrite(&keyword, sizeof(int16_t), 1, target);
                fwrite(&val, sizeof(int), 1, target);
            } else {
                puts("Invalid integer");
                return 1;
            }
        // Code gets better from here
        } else if (strcasecmp(command, "pop") == 0) {
            keyword = POP;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "top") == 0) {
            keyword = TOP;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "isempty") == 0) {
            keyword = IS_EMPTY;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "isfull") == 0) {
            keyword = IS_FULL;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "clear") == 0) {
            keyword = CLEAR;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "add") == 0) {
            keyword = ADD;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "sub") == 0) {
            keyword = SUBTRACT;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "div") == 0) {
            keyword = DIVIDE;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "mul") == 0) {
            keyword = MULTIPLY;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "times") == 0) {
            keyword = LOOP;
            fscanf(source, "%s", valStr);
            val = strtol(valStr, &endPtr, 10);
            fwrite(&keyword, sizeof(int16_t), 1, target);
            // Make sure this is a valid integer
            if (*endPtr == '\0') {
                fwrite(&val, sizeof(int), 1, target);
            } else {
                puts("Invalid integer");
                return 1;
            }
        } else if (strcasecmp(command, "end") == 0) {
            keyword = END;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "if") == 0) {
            fscanf(source, "%s", valStr);
            if (strcasecmp(valStr, "true") == 0) {
                val = true;
            } else {
                val = false;
            }

            keyword = IF;
            fwrite(&keyword, sizeof(int16_t), 1, target);
            fwrite(&val, sizeof(int8_t), 1, target);
        } else if (strcasecmp(command, "swap") == 0) {
            keyword = SWAP;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "dec") == 0) {
            keyword = DEC;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "inc") == 0) {
            keyword = INC;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "size") == 0) {
            keyword = SIZE;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else if (strcasecmp(command, "duplicate") == 0) {
            keyword = DUPLICATE;
            fwrite(&keyword, sizeof(int16_t), 1, target);
        } else {
            printf("Unknown function '%s'", &command);
        }
    }

    fclose(source);
    fclose(target);

    return 0;
}