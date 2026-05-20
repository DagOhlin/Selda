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
#include "components/sprite.h"

static TypeName current = TypeName{"Ground"};

struct EditorSystem
{
    inline static void Click(entt::registry &registry)
    {
        if (!IsMouseButtonPressed(0))
            return;
        auto view = registry.view<Box, TypeName>();

        for (auto [entity, box, t] : view.each())
        {
            if (CheckCollisionPointRec(GetMousePosition(), box.rectangle))
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
                        Image image = LoadImage(("textures/" + t.typeName + ".png").c_str());
                        Texture tex = LoadTextureFromImage(image);
                        UnloadImage(image);
                        registry.emplace_or_replace<Sprite>(entity, tex);
                    }
                    // Change stuff like sprite maybe
                }
            }
        }
    }
};