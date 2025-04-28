#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../include/ssbl.h"


int main(int argc, const char *argv[]) {
    if (argc < 3) {
        puts("USAGE:"
             "\tsbfm [source].ssbl [output]");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    FILE *target = fopen(argv[2], "wb");

    if (!source || !target) {
        perror("Could not open file");
        return 1;
    }

    int16_t varArr[400];
    memset(varArr, INT16_MIN, sizeof(int16_t));

    char command[200];
    char *cmdPtr = command;
    char *word = calloc(200, sizeof(char));
    uint8_t magicFileSignature[9] = {0xAF, 0x00, 0xDD, 0xF0,
                                    0xAA, 0x55, 0xBA, 0xBE, 0x03};

    // Write ssbl signature so that the interpreter can't run random binary files
    fwrite(&magicFileSignature, sizeof(uint8_t), 9, target);

    while (fscanf(source, "%s", command) != EOF) {
        if (command[0] == '@') {
            printf("%s: function\n", cmdPtr);
            memcpy(word, cmdPtr, strlen(command)+1);
        } else if (command[0] == '#') {
            printf("%s: variable\n", cmdPtr);
            if (atoi(cmdPtr) < 1) {
                puts("Variable index can't be less than 1\nVariable can't be named with text");
                return 1;
            }
            memcpy(word, cmdPtr, strlen(command)+1);
        } else {
            printf("%s: value to %s\n", cmdPtr, word);
        }
        
    }

    fclose(source);
    fclose(target);

    return 0;
}
