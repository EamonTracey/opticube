#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "algorithm.h"
#include "cube.h"
#include "korf.h"
#include "stack.h"
#include "state.h"
#include "table.h"

#define GODS_NUMBER 20

const char *DEPTHS_PATH = "depths";
const char *CORNERS_DT_PATH = "depths/corners.dt";
const char *SIX_EDGES_A_DT_PATH = "depths/six_edges_a.dt";
const char *SIX_EDGES_B_DT_PATH = "depths/six_edges_b.dt";
const uint32_t CORNERS_DT_SIZE = 88179840;
const uint32_t SIX_EDGES_A_DT_SIZE = 42577920;
const uint32_t SIX_EDGES_B_DT_SIZE = 42577920;

uint8_t *corners_dt = NULL;
uint8_t *six_edges_a_dt = NULL;
uint8_t *six_edges_b_dt = NULL;

uint8_t korf_heuristic(const struct cube *cube) {
    uint8_t max_depth;

    uint8_t corners_depth = corners_dt[corners_state(cube)];
    max_depth = corners_depth;

    uint8_t six_edges_a_depth = six_edges_a_dt[six_edges_a_state(cube)];
    if (six_edges_a_depth > max_depth)
        max_depth = six_edges_a_depth;

    uint8_t six_edges_b_depth = six_edges_b_dt[six_edges_b_state(cube)];
    if (six_edges_b_depth > max_depth)
        max_depth = six_edges_b_depth;

    return max_depth;
}

uint8_t *korf_solve(const struct cube *cube, uint16_t *n_turns) {
    static uint8_t tables_loaded = 0;

    if (cube == NULL) {
        if (tables_loaded) {
            free(corners_dt);
            free(six_edges_a_dt);
            free(six_edges_b_dt);
            tables_loaded = 0;
        }
        return NULL;
    }

    if (!tables_loaded) {
        corners_dt = read_depth_table(CORNERS_DT_PATH, CORNERS_DT_SIZE);
        six_edges_a_dt = read_depth_table(SIX_EDGES_A_DT_PATH, SIX_EDGES_A_DT_SIZE);
        six_edges_b_dt = read_depth_table(SIX_EDGES_B_DT_PATH, SIX_EDGES_B_DT_SIZE);
        tables_loaded = 1;
    }

    struct stack *stack = init_stack(GODS_NUMBER * 18);
    uint8_t *path = (uint8_t *)malloc((GODS_NUMBER + 1) * sizeof(uint8_t));

    uint8_t depth;
    for (depth = korf_heuristic(cube); depth <= GODS_NUMBER; ++depth) {
        push(stack, *cube, 255, 0);
        while (stack->index != 0) {
            struct stack_node node = pop(stack);
            path[node.depth] = node.turn;

            if (node.depth + korf_heuristic(&node.cube) > depth)
                continue;
            
            if (node.depth == depth) {
                if (cubes_equal(&node.cube, &SOLVED_CUBE))
                    goto solved;
            } else {
                uint8_t layer = node.turn / 3;
                for (uint8_t adj_turn = 17; adj_turn < 18; --adj_turn) {
                    uint8_t adj_layer = adj_turn / 3;
                    if ((adj_layer == layer) || (layer == 1 && adj_layer == 0) || (layer == 3 && adj_layer == 2) || (layer == 5 && adj_layer == 4))
                        continue;

                    struct cube adj_cube = node.cube;
                    turn(&adj_cube, adj_turn);
                    push(stack, adj_cube, adj_turn, node.depth + 1);
                }
            }
        }
    }

solved:
    *n_turns = depth;
    for (uint8_t i = 1; i <= *n_turns; ++i) {
        path[i - 1] = path[i];
    }

    return path;
}
