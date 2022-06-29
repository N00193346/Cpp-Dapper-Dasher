#include "raylib.h"


struct AnimnData
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

    AnimnData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x  = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.x  = windowWidth/2 - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //Rectangle to select section of sprite texture
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};

    //Position of the sprite
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};
  
    //Animation frame
    int frame{};
    int nebFrame{};
    int neb2Frame{};

    //Amount of time before update the animation 
    const float updateTime{1.0/12.0};
    const float nebUpdateTime{1.0/12.0};
    const float neb2UpdateTime{1.0/12.0};

    float runningTime{};
    float nebRunningTime{};   
    float neb2RunningTime{};

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


        //Update nebula position
        nebPos.x += nebVel * dT;

        //Update nebula2 position
        neb2Pos.x += nebVel * dT;

        //Update character position
        scarfyPos.y += velocity * dT;

        //Update chartacter running time
        runningTime += dT;
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            //Update animation frame
            if (!isInAir){
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        //Update nebula running time
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            //Update animation frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
       
        }

         //Update nebula2 running time
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            nebRunningTime = 0.0;
            //Update animation frame
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
       
        }

        //Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        //Draw nebula2
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        //Draw character 
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
       

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}