#include <iostream>
#include <entt/entt.hpp>
#include <raylib.h>
#include <string>

// create simpleEnemy
#include "components/position.h"
#include "scene.h"
#include "luabindings.h"
#include "components/scale.h"

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

    auto image = LoadImage("Blink2.png");
    // ImageResizeNN(&image, 128, 128);
    auto blinkTex = LoadTextureFromImage(image);
    UnloadImage(image);

    scene.CreateObject()
        .Add<Position>(Vector2{100.f, 100.f})
        .Add<Texture2D>(blinkTex)
        .Add<Scale>(8.f)
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
        scene.Update();
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