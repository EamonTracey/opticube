#include <stdint.h>
#include <stdlib.h>

#include "cube.h"
#include "stack.h"
#include "state.h"
#include "table.h"
#include "twop.h"

#define GODS_ONE 12
#define GODS_TWO 18

const char *EO_EQUATOR_COMBINATION_DT_PATH = "depths/eo_equator_combination.dt";
const char *CO_EQUATOR_COMBINATION_DT_PATH = "depths/co_equator_combination.dt";
const char *EP_TETRADS_COMBINATION_DT_PATH = "depths/ep_tetrads_combination.dt";
const char *CP_SLICES_COMBINATION_DT_PATH = "depths/cp_slices_combination.dt";
const uint32_t EO_EQUATOR_COMBINATION_DT_SIZE = 1013760;
const uint32_t CO_EQUATOR_COMBINATION_DT_SIZE = 1082565;
const uint32_t EP_TETRADS_COMBINATION_DT_SIZE = 2822400;
const uint32_t CP_SLICES_COMBINATION_DT_SIZE = 2822400;

uint8_t *eo_equator_combination_dt = NULL;
uint8_t *co_equator_combination_dt = NULL;
uint8_t *ep_tetrads_combination_dt = NULL;
uint8_t *cp_slices_combination_dt = NULL;

uint8_t phase_one_heuristic(const struct cube *cube) {
    uint8_t max_depth;

    uint8_t eo_equator_combination_depth = eo_equator_combination_dt[eo_equator_combination_state(cube)];
    max_depth = eo_equator_combination_depth;

    uint8_t co_equator_combination_depth = co_equator_combination_dt[co_equator_combination_state(cube)];
    if (co_equator_combination_depth > max_depth)
        max_depth = co_equator_combination_depth;

    return max_depth;
}

uint8_t phase_one_complete(const struct cube *cube) {
    for (uint8_t i = 0; i < 11; ++i)
        if (cube->edges[i].orientation != 0)
            return 0;

    for (uint8_t i = 8; i < 12; ++i)
        if (cube->edges[i].cubelet < 8)
            return 0;

    return 1;
}

uint8_t phase_two_heuristic(const struct cube *cube) {
    uint8_t max_depth;

    uint8_t ep_tetrads_combination_depth = ep_tetrads_combination_dt[ep_tetrads_combination_state(cube)];
    max_depth = ep_tetrads_combination_depth;

    uint8_t cp_slices_combination_depth = cp_slices_combination_dt[cp_slices_combination_state(cube)];
    if (cp_slices_combination_depth > max_depth)
        max_depth = cp_slices_combination_depth;

    return max_depth;
}

uint8_t *twop_solve(const struct cube *cube, uint16_t *n_turns) {
    static uint8_t tables_loaded = 0;

    if (cube == NULL) {
        if (tables_loaded) {
            free(eo_equator_combination_dt);
            free(co_equator_combination_dt);
            free(ep_tetrads_combination_dt);
            free(cp_slices_combination_dt);
            tables_loaded = 0;
        }
        return NULL;
    }

    if (!tables_loaded) {
        eo_equator_combination_dt = read_depth_table(EO_EQUATOR_COMBINATION_DT_PATH, EO_EQUATOR_COMBINATION_DT_SIZE);
        co_equator_combination_dt = read_depth_table(CO_EQUATOR_COMBINATION_DT_PATH, CO_EQUATOR_COMBINATION_DT_SIZE);
        ep_tetrads_combination_dt = read_depth_table(EP_TETRADS_COMBINATION_DT_PATH, EP_TETRADS_COMBINATION_DT_SIZE);
        cp_slices_combination_dt = read_depth_table(CP_SLICES_COMBINATION_DT_PATH, CP_SLICES_COMBINATION_DT_SIZE);
        tables_loaded = 1;
    }

    struct stack *stack = init_stack(GODS_TWO * 18);

    uint8_t one_path[GODS_ONE + 1];
    uint8_t one_depth;
    for (one_depth = phase_one_heuristic(cube); one_depth <= GODS_ONE; ++one_depth) {
        push(stack, *cube, 255, 0);
        while (stack->index != 0) {
            struct stack_node node = pop(stack);
            one_path[node.depth] = node.turn;

            if (node.depth + phase_one_heuristic(&node.cube) > one_depth)
                continue;
            
            if (node.depth == one_depth) {
                if (phase_one_complete(&node.cube))
                    goto phase_two;
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

phase_two:
    stack->index = 0;
    struct cube *two_cube = init_cube_copy(cube);
    for (int i = 1; i <= one_depth; ++i)
        turn(two_cube, one_path[i]);

    uint8_t two_path[GODS_TWO + 1];
    uint8_t two_depth;
    for (two_depth = phase_two_heuristic(two_cube); two_depth <= GODS_TWO; ++two_depth) {
        push(stack, *two_cube, 255, 0);
        while (stack->index != 0) {
            struct stack_node node = pop(stack);
            two_path[node.depth] = node.turn;

            if (node.depth + phase_two_heuristic(&node.cube) > two_depth)
                continue;

            if (node.depth == two_depth) {
                if (cubes_equal(&node.cube, &SOLVED_CUBE))
                    goto solved;
            } else {
                uint8_t layer = node.turn / 3;
                for (uint8_t adj_turn = 17; adj_turn < 18; --adj_turn) {
                    if (adj_turn == 6 || adj_turn == 8 || adj_turn == 9 || adj_turn == 11 || adj_turn == 12 || adj_turn == 14 || adj_turn == 15 || adj_turn == 17)
                        continue;

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
    free_stack(stack);

    *n_turns = one_depth + two_depth;
    uint8_t *path = (uint8_t *)malloc(one_depth + two_depth);
    for (uint8_t i = 1; i <= one_depth; ++i)
        path[i - 1] = one_path[i];
    for (uint8_t i = 1; i <= two_depth; ++i)
        path[one_depth + i - 1] = two_path[i];

    return path;
}
