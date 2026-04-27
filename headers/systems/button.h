#include <raylib.h>
#include "components/position.h"
#include <entt/entt.hpp>
#include "components/box.h"
#include "components/colour.h"
#include "components/clickable.h"


struct ButtonSystem
{
    static void Draw(entt::registry &registry)
    {
        auto view = registry.view<Box, Clickable, Colour>();

        for (auto [entity, box, clickable, colour] : view.each())
        {
            if (CheckCollisionPointRec(GetMousePosition(), box.rectangle) && IsMouseButtonPressed(0))
            {
                /* code */
                clickable.callBack();
            }
           
            
            DrawRectangle(box.rectangle.x, box.rectangle.y, box.rectangle.width, box.rectangle.height, colour.color);
        }
    }
};