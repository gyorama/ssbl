#include "../include/ssbl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INDEX 100
typedef bool (*Function)(int *stack);

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
        puts("Not valid stack index to print out");
        return true;
    }
    printf("%d\n", stack[stack[0]]);

    return false;
}

inline bool isEmpty(int *stack) {
    // There's literally no way this function can fail
    if (stack[0] < 1) {
        return true;
    }
    return false;
}

inline bool isFull(int *stack) {
    // Same for this function
    if (stack[0] == 100) {
        return true;
    }
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
        puts("Not enough values on the stack\nTry pushing something to the stack");
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
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] - stack[stack[0]-1];
    stack[0] -= 2;
    push(stack, result);
    return false;
}

inline bool divide(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] / stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

inline bool multiply(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    int result = stack[stack[0]] * stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, result);
    return false;
}

inline bool dec(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    --stack[stack[0]];
    return false;
}

inline bool inc(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack\nTry pushing something to the stack");
        return true;
    }
    ++stack[stack[0]];
    return false;
}

inline bool loop(int *stack, int times, FILE *source) {
    int loopBeginning = ftell(source);
    int val;
    bool ret;
    
    int16_t keyword;
    
    
    while (times != 0) {
        fseek(source, loopBeginning, SEEK_SET);
        --times;

        while (fread(&keyword, sizeof(keyword), 1, source) && keyword != END) {
        switch (keyword) {
            case PUSH:
                fread(&val, sizeof(val), 1, source);

                ret = push(stack, val);

                if (ret) {
                    return 1;
                }
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
                if (ret) {
                    return 1;
                }
                break;
            
            case IS_FULL:
                ret = isFull(stack);
                if (ret) {
                    return 1;
                }
                break;
        
            case CLEAR:
                ret = clear(stack);
                if (ret) {
                    return 1;
                }
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
                fread(&val, sizeof(val), 1, source);

                ret = loop(stack, val, source);
                if (ret) {
                    return 1;
                }
                break;

            case IF:
                fread(&val, sizeof(bool), 1, source);

                ifStatement(stack, source, val, ret);
                break;

            case SWAP:
                ret = swap(stack);
                if (ret) {
                    return 1;
                }
            
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
                if (ret) {
                    return 1;
                }
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
    }
    return false;
}

inline bool ifStatement(int *stack, FILE *source, bool condition, bool ret) {
    
    int16_t keyword;

    if (condition == ret) {
        loop(stack, 1, source); // I cooked
    } else {
        while (fread(&keyword, sizeof(int16_t), 1, source) && keyword != END) {
            continue;
        }
    }
}

inline bool swap(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int temp = stack[stack[0]];
    stack[stack[0]] = ++stack[stack[0]-1]; // I don't know why but this works
    stack[stack[0]-1] = temp;
    return false;
}

inline bool size(int *stack) {
    push(stack, stack[0]);
    return false;
}

inline bool duplicate(int *stack) {
    if (stack[0] < 1) {
        puts("Not enough values on the stack.\nTry pushing something to the stack");
        return true;
    }
    push(stack, stack[stack[0]]);
    return false;
}

inline bool print(int *stack) {
    if (stack[0] < 1) {
    	puts("Not valid stack index to print out");
    	return true;
    }
    putchar(stack[stack[0]]);
    return false;
}
