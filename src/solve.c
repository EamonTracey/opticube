#include <stdio.h>
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
    fprintf(stdout, "tables loaded ... solving");

    struct stack_node stack[360];
    struct stack_node *stack_pointer = stack;

    uint32_t traversed = 0;
    uint32_t pruned = 0;
    uint32_t searched = 0;

    for (int i = 0; i <= GODS_NUMBER; ++i) {
        fprintf(stdout, "searching depth %d\n", i);

        struct cube *start = init_cube_copy(cube);
        *(stack_pointer++) = (struct stack_node){ start, NULL, 255, 0 };
        while (stack != stack_pointer) {
            struct stack_node node = *(--stack_pointer);
            ++traversed;

            if (node.depth + heuristic(node.cube) > i) {
                free(node.cube);
                ++pruned;
                continue;
            }
            
            ++searched;

            if (node.depth == i) {
                if (cubes_equal(*node.cube, SOLVED_CUBE)) {
                    fprintf(stdout, "found solution at depth %d\n", i);
                    free(node.cube);

                    fprintf(stdout, "traversed %u nodes\n", traversed);
                    fprintf(stdout, "searched %u nodes\n", searched);
                    fprintf(stdout, "pruned %u nodes\n", pruned);

                    return;
                }
            } else {
                uint8_t layer = node.turn / 3;
                for (int j = 0; j < 18; ++j) {
                    if (layer == j / 3)
                        continue;

                    struct cube *adj_cube = init_cube_copy(node.cube);
                    turn(adj_cube, j);
                    *(stack_pointer++) = (struct stack_node){ adj_cube, NULL, j, node.depth + 1 };
                }
            }

            free(node.cube);
        }
    }
}
