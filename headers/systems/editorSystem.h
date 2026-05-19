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
#include "components/typeName.h"
#include "components/selector.h"

static TypeName current = TypeName{"Ground"};

struct EditorSystem
{
    inline static void Click(entt::registry &registry)
    {
        auto view = registry.view<Box, TypeName>();

        for (auto [entity, box, t] : view.each())
        {
            if (CheckCollisionPointRec(GetMousePosition(), box.rectangle) && IsMouseButtonPressed(0))
            {
                // Clicked box is a placement selector
                if (registry.try_get<Selector>(entity))
                {
                    // Set currently selected
                    current = t;
                }
                else
                {
                    // change type
                    if (t.typeName != current.typeName)
                    {
                        t = current;
                    }
                    // Change stuff like sprite maybe
                }
            }
        }
    }
};