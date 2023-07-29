#include <stdlib.h>
#include <string.h>

#include "cube.h"

struct cube *init_cube_solved() {
    struct cube *cube = (struct cube *)malloc(sizeof(struct cube));
    *cube = SOLVED_CUBE;
    return cube;
}

struct cube *init_cube_copy(struct cube *cube) {
    struct cube *copy = (struct cube *)malloc(sizeof(struct cube));
    memcpy(copy, cube, sizeof(struct cube));
    return copy;
}

void turn_up_cw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[1];
    cube->corners[1] = cube->corners[3];
    cube->corners[3] = cube->corners[2];
    cube->corners[2] = stored;
}

void turn_up_half(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[3];
    cube->corners[3] = stored;
    stored = cube->corners[1];
    cube->corners[1] = cube->corners[2];
    cube->corners[2] = stored;
}

void turn_up_ccw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[2];
    cube->corners[2] = cube->corners[3];
    cube->corners[3] = cube->corners[1];
    cube->corners[1] = stored;
}

void turn_down_cw(struct cube *cube) {
    struct corner stored = cube->corners[4];
    cube->corners[4] = cube->corners[5];
    cube->corners[5] = cube->corners[7];
    cube->corners[7] = cube->corners[6];
    cube->corners[6] = stored;
}

void turn_down_half(struct cube *cube) {
    struct corner stored = cube->corners[4];
    cube->corners[4] = cube->corners[7];
    cube->corners[7] = stored;
    stored = cube->corners[5];
    cube->corners[5] = cube->corners[6];
    cube->corners[6] = stored;
}

void turn_down_ccw(struct cube *cube) {
    struct corner stored = cube->corners[4];
    cube->corners[4] = cube->corners[6];
    cube->corners[6] = cube->corners[7];
    cube->corners[7] = cube->corners[5];
    cube->corners[5] = stored;
}

void turn_right_cw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[5];
    cube->corners[5] = cube->corners[1];
    cube->corners[1] = stored;
    cube->corners[0].orientation = (cube->corners[0].orientation + 2) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 1) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 2) % 3;
    cube->corners[1].orientation = (cube->corners[1].orientation + 1) % 3;
}

void turn_right_half(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[5];
    cube->corners[5] = stored;
    stored = cube->corners[1];
    cube->corners[1] = cube->corners[4];
    cube->corners[4] = stored;
}

void turn_right_ccw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[1];
    cube->corners[1] = cube->corners[5];
    cube->corners[5] = cube->corners[4];
    cube->corners[4] = stored;
    cube->corners[0].orientation = (cube->corners[0].orientation + 2) % 3;
    cube->corners[1].orientation = (cube->corners[1].orientation + 1) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 2) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 1) % 3;
}

void turn_left_cw(struct cube *cube) {
    struct corner stored = cube->corners[2];
    cube->corners[2] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[6];
    cube->corners[6] = stored;
    cube->corners[2].orientation = (cube->corners[2].orientation + 1) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 2) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 1) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 2) % 3;
}

void turn_left_half(struct cube *cube) {
    struct corner stored = cube->corners[2];
    cube->corners[2] = cube->corners[7];
    cube->corners[7] = stored;
    stored = cube->corners[3];
    cube->corners[3] = cube->corners[6];
    cube->corners[6] = stored;
}

void turn_left_ccw(struct cube *cube) {
    struct corner stored = cube->corners[2];
    cube->corners[2] = cube->corners[6];
    cube->corners[6] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored;
    cube->corners[2].orientation = (cube->corners[2].orientation + 1) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 2) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 1) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 2) % 3;
}

void turn_front_cw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[2];
    cube->corners[2] = cube->corners[6];
    cube->corners[6] = cube->corners[4];
    cube->corners[4] = stored;
    cube->corners[0].orientation = (cube->corners[0].orientation + 1) % 3;
    cube->corners[2].orientation = (cube->corners[2].orientation + 2) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 1) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 2) % 3;
}

void turn_front_half(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[6];
    cube->corners[6] = stored;
    stored = cube->corners[2];
    cube->corners[2] = cube->corners[4];
    cube->corners[4] = stored;
}

void turn_front_ccw(struct cube *cube) {
    struct corner stored = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[6];
    cube->corners[6] = cube->corners[2];
    cube->corners[2] = stored;
    cube->corners[0].orientation = (cube->corners[0].orientation + 1) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 2) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 1) % 3;
    cube->corners[2].orientation = (cube->corners[2].orientation + 2) % 3;
}

void turn_back_cw(struct cube *cube) {
    struct corner stored = cube->corners[1];
    cube->corners[1] = cube->corners[5];
    cube->corners[5] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored;
    cube->corners[1].orientation = (cube->corners[1].orientation + 2) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 1) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 2) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 1) % 3;
}

void turn_back_half(struct cube *cube) {
    struct corner stored = cube->corners[1];
    cube->corners[1] = cube->corners[7];
    cube->corners[7] = stored;
    stored = cube->corners[3];
    cube->corners[3] = cube->corners[5];
    cube->corners[5] = stored;
}

void turn_back_ccw(struct cube *cube) {
    struct corner stored = cube->corners[1];
    cube->corners[1] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[5];
    cube->corners[5] = stored;
    cube->corners[1].orientation = (cube->corners[1].orientation + 2) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 1) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 2) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 1) % 3;
}
