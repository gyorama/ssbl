#include <stdbool.h>
// All stuff is inline just in case the compiler actually decides to inline

// Main things
bool push(int *stack, int value);
bool pop(int *stack);
bool top(int *stack);
bool isEmpty(int *stack);
bool isFull(int *stack);
bool clear(int *stack);

// Math
bool add();
bool subtract();
bool divide();
bool multiply();