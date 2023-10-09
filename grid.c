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

    grid[x + y * 3] = choice; 
}

short grid_get_winner(Grid grid)
{
    // first row
    if (grid[0] != 2 && grid[0] == grid[1] && grid[1] == grid[2]) 
        return grid[0];

    // second row
    else if (grid[3] != 2 && grid[3] == grid[4] && grid[4] == grid[5])
        return grid[3];

    // thrid row
    else if (grid[6] != 2 && grid[6] == grid[7] && grid[7] == grid[8])
        return grid[6];

    // first column
    else if (grid[0] != 2 && grid[0] == grid[3] && grid[3] == grid[6])
        return grid[0];

    // second column
    else if (grid[1] != 2 && grid[1] == grid[4] && grid[4] == grid[7])
        return grid[1];

    // third column
    else if (grid[2] != 2 && grid[2] == grid[5] && grid[5] == grid[8])
        return grid[2];

    // Northwest-Southeast diagonal
    else if (grid[0] != 2 && grid[0] == grid[4] && grid[4] == grid[8])
       return grid[0];

    // Northeast-Southwest diagonal
    else if (grid[2] != 2 && grid[2] == grid[4] && grid[4] == grid[6])
       return grid[2];

    else 
       return 2; 
}
