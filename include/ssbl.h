#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum keywords {
    PUSH = 0,
    POP,
    TOP,
    IS_EMPTY,
    IS_FULL,
    CLEAR,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LOOP,
    END,
    IF,
    SWAP,
    DEC,
    INC,
    SIZE,
    DUPLICATE,
};

typedef bool (*Function)(int *stack);
// Main things
bool push(int *stack, int value);
bool pop(int *stack);
bool top(int *stack);
bool isEmpty(int *stack);
bool isFull(int *stack);
bool clear(int *stack);

// Math
bool add(int *stack);
bool subtract(int *stack);
bool divide(int *stack);
bool multiply(int *stack);
bool dec(int *stack);
bool inc(int *stack);

// Misc
bool loop(int *stack, int times, FILE *source);
bool ifStatement(int *stack, FILE *source, bool condition, bool ret);
bool swap(int *stack);
bool size(int *stack);
bool duplicate(int *stack);
bool print(int *stack);
