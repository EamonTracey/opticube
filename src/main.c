#include <stdlib.h>

#include "state.h"
#include "table.h"

int main() {
    uint8_t *corners_dt = generate_depth_table(&corners_state, 88189740);
    write_depth_table("corners.dt", corners_dt, 88189740);
    free(corners_dt);

    uint8_t *first_six_edges_dt = generate_depth_table(&first_six_edges_state, 42577920);
    write_depth_table("first_six_edges.dt", first_six_edges_dt, 42577920);
    free(first_six_edges_dt);

    uint8_t *second_six_edges_dt = generate_depth_table(&second_six_edges_state, 42577920);
    write_depth_table("second_six_edges.dt", second_six_edges_dt, 42577920);
    free(second_six_edges_dt);

    return 0;
}
