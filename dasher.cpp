#include "raylib.h"


int main() 
{

    //Window dimensions
    const int width {513};
    const int height {380};

    //Initalise window
    InitWindow(width, height, "Dapper Dasher");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        
        EndDrawing();
    }

}