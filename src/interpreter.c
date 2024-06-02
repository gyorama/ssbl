#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ssbl.h"
#include <stdbool.h>


int main(int argc, const char *argv[]) {
    if (argc < 2) {
        puts("USAGE:"
             "\tssbl [SOURCE FILE]");
        return 1;
    }

    int stack[101]; // The stack, which is really just an array
    stack[0] = 0;
    char valStr[13];
    int val;
    char *endPtr;
    bool ret;

    FILE *source = fopen(argv[1], "r");

    char command[200]; // if you buffer overflow this shit istg

    if (!source) {
        perror("Could not open file");
        return 1;
    }

    while (fscanf(source, "%s", command) != EOF) {

        // This is atrocious
        if (strcasecmp(command, "push") == 0) {
            fscanf(source, "%s", valStr);
            val = strtol(valStr, &endPtr, 10);
            // Make sure this is a valid integer
            if (*endPtr == '\0') {
                ret = push(stack, val);
                // if function failed
                if (ret) {
                    break;
                }
                
            } else {
                puts("Invalid integer");
            }
        // Code gets better from here
        } else if (strcasecmp(command, "pop") == 0) {
            ret = pop(stack);
            if (ret) {
                break;
            }
        } else if (strcasecmp(command, "top") == 0) {
            ret = top(stack);
            if (ret) {
                break;
            }
        } else if (strcasecmp(command, "isempty") == 0) {
            ret = isEmpty(stack);
        } else if (strcasecmp(command, "isfull") == 0) {
            ret = isFull(stack);
        } else if (strcasecmp(command, "clear") == 0) {
            ret = clear(stack);
        } else if (strcasecmp(command, "add") == 0) {
            ret = add(stack);
        } else if (strcasecmp(command, "sub") == 0) {
            ret = subtract(stack);
        } /* else if (strcasecmp(command, "div") == 0) {
            ret = subtract(stack);
        } */
    }

    fclose(source);

    return 0;
}