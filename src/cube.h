#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

struct edge {
    uint8_t cubelet;
    uint8_t orientation;
};

struct corner {
    uint8_t cubelet;
    uint8_t orientation;
};

struct cube {
    struct edge edges[12];
    struct corner corners[8];
};

extern const struct cube SOLVED_CUBE;

struct cube *init_cube_solved();
struct cube *init_cube_copy(const struct cube *);

uint8_t cubes_equal(const struct cube *, const struct cube *);

void turn(struct cube *, uint8_t);

void turn_up_cw(struct cube *);
void turn_up_half(struct cube *);
void turn_up_ccw(struct cube *);

void turn_down_cw(struct cube *);
void turn_down_half(struct cube *);
void turn_down_ccw(struct cube *);

void turn_right_cw(struct cube *);
void turn_right_half(struct cube *);
void turn_right_ccw(struct cube *);

void turn_left_cw(struct cube *);
void turn_left_half(struct cube *);
void turn_left_ccw(struct cube *);

void turn_front_cw(struct cube *);
void turn_front_half(struct cube *);
void turn_front_ccw(struct cube *);

void turn_back_cw(struct cube *);
void turn_back_half(struct cube *);
void turn_back_ccw(struct cube *);

#endif
