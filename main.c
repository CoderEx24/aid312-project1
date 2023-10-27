#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "grid.h"
#include "agent.h"

int main()
{
    Grid grid = grid_init();
    short turn = X;
    short winner = EMPTY;

    InitWindow(600, 600, "TicTacToe");
    while (!WindowShouldClose())
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = GetMouseX() / 200;
            int y = GetMouseY() / 200;

            if (grid[x + y * 3] == EMPTY)
            {
                grid[x + y * 3] = X;
                winner = grid_get_winner(grid);
                
                if (winner == EMPTY)
                {
                    size_t agent_solution = solve_by_depth_first(grid, O);

                    TraceLog(LOG_INFO, "Agent Solution = %zu", agent_solution);

                    if (agent_solution != 9)
                        grid[agent_solution] = O;

                    else
                    {
                        TraceLog(LOG_INFO, "Deadlocked, choicing randomly");
                        size_t random_position = rand() % 9;

                        while (grid[random_position] != EMPTY)
                            random_position = rand() % 9;

                        grid[random_position] = O;
                    }
                }
                
                winner = grid_get_winner(grid);
            }
        }

        ClearBackground(WHITE);
        BeginDrawing();

        if (winner == EMPTY)
        {
            DrawLine(200, 0, 200, 600, BLACK);
            DrawLine(400, 0, 400, 600, BLACK);
            DrawLine(0, 200, 600, 200, BLACK);
            DrawLine(0, 400, 600, 400, BLACK);

            for (int x = 0; x < 3; x ++)
                for (int y = 0; y < 3; y ++)
                {
                    char *text[] = { "X\0", "O\0" };
                    if (grid[x + y * 3] != EMPTY)
                        DrawText(text[grid[x + y * 3]], 230 * x, 230 * y, 150, BLACK);
                }

        }
        else
        {
            char *text[] = { "X has won\0", "O has won\0" };
            DrawText(text[winner], 20, 200, 100, BLACK);

        }

        if (IsKeyDown(KEY_R))
        {
            winner = EMPTY;
            turn = X;

            for (int i = 0; i < 9; i ++)
                grid[i] = EMPTY;
        }

        EndDrawing();

    }

    CloseWindow();
}

