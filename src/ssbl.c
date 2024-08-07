#include "../include/ssbl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INDEX 100
typedef bool (*Function)(int *stack);

bool push(int *stack, int value) {
    if (stack[0] > 100) {
        puts("Overflow");
        return true;
    }
    ++stack[0];
    stack[stack[0]] = value;
    return false;
};

bool pop(int *stack) {
    if (stack[0] < 1) {
        puts("Underflow");
        return true;
    }
    --stack[0];
    return false;
};

bool top(int *stack) {
    if (stack[0] < 1) {
        puts("Not valid stack index to print out");
        return true;
    }
    printf("%d\n", stack[stack[0]]);

    return false;
}

bool isEmpty(int *stack) {
    if (stack[0] < 1) {
        return true;
    }
    return false;
}

bool isFull(int *stack) {
    if (stack[0] == 100) {
        return true;
    }
    return false;
}

bool clear(int *stack) {
    if (isEmpty(stack)) {
        return true;
    }
    stack[0] = 0;
    return false;    
}

bool add(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] + stack[stack[0]-1];
    stack[0] -= 2;
    push(stack, result);
    return false;
}

bool subtract(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] - stack[stack[0]-1];
    stack[0] -= 2;
    push(stack, result);
    return false;
}

bool divide(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] / stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

bool multiply(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] * stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

bool dec(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    --stack[stack[0]];
    return false;
}

bool inc(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    ++stack[stack[0]];
    return false;
}

bool loop(int *stack, int times, FILE *source) {
    int loopBeginning = ftell(source);
    int val;
    bool ret;
    
    int16_t keyword;
    Function keywordArr[19] = {push, pop, top, isEmpty, isFull, clear, add,
                               subtract, multiply, divide, loop, ifStatement, swap,
                               dec, inc, size, duplicate};
    
    while (times != 0) {
        fseek(source, loopBeginning, SEEK_SET);
        --times;

        while (fread(&keyword, sizeof(keyword), 1, source) && keyword != END) {
            if (keyword == PUSH) {
                fread(&val, sizeof(int), 1, source);
                ret = push(stack, val);
                if (ret) {
                    fclose(source);
                    perror("Err:");
                    return 1;
                }
            } else if (keyword == IF) {
                fread(&val, sizeof(int), 1, source);
                ret = ifStatement(stack, source, val, ret);
                if (ret) {
                    fclose(source);
                    perror("Err:");
                    return 1;
                }
            } else if (keyword == LOOP) {
                fread(&val, sizeof(int), 1, source);
                ret = loop(stack, val, source);
                if (ret) {
                    fclose(source);
                    perror("Err:");
                    return 1;
                }
            } else if (keyword == END) {
                continue;
            } else {
                ret = keywordArr[keyword](stack);
            }
        }
    }
    return false;
}

bool ifStatement(int *stack, FILE *source, bool condition, bool ret) {
    int16_t keyword;

    if (condition == ret) {
        loop(stack, 1, source); // Reuse loop function because it works
    } else {
        while (fread(&keyword, sizeof(int16_t), 1, source) && keyword != END) {
            continue;
        }
    }
}

bool swap(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int temp = stack[stack[0]];
    stack[stack[0]] = ++stack[stack[0]-1]; // I don't know why but this works
    stack[stack[0]-1] = temp;
    return false;
}

bool size(int *stack) {
    push(stack, stack[0]);
    return false;
}

bool duplicate(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack.\nTry pushing something to the stack");
        return true;
    }
    push(stack, stack[stack[0]]);
    return false;
}