#ifndef TWOP_H
#define TWOP_H

#include <stdint.h>

#include "cube.h"

uint8_t phase_one_heuristic(const struct cube *);
uint8_t phase_one_complete(const struct cube *);

uint8_t phase_two_heuristic(const struct cube *);

uint8_t *twop_solve(const struct cube *, uint16_t *);

#endif
