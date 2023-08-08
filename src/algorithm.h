#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdint.h>

struct algorithm {
    uint8_t *turns;
    uint16_t n_turns;
};

uint8_t str_to_turn(char *);
struct algorithm str_to_algorithm(char *);

char *turn_to_str(uint8_t);
char *algorithm_to_str(struct algorithm);

#endif
