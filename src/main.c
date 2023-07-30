#include <stdlib.h>

#include "state.h"
#include "table.h"

int main() {
    uint8_t *corners_depth_table = generate_depth_table(&corners_state, 88189740);
    write_depth_table("corners.dt", corners_depth_table, 88189740);
    free(corners_depth_table);

    return 0;
}
