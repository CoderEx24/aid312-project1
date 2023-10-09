#ifndef GRID_H
#define GRID_H

#define X 0
#define O 1

typedef unsigned short* Grid;

Grid grid_init();
void grid_set(Grid grid, unsigned short x, unsigned short y, unsigned short choice);
short grid_get_winner(Grid grid);


#endif

