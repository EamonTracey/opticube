#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdint.h>

uint8_t str_to_turn(char *);
uint8_t *str_to_algorithm(char *, uint16_t *);

char *turn_to_str(uint8_t);
char *algorithm_to_str(uint8_t *, uint16_t);

#endif
