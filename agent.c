#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
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

size_t solve_by_breadth_first(Grid grid, unsigned short agent_turn)
{
    Grid local_grid = grid_copy(grid);

    size_t agent_square = 0;
    bool solution_found = false;

    for (; agent_square < 9 && !solution_found; agent_square ++)
    {
        if (local_grid[agent_square] != EMPTY)
            continue;

        Grid tree_root = grid_copy(local_grid);
        GQueue *queue = g_queue_new();

        tree_root[agent_square] = agent_turn;
        g_queue_push_tail(queue, tree_root);

        while (!g_queue_is_empty(queue))
        {
            Grid current_node = g_queue_pop_head(queue);

            if (grid_get_winner(current_node) == agent_turn)
            {
                solution_found = true;
                break;
            }

            for (size_t enemy_response = 0; enemy_response < 9; enemy_response ++)            
            {
                if (current_node[enemy_response] != EMPTY)
                    continue;

                Grid node_after_enemy_response = grid_copy(current_node);
                node_after_enemy_response[enemy_response] = OPPOSITE(agent_turn);

                for (size_t future_move = 0; future_move < 9; future_move ++)
                {
                    if (node_after_enemy_response[future_move] != EMPTY)
                        continue;

                    Grid node_of_future_move = grid_copy(node_after_enemy_response);
                    node_of_future_move[future_move] = agent_turn;

                    g_queue_push_tail(queue, node_of_future_move);

                    TraceLog(LOG_INFO, " | %c | %c | %c | ", STRINGIFY(node_of_future_move[0]), STRINGIFY(node_of_future_move[1]), STRINGIFY(node_of_future_move[2]));
                    TraceLog(LOG_INFO, " | %c | %c | %c | ", STRINGIFY(node_of_future_move[3]), STRINGIFY(node_of_future_move[4]), STRINGIFY(node_of_future_move[5]));
                    TraceLog(LOG_INFO, " | %c | %c | %c | \n", STRINGIFY(node_of_future_move[6]), STRINGIFY(node_of_future_move[7]), STRINGIFY(node_of_future_move[8]));

                }

            }
        }

        free(tree_root);
        
        g_queue_free_full(queue, free);
    }
    
    free(local_grid);
    return agent_square;
}
