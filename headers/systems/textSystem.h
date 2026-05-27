#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <lua.hpp>
#include <iostream>

#include "luabindings.h"

#include "components/position.h"
#include "components/box.h"
#include "components/colour.h"
#include "components/clickable.h"
#include "components/text.h"
#include "systems/characterControlSystem.h"

struct TextSystem
{
    inline static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Box, Text>();

        for (auto [entity, box, text] : view.each())
        {
            DrawText(text.text.c_str(), box.rectangle.x + text.pos.x, box.rectangle.y + text.pos.y, text.fontSize, text.color);
        }
    }
};