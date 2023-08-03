#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "queue.h"
#include "state.h"
#include "table.h"

uint8_t *generate_depth_table(uint32_t (*compute_state)(struct cube *), uint32_t size) {
    struct cube *cube_solved = init_cube_solved();
    struct queue *queue = init_queue();
    struct queue_value value = (struct queue_value){ cube_solved, (*compute_state)(cube_solved), 255, 0 };

    uint8_t *depth_table = (uint8_t *)malloc(size * sizeof(uint8_t));
    memset(depth_table, 255, size * sizeof(uint8_t));

    enqueue(queue, value);
    while (queue->head != NULL) {
        struct queue_value value = dequeue(queue);

        if (depth_table[value.state] != 255) {
            free(value.cube);
            continue;
        }
        depth_table[value.state] = value.depth;

        uint8_t layer = value.last / 3;
        uint8_t adj_depth = value.depth + 1;

        for (int i = 0; i < 18; ++i) {
            if (i / 3 == layer)
                continue;

            struct cube *adj_cube = init_cube_copy(value.cube);
            turn(adj_cube, i);
            uint32_t adj_state = compute_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                struct queue_value adj_value = (struct queue_value){ adj_cube, adj_state, i, adj_depth };
                enqueue(queue, adj_value);
            }
        }

        free(value.cube);
    }

    free(queue);

    return depth_table;
}

void write_depth_table(char *filename, uint8_t *table, uint32_t size) {
    FILE *fp = fopen(filename, "w");

    uint8_t buffer;
    for (uint32_t i = 0; i < size; i += 2) {
        buffer = (table[i] << 4) + table[i + 1];
        fwrite(&buffer, sizeof(uint8_t), 1, fp);
    }

    fclose(fp);
}

void load_depth_table(char *filename, uint32_t size) {
    FILE *fp = fopen(filename, "r");

    uint8_t *table = malloc(size * sizeof(uint8_t));
    uint8_t buffer;
    for (uint32_t i = 0; i < size; ++i) {
        fread(&buffer, sizeof(uint8_t), 1, fp);
        table[i * 2] = buffer >> 4;
        table[i * 2 + 1] = buffer & 15;
    }
}
