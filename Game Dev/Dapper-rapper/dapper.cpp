#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnground(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltatime, int maxFrame)
{
    data.runningTime += deltatime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //update anim frame
        data.rec.x = data.frame* data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}
int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    const int gravity{1'000};

    //nebula varibels
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //animeData nebula

    int sizeofNebulae{20};

    AnimData nebulae[sizeofNebulae]{};

    for(int  i = 0; i < sizeofNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i *300;
    }

    float finishLine{ nebulae[sizeofNebulae - 1].pos.x };
    float velLine{ nebulae[sizeofNebulae - 2].pos.x};

    // nebula velocity pixel/second
    int nebVel{-200};
    //scarfy varibles
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0; 
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;
    // in air check
    bool isInAir{};
    //jump velocity
    const int jumpVel{-600};

    int velocity{-10};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-building.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgX{};
    float fgX{};
    float mgX{};

    bool collision{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        //delta time

        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20*dT;
        if(bgX <= -background.width*2)
        {
            bgX = 0.0;
        }
        // scroll mid ground
        mgX -= 40*dT;
        if(mgX <= -midground.width*2)
        {
            mgX = 0.0;
        }     
        //scroll foreground
        fgX -= 80*dT;   
        if(fgX <= -foreground.width*2)
        {
            fgX = 0.0;
        }
        //Draw background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        // draw midground

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        //draw foreground

        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if (isOnground(scarfyData, windowDimensions[1]))
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        for (int i = 0; i < sizeofNebulae; i++)
        {
            nebulae[i].pos.x += nebVel*dT;
        }
        
        if (IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;
        }

        for (int i = 0; i < sizeofNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }
        velLine += nebVel*dT;


        //update finishing line
        finishLine += nebVel*dT;

        //update scarfy
        scarfyData.pos.y += velocity * dT;
        
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for(AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        if (collision)
        {
            // lose game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            DrawText("You won!", windowDimensions[0]/4, windowDimensions[1]/2, 40, BLUE);
        }
        else
        {
            for (int i = 0; i < sizeofNebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        }

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(foreground);
    UnloadTexture(midground);
    CloseWindow();
}