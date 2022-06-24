#include "raylib.h"


int main() 
{

    //Window dimensions
    const int windowWidth {513};
    const int windowHeight {380};

    //Initalise window
    InitWindow(windowWidth,windowHeight, "Dapper Dasher");

    //Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};
    const int jumpVel{-22};

    bool isInAir{false};

    //Rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

 
        //Check if on the ground
        if (posY >= windowHeight - height) 
        {
            //rectangle on the ground
            velocity = 0;
            isInAir = false;
        } else
        {
            //Apply gravity
            velocity += gravity;
        }

        //Check for jumping
          if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
            isInAir = true;
        }

        //Update position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        
       

        EndDrawing();
    }
    CloseWindow();

}