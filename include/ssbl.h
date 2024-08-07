#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INDEX 2048

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
bool push(int *stack, int value); // Add a value to the stack
bool pop(int *stack); // Remove a value from the stack
bool top(int *stack); // Print out the value on the current stack index
bool isEmpty(int *stack); // Check if the stack is empty
bool isFull(int *stack); // Check if the stack is full
bool clear(int *stack); // Clear the stack

// Math
bool add(int *stack);
bool subtract(int *stack);
bool divide(int *stack);
bool multiply(int *stack);
bool dec(int *stack); // Decrement
bool inc(int *stack); // Increment

// Misc
bool loop(int *stack, int times, FILE *source); // Repeat code inside `times` statement `int times` amount
bool ifStatement(int *stack, FILE *source, bool condition, bool ret); // Crappy conditional statement
bool swap(int *stack); // Swap 2 top stack values
bool size(int *stack); // Print the size of the stack
bool duplicate(int *stack); // Duplicate the top stack value

// 0 comparisons
bool cmpEq0(int *stack); // Compare if top is equal to 0 
bool cmpL0(int *stack); // Compare if top is less than 0
bool cmpG0(int *stack); // Compare if top is greater than 0