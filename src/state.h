#ifndef STATE_H
#define STATE_H

#include <stdint.h>

#include "cube.h"

uint32_t six_edges_a_state(struct cube *);
uint32_t six_edges_b_state(struct cube *);
uint32_t corners_state(struct cube *);

#endif
