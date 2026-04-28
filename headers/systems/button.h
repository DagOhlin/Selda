#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <lua.hpp>

#include "luabindings.h"

#include "components/position.h"
#include "components/box.h"
#include "components/colour.h"
#include "components/clickable.h"

struct ButtonSystem
{
    inline static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Box, Clickable, Colour>();

        for (auto [entity, box, clickable, colour] : view.each())
        {
            if (CheckCollisionPointRec(GetMousePosition(), box.rectangle) && IsMouseButtonPressed(0))
            {
                /* code */
                Lua::Get()->GetGlobal(clickable.luaFuncName.data());
                lua_pcall(Lua::Get()->GetState(), 0, 0, 0);
            }

            DrawRectangle(box.rectangle.x, box.rectangle.y, box.rectangle.width, box.rectangle.height, colour.color);
        }
    }
};