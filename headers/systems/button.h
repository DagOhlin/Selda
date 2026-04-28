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
            Text *maybeText = registry.try_get<Text>(entity);
            if(maybeText){
                //std::cout << "it has text" << std::endl;
                DrawText("Congrats! You created your first window!", 190, 300, 20, LIGHTGRAY);

                DrawText(maybeText->text.c_str(), box.rectangle.y, box.rectangle.width, maybeText->fontSize, maybeText->color);
            }
        }
    }
};