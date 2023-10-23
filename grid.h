#ifndef GRID_H
#define GRID_H

#include <stddef.h>

#define X 0
#define O 1
#define EMPTY 2
#define OPPOSITE(turn) (turn == X) ? O : X
#define STRINGIFY(block) (block == X) ? 'X' : (block == O) ? 'O' : ' '

typedef unsigned short* Grid;

Grid grid_init();
Grid grid_copy(Grid);
void grid_set(Grid grid, unsigned short x, unsigned short y, unsigned short choice);
short grid_get_winner(Grid grid);


#endif

