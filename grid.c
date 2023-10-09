#include <stdlib.h>
#include "grid.h"

Grid grid_init()
{
    unsigned short* grid = (unsigned short*) malloc(9 * sizeof(unsigned short));
    for (int i = 0; i < 9; i ++)
        grid[i] = 2;

    return grid;
}

void grid_set(Grid grid, unsigned short x, unsigned short y, unsigned short choice)
{
    if (x < 0 || x > 8 || y < 0 || y > 8)
        return;

    grid[y + 3 * x] = choice; 
}
