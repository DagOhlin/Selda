#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include "components/velocity.h"
#include "components/characterController.h"
#include "components/boxCollider.h"

static Vector2 playerPos = {0, 0};

static Vector2 ScreenSpaceToWorld(Vector2 pixelPos, bool reversed = false)
{

    float scale = 1;
    float changeX = -playerPos.x + GetScreenWidth() / 2 - scale * 8;
    float changeY = -playerPos.y + GetScreenHeight() / 2 - scale * 8;

    if (reversed)
    {
        changeX *= -1;
        changeY *= -1;
    }

    Vector2 worldPos =
        {pixelPos.x - changeX,
         pixelPos.y - changeY};

    return worldPos;
}

struct CharacterControlSystem
{
    inline static void MoveBasedOnInput(entt::registry &registry)
    {
        auto view = registry.view<CharacterController, Velocity, Position>();

        for (auto [entt, characterController, velocity, pos] : view.each())
        {
            velocity.velocity.x = 0.0f;
            velocity.velocity.y = 0.0f;

            if (IsKeyDown(KEY_W))
                velocity.velocity.y -= characterController.speed;
            if (IsKeyDown(KEY_S))
                velocity.velocity.y += characterController.speed;
            if (IsKeyDown(KEY_A))
                velocity.velocity.x -= characterController.speed;
            if (IsKeyDown(KEY_D))
                velocity.velocity.x += characterController.speed;

            playerPos = pos.pos;
        }
    }
};