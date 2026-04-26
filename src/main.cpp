#include <iostream>
#include <entt/entt.hpp>
#include <raylib.h>
#include <string>

// create simpleEnemy
#include "components/position.h"
#include "scene.h"
#include "luabindings.h"

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Scene scene;
    Lua lua;

    lua.DoFile("scripts/test.lua");
    lua.DoFile("scripts/test2.lua");

    lua.GetGlobal("testvar");
    lua.GetGlobal("testvar2");

    lua.DumpStack();

    auto image = LoadImage("Blink.png");
    // ImageResizeNN(&image, 128, 128);
    auto blinkTex = LoadTextureFromImage(image);
    UnloadImage(image);

    scene.CreateObject()
        .Add<int>(15)
        .Add<Position>(Vector2{100.f, 100.f})
        .Add<Texture2D>(blinkTex)
        .Build();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Tick
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw objects
        for (auto [entity, texture, position] : scene.GetRegistry().view<Texture2D, Position>().each())
        {
            DrawTextureEx(texture, position.pos, 0, 8, Color{255, 255, 255, 255});
        }
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}