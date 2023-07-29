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
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[3];
    cube->edges[3] = cube->edges[1];
    cube->edges[1] = cube->edges[2];
    cube->edges[2] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[1];
    cube->corners[1] = cube->corners[3];
    cube->corners[3] = cube->corners[2];
    cube->corners[2] = stored_corner;
}

void turn_up_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[3];
    cube->corners[3] = stored_corner;
    stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[2];
    cube->corners[2] = stored_corner;
}

void turn_up_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[2];
    cube->corners[2] = cube->corners[3];
    cube->corners[3] = cube->corners[1];
    cube->corners[1] = stored_corner;
}

void turn_down_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[4];
    cube->edges[4] = cube->edges[6];
    cube->edges[6] = cube->edges[5];
    cube->edges[5] = cube->edges[7];
    cube->edges[7] = stored_edge;

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[5];
    cube->corners[5] = cube->corners[7];
    cube->corners[7] = cube->corners[6];
    cube->corners[6] = stored_corner;
}

void turn_down_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[5];
    cube->corners[5] = cube->corners[6];
    cube->corners[6] = stored_corner;
}

void turn_down_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[6];
    cube->corners[6] = cube->corners[7];
    cube->corners[7] = cube->corners[5];
    cube->corners[5] = stored_corner;
}

void turn_right_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[8];
    cube->edges[8] = cube->edges[4];
    cube->edges[4] = cube->edges[9];
    cube->edges[9] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[5];
    cube->corners[5] = cube->corners[1];
    cube->corners[1] = stored_corner;
    cube->corners[0].orientation = (cube->corners[0].orientation + 2) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 1) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 2) % 3;
    cube->corners[1].orientation = (cube->corners[1].orientation + 1) % 3;
}

void turn_right_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[5];
    cube->corners[5] = stored_corner;
    stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[4];
    cube->corners[4] = stored_corner;
}

void turn_right_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[1];
    cube->corners[1] = cube->corners[5];
    cube->corners[5] = cube->corners[4];
    cube->corners[4] = stored_corner;
    cube->corners[0].orientation = (cube->corners[0].orientation + 2) % 3;
    cube->corners[1].orientation = (cube->corners[1].orientation + 1) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 2) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 1) % 3;
}

void turn_left_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[1];
    cube->edges[1] = cube->edges[11];
    cube->edges[11] = cube->edges[5];
    cube->edges[5] = cube->edges[10];
    cube->edges[10] = stored_edge;

    struct corner stored_corner = cube->corners[2];
    cube->corners[2] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[6];
    cube->corners[6] = stored_corner;
    cube->corners[2].orientation = (cube->corners[2].orientation + 1) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 2) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 1) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 2) % 3;
}

void turn_left_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[2];
    cube->corners[2] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[3];
    cube->corners[3] = cube->corners[6];
    cube->corners[6] = stored_corner;
}

void turn_left_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[2];
    cube->corners[2] = cube->corners[6];
    cube->corners[6] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored_corner;
    cube->corners[2].orientation = (cube->corners[2].orientation + 1) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 2) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 1) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 2) % 3;
}

void turn_front_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[2];
    cube->edges[2] = cube->edges[10];
    cube->edges[10] = cube->edges[6];
    cube->edges[6] = cube->edges[8];
    cube->edges[8] = stored_edge;
    cube->edges[2].orientation = (cube->edges[2].orientation + 1) % 2;
    cube->edges[10].orientation = (cube->edges[10].orientation + 1) % 2;
    cube->edges[6].orientation = (cube->edges[6].orientation + 1) % 2;
    cube->edges[8].orientation = (cube->edges[8].orientation + 1) % 2;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[2];
    cube->corners[2] = cube->corners[6];
    cube->corners[6] = cube->corners[4];
    cube->corners[4] = stored_corner;
    cube->corners[0].orientation = (cube->corners[0].orientation + 1) % 3;
    cube->corners[2].orientation = (cube->corners[2].orientation + 2) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 1) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 2) % 3;
}

void turn_front_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[6];
    cube->corners[6] = stored_corner;
    stored_corner = cube->corners[2];
    cube->corners[2] = cube->corners[4];
    cube->corners[4] = stored_corner;
}

void turn_front_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[6];
    cube->corners[6] = cube->corners[2];
    cube->corners[2] = stored_corner;
    cube->corners[0].orientation = (cube->corners[0].orientation + 1) % 3;
    cube->corners[4].orientation = (cube->corners[4].orientation + 2) % 3;
    cube->corners[6].orientation = (cube->corners[6].orientation + 1) % 3;
    cube->corners[2].orientation = (cube->corners[2].orientation + 2) % 3;
}

void turn_back_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[3];
    cube->edges[3] = cube->edges[9];
    cube->edges[9] = cube->edges[7];
    cube->edges[7] = cube->edges[11];
    cube->edges[11] = stored_edge;
    cube->edges[3].orientation = (cube->edges[3].orientation + 1) % 2;
    cube->edges[9].orientation = (cube->edges[9].orientation + 1) % 2;
    cube->edges[7].orientation = (cube->edges[7].orientation + 1) % 2;
    cube->edges[11].orientation = (cube->edges[11].orientation + 1) % 2;

    struct corner stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[5];
    cube->corners[5] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored_corner;
    cube->corners[1].orientation = (cube->corners[1].orientation + 2) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 1) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 2) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 1) % 3;
}

void turn_back_half(struct cube *cube) {
    struct corner stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[3];
    cube->corners[3] = cube->corners[5];
    cube->corners[5] = stored_corner;
}

void turn_back_ccw(struct cube *cube) {
    struct corner stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[5];
    cube->corners[5] = stored_corner;
    cube->corners[1].orientation = (cube->corners[1].orientation + 2) % 3;
    cube->corners[3].orientation = (cube->corners[3].orientation + 1) % 3;
    cube->corners[7].orientation = (cube->corners[7].orientation + 2) % 3;
    cube->corners[5].orientation = (cube->corners[5].orientation + 1) % 3;
}
