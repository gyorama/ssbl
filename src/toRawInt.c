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

    char valStr[4096];
    int32_t val;
    char *endPtr;
    bool ret;
    char command[200];
    uint8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                    0xAA, 0x55, 0xBA, 0xBE, 0x03};
    enum keywords keyword;
    char *keywordArr_Str[] = {
        "push", "pop", "top", "isempty", "isfull", "clear", "add",
        "sub", "mul", "div", "times", "if", "swap",
        "dec", "inc", "size", "dup", "Eq0", "l0", "l0", "mod",
    };

    // Write ssbl signature so that the interpreter can't run random binary files
    fwrite(&magicFileSignature, sizeof(uint8_t), 9, target);

    while (fscanf(source, "%s", command) != EOF) {

        for (int i = 0; i < sizeof(keywordArr_Str) / sizeof(char*); ++i) { 
            if (strcasecmp(command, keywordArr_Str[i]) == 0) {
                keyword = i;
                fwrite(&keyword, sizeof(uint8_t), 1, target);
                if (keyword == PUSH || keyword == LOOP || keyword == IF) {
                    fscanf(source, "%d", &val);
                    fwrite(&val, sizeof(int32_t), 1, target);
                }
            }
        }
    }

    fclose(source);
    fclose(target);

    return 0;
}
