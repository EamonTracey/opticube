#ifndef KORF_H
#define KORF_H

#include <stdint.h>

#include "cube.h"

uint8_t korf_heuristic(const struct cube *);
uint8_t *korf_solve(const struct cube *, uint16_t *);

#endif
