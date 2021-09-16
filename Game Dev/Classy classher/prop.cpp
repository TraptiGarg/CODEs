#include "prop.h"

Prop::Prop(Vector2 pos, Texture2D tex):
    WorldPos(pos),
    texture (tex)
{
    
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos{ Vector2Subtract(WorldPos, knightPos) };
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{ Vector2Subtract(WorldPos, knightPos) };
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}