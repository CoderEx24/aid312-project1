#include <stdio.h>
#include <raylib.h>
#include "grid.h"

int main()
{
    Grid grid = grid_init();
    short turn = X;
    short winner = 2;

    InitWindow(600, 600, "test");
    while (!WindowShouldClose())
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = GetMouseX() / 200;
            int y = GetMouseY() / 200;

            if (grid[x + y * 3] == 2)
            {
                grid[x + y * 3] = turn;
                turn = (turn == X) ? O : X;

                winner = grid_get_winner(grid);
            }
        }

        ClearBackground(WHITE);
        BeginDrawing();

        if (winner == 2)
        {
            DrawLine(200, 0, 200, 600, BLACK);
            DrawLine(400, 0, 400, 600, BLACK);
            DrawLine(0, 200, 600, 200, BLACK);
            DrawLine(0, 400, 600, 400, BLACK);

            for (int x = 0; x < 3; x ++)
                for (int y = 0; y < 3; y ++)
                {
                    char *text[] = { "X\0", "O\0" };
                    if (grid[x + y * 3] != 2)
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
            winner = 2;
            turn = X;

            for (int i = 0; i < 9; i ++)
                grid[i] = 2;
        }

        EndDrawing();

    }

    CloseWindow();
}

