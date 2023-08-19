#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#include "cube.h"

struct stack_node {
    struct cube cube;
    uint8_t turn;
    uint8_t depth;
};

struct stack {
    struct stack_node *nodes;
    uint16_t index;
};

struct stack *init_stack(uint16_t);
void push(struct stack *, struct cube, uint8_t, uint8_t);
struct stack_node pop(struct stack *);

#endif
