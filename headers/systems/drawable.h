#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

#include "components/position.h"
#include "components/scale.h"
#include "components/sprite.h"
#include "systems/characterControlSystem.h"
struct DrawSystem
{
    inline static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Sprite, Position>();

        for (auto [entity, tex, pos] : view.each())
        {
            Scale *maybeScale = registry.try_get<Scale>(entity);
            float scale = maybeScale ? maybeScale->scale : 1;
            Vector2 centeredCoords = ScreenSpaceToWorld(pos.pos, true);

            DrawTextureEx(tex.texture, centeredCoords, 0, scale, Color{255, 255, 255, 255});
        }
        auto view2 = registry.view<Sprite, Position, CharacterController>();
        for (auto [entity, tex, pos, _] : view2.each())
        {
            Scale *maybeScale = registry.try_get<Scale>(entity);
            float scale = maybeScale ? maybeScale->scale : 1;
            Vector2 centeredCoords = ScreenSpaceToWorld(pos.pos, true);

            DrawTextureEx(tex.texture, centeredCoords, 0, scale, Color{255, 255, 255, 255});
        }
    }
};