#include <raylib.h>
#include "components/position.h"
#include <entt/entt.hpp>
#include "components/scale.h"

struct DrawSystem
{
    static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Texture, Position>();

        for (auto [entity, tex, pos] : view.each())
        {
            Scale *maybeScale = registry.try_get<Scale>(entity);
            float scale = maybeScale ? maybeScale->scale : 1;

            DrawTextureEx(tex, pos.pos, 0, scale, Color{255, 255, 255, 255});
        }
    }
};