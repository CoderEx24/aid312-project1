#include <raylib.h>

int main()
{
    InitWindow(600, 600, "test");
    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        DrawText("TIC-TAC-TOE", 200, 260, 20, BROWN); 

        EndDrawing();

    }

    CloseWindow();
}

