#ifndef STACK_H
#define STACK_H

typedef long long STACK_VALUE_T ;

typedef struct {
    STACK_VALUE_T *data;
    int size;
    int capacity;
} Stack;

void stack_init(Stack *s);
void stack_free(Stack *s);
int stack_is_empty(Stack *s);
void stack_push(Stack *s, STACK_VALUE_T value);
STACK_VALUE_T stack_pop(Stack *s);
STACK_VALUE_T stack_get_from_bottom(Stack *s, int index);
STACK_VALUE_T stack_get_by_offset(Stack *s, int base_index, int offset);
void stack_set_from_bottom(Stack* s, int index, STACK_VALUE_T value);
 
#endif