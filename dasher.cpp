#include "raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() 
{

    //Window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    
  

    //Initalise window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    //Acceleration due to gravity (pixels/s)/s
    const int gravity{1000};
    //Jump velocity (pixels per second)
    const int jumpVel{-600};

    bool isInAir{false};

    //Loading sprite Texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x  = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.x  = windowDimensions[0]/2 - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++ )
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8; 
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y =  windowDimensions[1] - nebula.height/8;     
        nebulae[i].frame = 0;     
        nebulae[i].runningTime = 0.0;     
        nebulae[i].updateTime = 0.0;

    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;


    int velocity{0};
    //Nebula x velocity (pixels/second)
    int nebVel{-200};
   

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        //Delta time
        const float dT{GetFrameTime()};


        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

 
        //Check if on the ground
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) 
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


        //Update nebula position
       nebulae[0].pos.x += nebVel * dT;

        //Update nebula2 position
        nebulae[1].pos.x += nebVel * dT;

        //Update character position
       scarfyData.pos.y += velocity * dT;

        //Update chartacter running time
        scarfyData.runningTime += dT;
        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0.0;
            //Update animation frame
            if (!isInAir){
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        //Update nebula running time
        for (int i; i < 3; i ++){

            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                //Update animation frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                } 
        }

        }
  

        //Draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        //Draw nebula2
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
          //Draw nebula2
        DrawTextureRec(nebula, nebulae[2].rec, nebulae[2].pos, WHITE);

        //Draw character 
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
       

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}