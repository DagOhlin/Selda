#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

#include "components/position.h"
#include "components/scale.h"
#include "components/sprite.h"
#include "systems/characterControlSystem.h"
#include <vector>

struct DrawData
{
    entt::entity entity;
    Sprite sprite;
    Vector2 pos;
    float scale;
};
struct DrawSystem
{
    inline static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Sprite, Position>();
        std::vector<DrawData> drawData;
        drawData.reserve(64);
        for (auto [entity, tex, pos] : view.each())
        {
            Scale *maybeScale = registry.try_get<Scale>(entity);
            float scale = maybeScale ? maybeScale->scale : 1;
            Vector2 centeredCoords = ScreenSpaceToWorld(pos.pos, true);
            drawData.emplace_back(entity, tex, centeredCoords, scale);

            // DrawTextureEx(tex.texture, centeredCoords, 0, scale, Color{255, 255, 255, 255});
        }
        std::sort(drawData.begin(), drawData.end(), [](const DrawData &a, const DrawData &b)
                  { return a.sprite.layer < b.sprite.layer; });

        for (auto d : drawData)
        {
            DrawTextureEx(d.sprite.texture, d.pos, 0, d.scale, Color{255, 255, 255, 255});
        }
    }
};