#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

#include "cube.h"

uint8_t *generate_depth_table(uint32_t (*)(struct cube *), uint32_t);
void write_depth_table(char *, uint8_t *, uint32_t);
uint8_t *read_depth_table(char *, uint32_t);

#endif
