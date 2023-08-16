#ifndef STATE_H
#define STATE_H

#include <stdint.h>

#include "cube.h"

uint32_t eo_equator_combination_state(const struct cube *);
uint32_t co_equator_combination_state(const struct cube *);

uint32_t six_edges_a_state(const struct cube *);
uint32_t six_edges_b_state(const struct cube *);
uint32_t corners_state(const struct cube *);

#endif
