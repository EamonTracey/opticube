#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "state.h"
#include "queue.h"

int main() {
    struct cube *cube_solved = init_cube_solved();
    struct queue *queue = init_queue();
    struct value value = { cube_solved, 0, 255, 0 };

    uint8_t *depth_table = (uint8_t *)malloc(88179840 * sizeof(uint8_t));
    memset(depth_table, 255, 88179840 * sizeof(uint8_t));

    int count = 0;
    enqueue(queue, value);
    while (queue->head != NULL) {
        struct value value = dequeue(queue);
        
        if (depth_table[value.state] != 255) {
            free(value.cube);
            continue;
        }
        depth_table[value.state] = value.depth;
        count += 1;

        if (count % 881798 == 0)
            printf("count: %d (%d)\n", count, value.depth);

        struct cube *adj_cube;
        uint32_t adj_state;
        struct value adj_value;
        uint8_t adj_depth = value.depth + 1;

        if (value.last > 2) {
            adj_cube = init_cube_copy(value.cube);
            turn_up_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 0, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_up_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 1, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_up_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 2, adj_depth };
                enqueue(queue, adj_value);
            }

        }

        if (value.last < 3 || value.last > 5) {
            adj_cube = init_cube_copy(value.cube);
            turn_down_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 3, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_down_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 4, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_down_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 5, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        if (value.last < 6 || value.last > 8) {
            adj_cube = init_cube_copy(value.cube);
            turn_right_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 6, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_right_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 7, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_right_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 8, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        if (value.last > 9 || value.last < 11) {
            adj_cube = init_cube_copy(value.cube);
            turn_left_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 9, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_left_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 10, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_left_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 11, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        if (value.last < 12 || value.last > 14) {
            adj_cube = init_cube_copy(value.cube);
            turn_front_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 12, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_front_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 13, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_front_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 14, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        if (value.last > 15) {
            adj_cube = init_cube_copy(value.cube);
            turn_back_cw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 15, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_back_ccw(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 16, adj_depth };
                enqueue(queue, adj_value);
            }

            adj_cube = init_cube_copy(value.cube);
            turn_back_half(adj_cube);
            adj_state = corners_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                adj_value = (struct value){ adj_cube, adj_state, 17, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        free(value.cube);
    }
    
    free(queue);

    printf("final count: %d\n", count);

    return 0;
}
