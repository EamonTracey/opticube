#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

uint8_t *generate_depth_table(uint32_t (*)(struct cube *), uint32_t);
void write_depth_table(char *, uint8_t *, uint32_t);
void load_depth_table(char *, uint32_t);

#endif
