#include <iostream>
#include <entt/entt.hpp>
#include <raylib.h>
#include <string>

// create simpleEnemy
#include "components/position.h"
#include "scene.h"
#include "luabindings.h"
#include "components/scale.h"
#include "components/sprite.h"
#include "components/box.h"
#include "components/clickable.h"
#include "components/colour.h"
#include "components/characterController.h"

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Lua::Get()->DoFile("scripts/init.lua");

    auto image = LoadImage("Blink2.png");
    // ImageResizeNN(&image, 128, 128);
    auto blinkTex = LoadTextureFromImage(image);
    UnloadImage(image);

    Scene *scene = Scene::Get();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);

    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT); // this makes the pixels nu blury when scaled
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_F11))
        {
            if (IsWindowFullscreen())
            {
                ToggleFullscreen();
                SetWindowSize(screenWidth, screenHeight);
            }
            else
            {
                int monitor = GetCurrentMonitor();

                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
                ToggleFullscreen();
            }
        }
        // new stuff

        float scaleX = (float)GetScreenWidth() / screenWidth;
        float scaleY = (float)GetScreenHeight() / screenHeight;
        SetMouseScale(1.0f / scaleX, 1.0f / scaleY);
        SetMouseOffset(0, 0);

        BeginTextureMode(canvas);
        ClearBackground(Color{100, 100, 200, 255});

        scene->Update();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle sourceRec = {0.0f, 0.0f, (float)canvas.texture.width, -(float)canvas.texture.height};

        Rectangle destRec = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};

        Vector2 origin = {0.0f, 0.0f};

        DrawTexturePro(canvas.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        // Tick

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}