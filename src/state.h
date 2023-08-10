#ifndef STATE_H
#define STATE_H

#include <stdint.h>

#include "cube.h"

uint32_t first_six_edges_state(struct cube *);
uint32_t second_six_edges_state(struct cube *);
uint32_t corners_state(struct cube *);

#endif
