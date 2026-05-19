#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include "components/velocity.h"
#include "components/characterController.h"
#include "components/boxCollider.h"


struct CharacterControlSystem
{
    inline static void MoveBasedOnInput(entt::registry &registry)
    {
        auto view = registry.view<CharacterController, Velocity>();

        for (auto [entt, characterController, velocity] : view.each())
        {
            velocity.velocity.x = 0.0f;
            velocity.velocity.y = 0.0f;

            if (IsKeyDown(KEY_W)) velocity.velocity.y -= characterController.speed;
            if (IsKeyDown(KEY_S)) velocity.velocity.y += characterController.speed;
            if (IsKeyDown(KEY_A)) velocity.velocity.x -= characterController.speed;
            if (IsKeyDown(KEY_D)) velocity.velocity.x += characterController.speed;
        }
    }
};