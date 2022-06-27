#include "raylib.h"


int main() 
{

    //Window dimensions
    const int windowWidth {513};
    const int windowHeight {380};

    //Initalise window
    InitWindow(windowWidth,windowHeight, "Dapper Dasher");

    //Acceleration due to gravity (pixels/s)/s
    const int gravity{1000};
    //Jump velocity (pixels per second)
    const int jumpVel{-600};

    bool isInAir{false};

    //Loading sprite Texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    //Rectangle to select section of sprite texture
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    //Position of the sprite
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //Animation frame
    int frame{};

    //Amount of time before update the animation 
    const float updateTime{1.0/12.0};
    float runningTime{};
    int velocity{0};
   

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        //Delta time
        const float dT{GetFrameTime()};


        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

 
        //Check if on the ground
        if (scarfyPos.y >= windowHeight - scarfyRec.height) 
        {
            //rectangle on the ground
            velocity = 0;
            isInAir = false;
        } else
        {
            //Apply gravity
            velocity += gravity * dT;
        }

        //Check for jumping
          if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
            isInAir = true;
        }

        //Update position
        scarfyPos.y += velocity * dT;

        //Update running time
        runningTime += dT;
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            //Update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }


        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
       

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

}