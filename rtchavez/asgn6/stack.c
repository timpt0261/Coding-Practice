//stack.c

#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Stack Stack;

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **stack;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = 0;
        s->capacity = capacity;
        s->stack = (Node **) malloc(s->capacity * sizeof(Node *));
        if (s->stack == NULL) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (s) {
        free(s->stack[]);
        *s
    }
    free(**s);
    *s = NULL;
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        s->capacity *= 2;
        s->stack = (Node **) realloc(s->stack, s->capacity * sizeof(Node *));
    }

    s->top += 1;
    s->stack[s->top] = n;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *n = s->stack[s->top];
    return true;
}

void stack_print(Stack *s) {
    printf(stderr,
        "Stack Current Top: %d\n"
        "Stack Capactiy: %d\n"
        s->top, s->capacity);
}
