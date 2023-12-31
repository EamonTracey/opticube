#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "queue.h"
#include "state.h"
#include "table.h"

uint8_t *generate_depth_table(uint32_t (*compute_state)(const struct cube *), uint32_t size, uint8_t *turns, uint8_t n_turns) {
    struct cube *cube_solved = init_cube_solved();
    struct queue *queue = init_queue();
    struct queue_value value = (struct queue_value){cube_solved, (*compute_state)(cube_solved), 255, 0};

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

        uint8_t layer = value.turn / 3;
        for (uint8_t i = n_turns - 1; i < 18; --i) {
            uint8_t adj_turn = turns[i];
            uint8_t adj_layer = adj_turn / 3;
            if ((adj_layer == layer) || (layer == 1 && adj_layer == 0) || (layer == 3 && adj_layer == 2) || (layer == 5 && adj_layer == 4))
                continue;

            struct cube *adj_cube = init_cube_copy(value.cube);
            turn(adj_cube, adj_turn);
            uint32_t adj_state = compute_state(adj_cube);
            if (depth_table[adj_state] != 255) {
                free(adj_cube);
            } else {
                struct queue_value adj_value = (struct queue_value){adj_cube, adj_state, adj_turn, value.depth + 1};
                enqueue(queue, adj_value);
            }
        }

        free(value.cube);
    }

    free(queue);

    return depth_table;
}

void write_depth_table(const char *filename, const uint8_t *table, uint32_t size) {
    FILE *fp = fopen(filename, "w");

    uint8_t buffer;
    for (uint32_t i = 0; i < size; i += 2) {
        buffer = (table[i] << 4) + table[i + 1];
        fwrite(&buffer, sizeof(uint8_t), 1, fp);
    }

    fclose(fp);
}

uint8_t *read_depth_table(const char *filename, uint32_t size) {
    FILE *fp = fopen(filename, "r");

    uint8_t *table = malloc(size * sizeof(uint8_t));
    uint8_t buffer;
    for (uint32_t i = 0; i < size / 2; ++i) {
        fread(&buffer, sizeof(uint8_t), 1, fp);
        table[i * 2] = buffer >> 4;
        table[i * 2 + 1] = buffer & 15;
    }

    fclose(fp);

    return table;
}
