#include <stdint.h>
#include <stdlib.h>

#include "stack.h"

struct stack *init_stack(uint16_t capacity) {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->nodes = (struct stack_node *)malloc(capacity * sizeof(struct stack_node));
    stack->index = 0;
    return stack;
}

void push(struct stack *stack, struct cube cube, uint8_t turn, uint8_t depth) {
    stack->nodes[stack->index++] = (struct stack_node){cube, turn, depth};
}

struct stack_node pop(struct stack *stack) {
    return stack->nodes[--stack->index];
}
