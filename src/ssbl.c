#include "../include/ssbl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_INDEX 100

inline bool push(int *stack, int value) {
    if (stack[0] > 100) {
        puts("Overflow");
        return true;
    }
    ++stack[0];
    stack[stack[0]] = value; // wtf is stack[stack[0]] bro
    return false;
};

inline bool pop(int *stack) {
    if (stack[0] < 1) {
        puts("Underflow");
        return true;
    }
    --stack[0];
    return false;
};

inline bool top(int *stack) {
    if (stack[0] < 1) {
        puts("Not valid stack index");
        return true;
    }
    printf("%d\n", stack[stack[0]]);

    return false;
}

inline bool isEmpty(int *stack) {
    // There's literally no way this function can fail
    if (stack[0] == 0) {
        puts("Stack is empty");
        return true;
    }
    puts("Stack is not empty");
    return false;
}

inline bool isFull(int *stack) {
    // Same for this function
    if (stack[0] == 100) {
        puts("Stack is full");
        return true;
    }
    puts("Stack is not full");
    return false;
}

inline bool clear(int *stack) {
    if (isEmpty(stack)) {
        return true;
    }
    stack[0] = 0;
    return false;    
}

inline bool add(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int result = stack[stack[0]] + stack[stack[0]-1];
    stack[0] -= 2;
    push(stack, result); // This is so unreadable but fuck it
    return false;
}

// That's literally add copypasted but with a -
inline bool subtract(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int result = stack[stack[0]] - stack[stack[0]-1];
    stack[0] -= 2;
    push(stack, result);
    return false;
}

inline bool divide(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int result = stack[stack[0]] / stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

inline bool multiply(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int result = stack[stack[0]] * stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

// Felt bad about making nested loops so I made it a function
// Todo: Make this shit work
inline bool loop(int *stack, int times, FILE *source) {
    int loopBeginning = ftell(source);
    char valStr[13];
    int val;
    char *endPtr;
    bool ret;

    char command[200];
    
    
    while (times != 0) {
        fseek(source, loopBeginning, SEEK_SET);
        memset(command, 0, 200);
        --times;
        // Never fucking mind
        while (fscanf(source, "%s", &command) != EOF && strcasecmp(command, "end") != 0) {
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
            } else if (strcasecmp(command, "div") == 0) {
                ret = divide(stack);
            } else if (strcasecmp(command, "mul") == 0) {
                ret = multiply(stack);
            } else if (strcasecmp(command, "times") == 0) {
                fscanf(source, "%s", valStr);
                val = strtol(valStr, &endPtr, 10);
                if (*endPtr == '\0') {
                    ret = loop(stack, val, source);
                    if (ret) {
                        break;
                    }
                }
            }
        }
    }
    return false;
}