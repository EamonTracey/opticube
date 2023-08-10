#ifndef SOLVE_H
#define SOLVE_H

#include <stdint.h>

#include "cube.h"

struct stack_node {
    struct cube *cube;
    uint8_t turn;
    uint8_t depth;
};

static const char *CORNERS_DT_PATH = "depths/corners.dt";
static const char *SIX_EDGES_A_DT_PATH = "depths/six_edges_a.dt";
static const char *SIX_EDGES_B_DT_PATH = "depths/six_edges_b.dt";
static const uint32_t CORNERS_DT_SIZE = 88179840;
static const uint32_t SIX_EDGES_A_DT_SIZE = 42577920;
static const uint32_t SIX_EDGES_B_DT_SIZE = 42577920;

static uint8_t tables_loaded = 0;
static uint8_t *corners_dt = NULL;
static uint8_t *six_edges_a_dt = NULL;
static uint8_t *six_edges_b_dt = NULL;

void load_depth_tables();

uint8_t heuristic(const struct cube *);
uint8_t *solve(const struct cube *, uint16_t *);

#endif
