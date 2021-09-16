#include "raylib.h"
int main()
{
    //windows dimentions
    int width{800};
    int height{450};
    InitWindow(width, height, "Rijul's window");
    
    //circle cords
    int circle_x{200};
    int circle_y{200};
    int circle_r{25};

    //circle edges
    int l_circle_x{circle_x - circle_r};
    int r_circle_x{circle_x + circle_r};
    int u_circle_y{circle_y - circle_r};
    int b_circle_y{circle_y + circle_r};


    //axe cords etc.
    int axe_x{400};
    int axe_y{0};
    int axe_l{50};
    int direction{10};

    //axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_l};
    int u_axe_y{axe_y - axe_l};
    int b_axe_y{axe_y + axe_l};

    // collistion
    bool collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);


        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // update edges
            l_circle_x = circle_x - circle_r;
            r_circle_x = circle_x + circle_r;
            u_circle_y = circle_y - circle_r;
            b_circle_y = circle_y + circle_r;
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_l;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_l;

            //update collision with axe;
            collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

            DrawCircle(circle_x, circle_y, circle_r, BLUE);
            DrawRectangle(axe_x, axe_y, axe_l, axe_l, RED);

            //move axe
            axe_y += direction;

            if (axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }

            if (IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x += 10;
            }

            if (IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= 10;
        }

        }
        EndDrawing();
    }
    
}