#include <stdlib.h>
#include "grid.h"

Grid grid_init()
{
    unsigned short* grid = (unsigned short*) malloc(9 * sizeof(unsigned short));
    for (int i = 0; i < 9; i ++)
        grid[i] = 2;

    return grid;
}

