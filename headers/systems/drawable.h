#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

#include "components/position.h"
#include "components/scale.h"
#include "components/sprite.h"
struct DrawSystem
{
    inline static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Sprite, Position>();

        for (auto [entity, tex, pos] : view.each())
        {
            Scale *maybeScale = registry.try_get<Scale>(entity);
            float scale = maybeScale ? maybeScale->scale : 1;

            DrawTextureEx(tex.texture, pos.pos, 0, scale, Color{255, 255, 255, 255});
        }
    }
};