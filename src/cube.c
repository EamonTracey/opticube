#include <stdlib.h>
#include <string.h>

#include "cube.h"

void (*turns[])(struct cube *) = {
    turn_up_cw, turn_up_half, turn_up_ccw,
    turn_down_cw, turn_down_half, turn_down_ccw,
    turn_right_cw, turn_right_half, turn_right_ccw,
    turn_left_cw, turn_left_half, turn_left_ccw,
    turn_front_cw, turn_front_half, turn_front_ccw,
    turn_back_cw, turn_back_half, turn_back_ccw,
};

const uint8_t edge_flip[] = { 1, 0 };
const uint8_t corner_twist_cw[] = { 1, 2, 0 };
const uint8_t corner_twist_ccw[] = { 2, 0, 1 };

struct cube *init_cube_solved() {
    struct cube *cube = (struct cube *)malloc(sizeof(struct cube));
    *cube = SOLVED_CUBE;
    return cube;
}

struct cube *init_cube_copy(const struct cube *cube) {
    struct cube *copy = (struct cube *)malloc(sizeof(struct cube));
    memcpy(copy, cube, sizeof(struct cube));
    return copy;
}

uint8_t cubes_equal(const struct cube *cube1, const struct cube *cube2) {
    return 
       memcmp(cube1->edges, cube2->edges, sizeof(struct edge[12])) == 0 &&
       memcmp(cube1->corners, cube2->corners, sizeof(struct corner[8])) == 0;
}

void turn(struct cube *cube, uint8_t turn) {
    turns[turn](cube);
}

void turn_up_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[5];
    cube->edges[5] = cube->edges[1];
    cube->edges[1] = cube->edges[4];
    cube->edges[4] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[1];
    cube->corners[1] = cube->corners[5];
    cube->corners[5] = stored_corner;
}

void turn_up_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[1];
    cube->edges[1] = stored_edge;
    stored_edge = cube->edges[4];
    cube->edges[4] = cube->edges[5];
    cube->edges[5] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[1];
    cube->corners[1] = stored_corner;
    stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[5];
    cube->corners[5] = stored_corner;
}

void turn_up_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[4];
    cube->edges[4] = cube->edges[1];
    cube->edges[1] = cube->edges[5];
    cube->edges[5] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[5];
    cube->corners[5] = cube->corners[1];
    cube->corners[1] = cube->corners[4];
    cube->corners[4] = stored_corner;
}

void turn_down_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[2];
    cube->edges[2] = cube->edges[6];
    cube->edges[6] = cube->edges[3];
    cube->edges[3] = cube->edges[7];
    cube->edges[7] = stored_edge;

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[2];
    cube->corners[2] = stored_corner;
}

void turn_down_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[2];
    cube->edges[2] = cube->edges[3];
    cube->edges[3] = stored_edge;
    stored_edge = cube->edges[6];
    cube->edges[6] = cube->edges[7];
    cube->edges[7] = stored_edge;

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[2];
    cube->corners[2] = cube->corners[3];
    cube->corners[3] = stored_corner;
}

void turn_down_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[2];
    cube->edges[2] = cube->edges[7];
    cube->edges[7] = cube->edges[3];
    cube->edges[3] = cube->edges[6];
    cube->edges[6] = stored_edge;

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[2];
    cube->corners[2] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored_corner;
}

void turn_right_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[8];
    cube->edges[8] = cube->edges[2];
    cube->edges[2] = cube->edges[9];
    cube->edges[9] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[2];
    cube->corners[2] = cube->corners[4];
    cube->corners[4] = stored_corner;
    cube->corners[0].orientation = corner_twist_ccw[cube->corners[0].orientation];
    cube->corners[4].orientation = corner_twist_cw[cube->corners[4].orientation];
    cube->corners[2].orientation = corner_twist_ccw[cube->corners[2].orientation];
    cube->corners[4].orientation = corner_twist_cw[cube->corners[4].orientation];
}

void turn_right_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[2];
    cube->edges[2] = stored_edge;
    stored_edge = cube->edges[8];
    cube->edges[8] = cube->edges[9];
    cube->edges[9] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[2];
    cube->corners[2] = stored_corner;
    stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[4];
    cube->corners[4] = stored_corner;
}

void turn_right_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[0];
    cube->edges[0] = cube->edges[9];
    cube->edges[9] = cube->edges[2];
    cube->edges[2] = cube->edges[8];
    cube->edges[8] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[2];
    cube->corners[2] = cube->corners[4];
    cube->corners[4] = stored_corner;
    cube->corners[0].orientation = corner_twist_ccw[cube->corners[0].orientation];
    cube->corners[4].orientation = corner_twist_cw[cube->corners[4].orientation];
    cube->corners[2].orientation = corner_twist_ccw[cube->corners[2].orientation];
    cube->corners[4].orientation = corner_twist_cw[cube->corners[4].orientation];
}

void turn_left_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[1];
    cube->edges[1] = cube->edges[11];
    cube->edges[11] = cube->edges[3];
    cube->edges[3] = cube->edges[10];
    cube->edges[10] = stored_edge;

    struct corner stored_corner = cube->corners[5];
    cube->corners[5] = cube->corners[1];
    cube->corners[1] = cube->corners[7];
    cube->corners[7] = cube->corners[3];
    cube->corners[3] = stored_corner;
    cube->corners[5].orientation = corner_twist_cw[cube->corners[5].orientation];
    cube->corners[1].orientation = corner_twist_ccw[cube->corners[1].orientation];
    cube->corners[7].orientation = corner_twist_cw[cube->corners[7].orientation];
    cube->corners[3].orientation = corner_twist_ccw[cube->corners[3].orientation];
}

void turn_left_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[1];
    cube->edges[1] = cube->edges[3];
    cube->edges[3] = stored_edge;
    stored_edge = cube->edges[10];
    cube->edges[10] = cube->edges[11];
    cube->edges[11] = stored_edge;

    struct corner stored_corner = cube->corners[5];
    cube->corners[5] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[3];
    cube->corners[3] = stored_corner;
}

void turn_left_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[1];
    cube->edges[1] = cube->edges[10];
    cube->edges[10] = cube->edges[3];
    cube->edges[3] = cube->edges[11];
    cube->edges[11] = stored_edge;

    struct corner stored_corner = cube->corners[5];
    cube->corners[5] = cube->corners[3];
    cube->corners[3] = cube->corners[7];
    cube->corners[7] = cube->corners[1];
    cube->corners[1] = stored_corner;
    cube->corners[5].orientation = corner_twist_cw[cube->corners[5].orientation];
    cube->corners[3].orientation = corner_twist_ccw[cube->corners[3].orientation];
    cube->corners[7].orientation = corner_twist_cw[cube->corners[7].orientation];
    cube->corners[1].orientation = corner_twist_ccw[cube->corners[1].orientation];
}

void turn_front_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[4];
    cube->edges[4] = cube->edges[10];
    cube->edges[10] = cube->edges[6];
    cube->edges[6] = cube->edges[8];
    cube->edges[8] = stored_edge;
    cube->edges[4].orientation = edge_flip[cube->edges[4].orientation];
    cube->edges[10].orientation = edge_flip[cube->edges[10].orientation];
    cube->edges[6].orientation = edge_flip[cube->edges[6].orientation];
    cube->edges[8].orientation = edge_flip[cube->edges[8].orientation];

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[5];
    cube->corners[5] = cube->corners[3];
    cube->corners[3] = cube->corners[4];
    cube->corners[4] = stored_corner;
    cube->corners[0].orientation = corner_twist_cw[cube->corners[0].orientation];
    cube->corners[5].orientation = corner_twist_ccw[cube->corners[5].orientation];
    cube->corners[3].orientation = corner_twist_cw[cube->corners[3].orientation];
    cube->corners[4].orientation = corner_twist_ccw[cube->corners[4].orientation];
}

void turn_front_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[4];
    cube->edges[4] = cube->edges[6];
    cube->edges[6] = stored_edge;
    stored_edge = cube->edges[8];
    cube->edges[8] = cube->edges[10];
    cube->edges[10] = stored_edge;

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[3];
    cube->corners[3] = stored_corner;
    stored_corner = cube->corners[5];
    cube->corners[5] = cube->corners[4];
    cube->corners[4] = stored_corner;
}

void turn_front_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[4];
    cube->edges[4] = cube->edges[8];
    cube->edges[8] = cube->edges[6];
    cube->edges[6] = cube->edges[10];
    cube->edges[10] = stored_edge;
    cube->edges[4].orientation = edge_flip[cube->edges[4].orientation];
    cube->edges[8].orientation = edge_flip[cube->edges[8].orientation];
    cube->edges[6].orientation = edge_flip[cube->edges[6].orientation];
    cube->edges[10].orientation = edge_flip[cube->edges[10].orientation];

    struct corner stored_corner = cube->corners[0];
    cube->corners[0] = cube->corners[4];
    cube->corners[4] = cube->corners[3];
    cube->corners[3] = cube->corners[5];
    cube->corners[5] = stored_corner;
    cube->corners[0].orientation = corner_twist_cw[cube->corners[0].orientation];
    cube->corners[4].orientation = corner_twist_ccw[cube->corners[4].orientation];
    cube->corners[3].orientation = corner_twist_cw[cube->corners[3].orientation];
    cube->corners[5].orientation = corner_twist_ccw[cube->corners[5].orientation];
}

void turn_back_cw(struct cube *cube) {
    struct edge stored_edge = cube->edges[5];
    cube->edges[5] = cube->edges[9];
    cube->edges[9] = cube->edges[7];
    cube->edges[7] = cube->edges[11];
    cube->edges[11] = stored_edge;
    cube->edges[5].orientation = edge_flip[cube->edges[5].orientation];
    cube->edges[9].orientation = edge_flip[cube->edges[9].orientation];
    cube->edges[7].orientation = edge_flip[cube->edges[7].orientation];
    cube->edges[11].orientation = edge_flip[cube->edges[11].orientation];

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[2];
    cube->corners[2] = cube->corners[7];
    cube->corners[7] = cube->corners[1];
    cube->corners[1] = stored_corner;
    cube->corners[4].orientation = corner_twist_ccw[cube->corners[4].orientation];
    cube->corners[2].orientation = corner_twist_cw[cube->corners[2].orientation];
    cube->corners[7].orientation = corner_twist_ccw[cube->corners[7].orientation];
    cube->corners[1].orientation = corner_twist_cw[cube->corners[1].orientation];
}

void turn_back_half(struct cube *cube) {
    struct edge stored_edge = cube->edges[5];
    cube->edges[5] = cube->edges[7];
    cube->edges[7] = stored_edge;
    stored_edge = cube->edges[9];
    cube->edges[9] = cube->edges[11];
    cube->edges[11] = stored_edge;

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[7];
    cube->corners[7] = stored_corner;
    stored_corner = cube->corners[1];
    cube->corners[1] = cube->corners[2];
    cube->corners[2] = stored_corner;
}

void turn_back_ccw(struct cube *cube) {
    struct edge stored_edge = cube->edges[5];
    cube->edges[5] = cube->edges[11];
    cube->edges[11] = cube->edges[7];
    cube->edges[7] = cube->edges[9];
    cube->edges[9] = stored_edge;
    cube->edges[5].orientation = edge_flip[cube->edges[5].orientation];
    cube->edges[11].orientation = edge_flip[cube->edges[11].orientation];
    cube->edges[7].orientation = edge_flip[cube->edges[7].orientation];
    cube->edges[9].orientation = edge_flip[cube->edges[9].orientation];

    struct corner stored_corner = cube->corners[4];
    cube->corners[4] = cube->corners[1];
    cube->corners[1] = cube->corners[7];
    cube->corners[7] = cube->corners[2];
    cube->corners[2] = stored_corner;
    cube->corners[4].orientation = corner_twist_ccw[cube->corners[4].orientation];
    cube->corners[1].orientation = corner_twist_cw[cube->corners[1].orientation];
    cube->corners[7].orientation = corner_twist_ccw[cube->corners[7].orientation];
    cube->corners[2].orientation = corner_twist_cw[cube->corners[2].orientation];
}
