#include <stdlib.h>
#include <string.h>

#include "algorithm.h"

uint8_t str_to_turn(char *str) {
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
    case '\0':
    case ' ':
        return turn;
    case '2':
        return turn + 1;
    case '\'':
        return turn + 2;
    default:
        return 255;
    }
}

struct algorithm str_to_algorithm(char *str) {
    struct algorithm algorithm = (struct algorithm){ (uint8_t *)malloc(20 * sizeof(uint8_t)), 0 };

    uint8_t turn;
    while (1) {
        turn = str_to_turn(str);
        if (turn == 255) {
          free(algorithm.turns);
          algorithm.turns = NULL;
          return algorithm;
        }

        algorithm.turns[algorithm.n_turns++] = turn;

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

    return algorithm;
}

char *turn_to_str(uint8_t turn) {
    return "";
}

char *algorithm_to_str(struct algorithm algorithm) {
    return "";
}
