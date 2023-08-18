#ifndef KORF_H
#define KORF_H

#include <stdint.h>

#include "cube.h"

struct stack_node {
    struct cube cube;
    uint8_t turn;
    uint8_t depth;
};

void load_depth_tables();
uint8_t korf_heuristic(const struct cube *);
uint8_t *korf_solve(const struct cube *, uint16_t *);

#endif
