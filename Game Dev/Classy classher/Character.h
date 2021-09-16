#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return WorldPos; }
    void tick(float deltaTime);
    Rectangle getCollisionRec();
    void undoMovement();
private:
    Texture2D texture{LoadTexture("charecters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("charecters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("charecters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 WorldPos{};

    Vector2 worldPoslastframe{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
};
