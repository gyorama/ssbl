#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// All stuff is inline just in case the compiler actually decides to inline

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
bool loop(int *stack, int times, FILE *source);