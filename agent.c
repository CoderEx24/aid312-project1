#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include "agent.h"
#include "raylib.h"

bool search_by_depth(Grid grid, unsigned short agent_turn)
{
    TraceLog(LOG_INFO, " | %c | %c | %c | ", STRINGIFY(grid[0]), STRINGIFY(grid[1]), STRINGIFY(grid[2]));
    TraceLog(LOG_INFO, " | %c | %c | %c | ", STRINGIFY(grid[3]), STRINGIFY(grid[4]), STRINGIFY(grid[5]));
    TraceLog(LOG_INFO, " | %c | %c | %c | \n", STRINGIFY(grid[6]), STRINGIFY(grid[7]), STRINGIFY(grid[8]));
    if (grid_get_winner(grid) == agent_turn)
        return true;

    for (size_t enemy_square = 0; enemy_square < 9; enemy_square ++)
    {
        if (grid[enemy_square] != EMPTY)
            continue;

        grid[enemy_square] = OPPOSITE(agent_turn);

        for (size_t agent_square = 0; agent_square < 9; agent_square ++)
        {
            if (grid[agent_square] != EMPTY)
                continue;

            grid[agent_square] = agent_turn;


            if (search_by_depth(grid, agent_turn))
                return true;

            grid[agent_square] = EMPTY;
        }
        
        grid[enemy_square] = EMPTY;
    }

    return false;
}

size_t solve_by_depth_first(Grid grid, unsigned short agent_turn)
{
    Grid local_grid = grid_copy(grid);

    size_t agent_square = 0;
    
    for (; agent_square < 9; agent_square ++)
    {
        if (local_grid[agent_square] != EMPTY)
            continue;

        local_grid[agent_square] = agent_turn;

        if (search_by_depth(local_grid, agent_turn))
        {
            free(local_grid);
            return agent_square;
        }
        
        local_grid[agent_square] = EMPTY;
    }

    free(local_grid);
    return agent_square;
    
}
