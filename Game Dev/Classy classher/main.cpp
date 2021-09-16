#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Rijul's window");

    Texture2D map = LoadTexture("nature_tileset/World_map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};


    Prop props[2]{
        Prop{Vector2{400.f, 600.f}, LoadTexture("nature_tileset/rock.png")},
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Log.png")}
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        
        for(auto prop:props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
}