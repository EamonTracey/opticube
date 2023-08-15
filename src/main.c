#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"
#include "cube.h"
#include "korf.h"
#include "state.h"
#include "table.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "ERROR: Must input a scramble.\n");
        return EXIT_FAILURE;
    }

    if (argc > 2) {
        fprintf(stderr, "ERROR: Too many input arguments.\n");
        return EXIT_FAILURE;
    }

    uint8_t *scramble;
    uint16_t n_turns;
    if ((scramble = str_to_algorithm(argv[1], &n_turns)) == NULL) {
        fprintf(stderr, "ERROR: Unable to parse scramble.\n");
        return EXIT_FAILURE;
    }

    struct cube *cube = init_cube_solved();
    for (uint16_t i = 0; i < n_turns; ++i)
        turn(cube, scramble[i]);
    free(scramble);

    uint8_t *solution = korf_solve(cube, &n_turns);
    char *solution_str = algorithm_to_str(solution, n_turns);
    fprintf(stdout, "Solution in %d turns.\n", n_turns);
    fprintf(stdout, "Solution: %s\n", solution_str);

    free(cube);
    free(solution);
    free(solution_str);
    korf_solve(NULL, NULL);

    return EXIT_SUCCESS;
}
