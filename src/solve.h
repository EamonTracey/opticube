#ifndef SOLVE_H
#define SOLVE_H

#include "cube.h"

struct stack_node {
    struct cube *cube;
    struct stack_node *parent;
    uint8_t turn;
    uint8_t depth;
};

void solve(struct cube *, int *);

#endif
