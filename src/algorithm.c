#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "algorithm.h"

uint8_t str_to_turn(const char *str) {
    uint8_t turn;

    switch (*str) {
    case 'U':
        turn = 0;
        break;
    case 'D':
        turn = 3;
        break;
    case 'R':
        turn = 6;
        break;
    case 'L':
        turn = 9;
        break;
    case 'F':
        turn = 12;
        break;
    case 'B':
        turn = 15;
        break;
    default:
        return 255;
    }

    switch (*(str + 1)) {
    case ' ':
    case '\0':
        return turn;
    case '2':
        return turn + 1;
    case '\'':
        return turn + 2;
    default:
        return 255;
    }
}

uint8_t *str_to_algorithm(const char *str, uint16_t *n_turns) {
    uint16_t turns_allocated = 20;
    uint8_t *turns = (uint8_t *)malloc(turns_allocated * sizeof(uint8_t));
    *n_turns = 0;

    uint8_t turn;
    while (1) {
        turn = str_to_turn(str);
        if (turn == 255) {
          free(turns);
          return NULL;
        }

        if (turns_allocated == *n_turns) {
            turns_allocated += 20;
            turns = (uint8_t *)realloc(turns, turns_allocated * sizeof(uint8_t));
        }
        turns[(*n_turns)++] = turn;

        if (turn % 3 == 0) {
            if (*(str + 1) == '\0')
                break;
            str += 2;
        } else {
            if (*(str + 2) == '\0')
                break;
            str += 3;
        }
    }

    return turns;
}

char *turn_to_str(uint8_t turn) {
    char *str = (char *)malloc(3 * sizeof(char));

    switch (turn / 3) {
    case 0:
        *str = 'U';
        break;
    case 1:
        *str = 'D';
        break;
    case 2:
        *str = 'R';
        break;
    case 3:
        *str = 'L';
        break;
    case 4:
        *str = 'F';
        break;
    case 5:
        *str = 'B';
        break;
    default:
        return NULL;
    }

    switch (turn % 3) {
    case 0:
        *(str + 1) = '\0';
        break;
    case 1:
        *(str + 1) = '2';
        *(str + 2) = '\0';
        break;
    case 2:
        *(str + 1) = '\'';
        *(str + 2) = '\0';
        break;
    }

    return str;
}

char *algorithm_to_str(const uint8_t *turns, uint16_t n_turns) {
    char *str = malloc(3 * n_turns * sizeof(char));

    char *turn;
    for (int i = 0; i < n_turns; ++i) {
        turn = turn_to_str(turns[i]);
        if (turn == NULL) {
            free(str);
            return NULL;
        }
        if (i > 0)
            strcat(str, " ");
        strcat(str, turn);
        free(turn);
    }

    return str;
}
