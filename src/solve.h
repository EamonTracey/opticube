#ifndef SOLVE_H
#define SOLVE_H

#include <stdint.h>

#include "cube.h"

struct stack_node {
    struct cube *cube;
    uint8_t turn;
    uint8_t depth;
};

uint8_t heuristic(struct cube *);
uint8_t *solve(struct cube *, uint16_t *);

#endif
