#include <iostream>
#include <entt/entt.hpp>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <raylib.h>
#include <string>

// create simpleEnemy

#include "scene.h"

int main()
{
    Scene scene;

    scene.CreateObject().Add<int>(15).Add<std::string>("Hello there").Build();

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Tick
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw objects

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