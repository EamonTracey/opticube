#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cube.h"
#include "solve.h"
#include "state.h"
#include "table.h"

#define GODS_NUMBER 20

void load_depth_tables() {
    DIR *depths_dir;
    if ((depths_dir = opendir(DEPTHS_PATH)) == NULL) {
        mkdir(DEPTHS_PATH, S_IRWXU | S_IRWXG | S_IRWXO);
        write_depth_table(
            CORNERS_DT_PATH,
            generate_depth_table(corners_state, CORNERS_DT_SIZE),
            CORNERS_DT_SIZE
        );
        write_depth_table(
            SIX_EDGES_A_DT_PATH,
            generate_depth_table(six_edges_a_state, SIX_EDGES_A_DT_SIZE),
            SIX_EDGES_A_DT_SIZE
        );
        write_depth_table(
            SIX_EDGES_B_DT_PATH,
            generate_depth_table(six_edges_b_state, SIX_EDGES_B_DT_SIZE),
            SIX_EDGES_B_DT_SIZE
        );
    } else
        closedir(depths_dir);

    corners_dt = read_depth_table(CORNERS_DT_PATH, CORNERS_DT_SIZE);
    six_edges_a_dt = read_depth_table(SIX_EDGES_A_DT_PATH, SIX_EDGES_A_DT_SIZE);
    six_edges_b_dt = read_depth_table(SIX_EDGES_B_DT_PATH, SIX_EDGES_B_DT_SIZE);
    tables_loaded = 1;
}

uint8_t heuristic(const struct cube *cube) {
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

uint8_t *solve(const struct cube *cube, uint16_t *n_turns) {
    if (cube == NULL) {
        if (tables_loaded) {
            free(corners_dt);
            free(six_edges_a_dt);
            free(six_edges_b_dt);
        }
        return NULL;
    }

    if (!tables_loaded)
        load_depth_tables();

    struct stack_node stack[GODS_NUMBER * 18];
    uint16_t stack_index = 0;
    uint8_t *path = (uint8_t *)malloc((GODS_NUMBER + 1) * sizeof(uint8_t));

    uint8_t depth;
    for (depth = heuristic(cube); depth <= GODS_NUMBER; ++depth) {
        stack[stack_index++] = (struct stack_node){ *cube, 255, 0 };
        while (stack_index != 0) {
            struct stack_node node = stack[--stack_index];
            path[node.depth] = node.turn;

            if (node.depth + heuristic(&node.cube) > depth)
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

                    stack[stack_index] = (struct stack_node){node.cube, adj_turn, node.depth + 1};
                    turn(&stack[stack_index].cube, adj_turn);
                    ++stack_index;
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
