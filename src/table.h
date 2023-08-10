#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

#include "cube.h"

uint8_t *generate_depth_table(uint32_t (*)(const struct cube *), uint32_t);
void write_depth_table(const char *, const uint8_t *, uint32_t);
uint8_t *read_depth_table(const char *, uint32_t);

#endif
