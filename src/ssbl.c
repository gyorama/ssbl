#include "../include/ssbl.h"
#include <stdio.h>
#include <string.h>
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

// Todo: make work
inline bool divide(int *stack) {
    if (stack[0] < 2) {
        puts("Not enough arguments");
        return true;
    }
    int result = (int)stack[stack[0]] / stack[stack[0]-1]; // Only full divisions for now
    stack[0] -= 2;
    push(stack, (int)result); // double casting because wht the fuck not
    return false;
}
