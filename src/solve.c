#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "solve.h"
#include "state.h"
#include "table.h"

#define GODS_NUMBER 20

static uint8_t TABLES_LOADED = 0;
static uint8_t *corners_dt = NULL;
static uint8_t *first_six_edges_dt = NULL;
static uint8_t *second_six_edges_dt = NULL;

void load_depth_tables() {
    corners_dt = read_depth_table("corners.dt", 88179840);
    first_six_edges_dt = read_depth_table("first_six_edges.dt", 42577920);
    second_six_edges_dt = read_depth_table("second_six_edges.dt", 42577920);
    TABLES_LOADED = 1;
}

uint8_t heuristic(struct cube *cube) {
    uint8_t max_depth;

    uint8_t corners_depth = corners_dt[corners_state(cube)];
    max_depth = corners_depth;

    uint8_t first_six_edges_depth = first_six_edges_dt[first_six_edges_state(cube)];
    if (first_six_edges_depth > max_depth)
        max_depth = first_six_edges_depth;

    uint8_t second_six_edges_depth = second_six_edges_dt[second_six_edges_state(cube)];
    if (second_six_edges_depth > max_depth)
        max_depth = second_six_edges_depth;

    return max_depth;
}

void solve(struct cube *cube, int *n_turns) {
    if (!TABLES_LOADED)
        load_depth_tables();

    struct stack_node stack[360];
    uint8_t stack_index = 0;

    for (int depth = 0; depth <= GODS_NUMBER; ++depth) {
        struct cube *start = init_cube_copy(cube);
        stack[stack_index++] = (struct stack_node){ start, NULL, 255, 0 };
        while (stack_index != 0) {
            struct stack_node node = stack[--stack_index];

            if (node.depth + heuristic(node.cube) > depth) {
                free(node.cube);
                continue;
            }
            
            if (node.depth == depth) {
                if (cubes_equal(*node.cube, SOLVED_CUBE)) {
                    free(node.cube);
                    return;
                }
            } else {
                uint8_t layer = node.turn / 3;
                for (int j = 0; j < 18; ++j) {
                    if (layer == j / 3)
                        continue;

                    struct cube *adj_cube = init_cube_copy(node.cube);
                    turn(adj_cube, j);
                    stack[stack_index++] = (struct stack_node){ adj_cube, NULL, j, node.depth + 1 };
                }
            }

            free(node.cube);
        }
    }
}
