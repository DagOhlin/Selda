#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include "components/position.h"
#include "components/characterController.h"
#include "components/boxCollider.h"


struct CharacterControlSystem
{
    inline static void MoveBasedOnInput(entt::registry &registry)
    {
        auto view = registry.view<CharacterController, Position>();

        for (auto [entt, characterController, position] : view.each())
        {
            float deltaTime = GetFrameTime();

            if (IsKeyDown(KEY_W))
            {
                position.pos.y -= characterController.speed * deltaTime;
            }
            if (IsKeyDown(KEY_S))
            {
                position.pos.y += characterController.speed * deltaTime;
            }
            if (IsKeyDown(KEY_A))
            {
                position.pos.x -= characterController.speed * deltaTime;
            }
            if (IsKeyDown(KEY_D))
            {
                position.pos.x += characterController.speed * deltaTime;
            }
        }
    }
};