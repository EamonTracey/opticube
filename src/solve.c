#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "solve.h"

void solve(struct cube *cube, int *n_turns) {
    struct stack_node stack[360];
    struct stack_node *stack_pointer = stack;

    for (int i = 0; i < 21; ++i) {
        struct cube *start = init_cube_copy(cube);
        *(stack_pointer++) = (struct stack_node){ start, NULL, 255, 0 };
        while (stack != stack_pointer) {
            struct stack_node node = *(--stack_pointer);
            
            if (node.depth == i) {
                if (cubes_equal(*node.cube, SOLVED_CUBE)) {
                    fprintf(stdout, "found solution at depth %d\n", i);
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
