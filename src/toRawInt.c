#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../include/ssbl.h"


int main(int argc, const char *argv[]) {
    if (argc < 3) {
        puts("USAGE:"
             "\tsbfm [SOURCE FILE] [BYTECODE FILE]");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    FILE *target = fopen(argv[2], "wb");

    if (!source || !target) {
        perror("Could not open file");
        return 1;
    }

    char valStr[20];
    int32_t val;
    char *endPtr;
    bool ret;
    char command[200];
    uint8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                    0xAA, 0x55, 0xBA, 0xBE, 0x03};
    enum keywords keyword;

    // Write ssbl signature so that the interpreter can't run random binary files
    fwrite(&magicFileSignature, sizeof(uint8_t), 9, target);

    while (fscanf(source, "%s", command) != EOF) {
        if (strcasecmp(command, "push") == 0) {
            keyword = PUSH;

            fscanf(source, "%d", &val);
            fwrite(&keyword, sizeof(uint8_t), 1, target);
            fwrite(&val, sizeof(int32_t), 1, target);
        } else if (strcasecmp(command, "pop") == 0) {
            keyword = POP;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "top") == 0) {
            keyword = TOP;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "isempty") == 0) {
            keyword = IS_EMPTY;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "isfull") == 0) {
            keyword = IS_FULL;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "clear") == 0) {
            keyword = CLEAR;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "add") == 0) {
            keyword = ADD;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "sub") == 0) {
            keyword = SUBTRACT;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "div") == 0) {
            keyword = DIVIDE;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "mul") == 0) {
            keyword = MULTIPLY;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "times") == 0) {
            keyword = LOOP;
            fscanf(source, "%s", &valStr);

            if (strcmp(valStr, "_") == 0) {
                val = LAST_STACK_VAL;
            } else {
                val = strtol(valStr, &endPtr, 10);
            
                if (*endPtr != '\0') {
                    puts("Invalid integer");
                    return 1;
                }
            }

            fwrite(&keyword, sizeof(uint8_t), 1, target);
            fwrite(&val, sizeof(int32_t), 1, target);
        } else if (strcasecmp(command, "end") == 0) {
            keyword = END;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "if") == 0) {
            fscanf(source, "%s", valStr);
            if (strcasecmp(valStr, "true") == 0 || strcmp(valStr, "1") == 0) {
                val = true;
            } else if (strcasecmp(valStr, "false") == 0 || strcmp(valStr, "0") == 0) {
                val = false;
            } else {
                puts("Only boolean conditions are supported now.");
                fclose(source);
                fclose(target);
                return 1;
            }

            keyword = IF;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
            fwrite(&val, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "swap") == 0) {
            keyword = SWAP;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "dec") == 0) {
            keyword = DEC;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "inc") == 0) {
            keyword = INC;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "size") == 0) {
            keyword = SIZE;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "dup") == 0) {
            keyword = DUPLICATE;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "Eq0") == 0) {
            keyword = EQ_0;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "L0") == 0) {
            keyword = L_0;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "G0") == 0) {
            keyword = G_0;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else if (strcasecmp(command, "prnt") == 0) {
            keyword = PRINT;
            fwrite(&keyword, sizeof(uint8_t), 1, target);
        } else {
            printf("Unknown function '%s'", &command);
            fclose(source);
            fclose(target);
            return 1;
        }
    }

    fclose(source);
    fclose(target);

    return 0;
}
