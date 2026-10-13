#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_init(Stack *s) {
    s->size = 0;
    s->capacity = 4;
    s->data = (STACK_VALUE_T*)malloc(s->capacity * sizeof(STACK_VALUE_T));
    if (!s->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    } 
}

void stack_free(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}

int stack_is_empty(Stack *s) {
    return s->size == 0;
}

void stack_push(Stack *s, STACK_VALUE_T value) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        STACK_VALUE_T *new_data = (STACK_VALUE_T*)realloc(s->data, s->capacity * sizeof(STACK_VALUE_T));
        if (!new_data) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        s->data = new_data;
    }
    s->data[s->size] = value;
    s->size++;
}

STACK_VALUE_T stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Error: pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    s->size--;
    return s->data[s->size];
}

STACK_VALUE_T stack_get_from_bottom(Stack *s, int index) {
    if (index < 0 || index >= s->size) {
        fprintf(stderr, "Error: index %d out of range [0, %d]\n", index, s->size - 1);
        exit(EXIT_FAILURE);
    }
    return s->data[index];
}

STACK_VALUE_T stack_get_by_offset(Stack *s, int base_index, int offset) {
    int target_index = base_index + offset;
    if (target_index < 0 || target_index >= s->size) {
        fprintf(stderr, "Error: resulting index %d out of range [0, %d]\n",
                target_index, s->size - 1);
        exit(EXIT_FAILURE);
    }
    return s->data[target_index];
}

void stack_set_from_bottom(Stack* s, int index, STACK_VALUE_T value)
{
    if (index < 0 || index >= s->size) {
        fprintf(stderr, "Error: index %d out of range [0, %d]\n", index, s->size - 1);
        exit(EXIT_FAILURE);
    }
    s->data[index] = value;
}