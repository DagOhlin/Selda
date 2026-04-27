#include <raylib.h>
#include "components/position.h"
#include <entt/entt.hpp>
#include "components/charachterController.h"


struct CharachterControllSystem
{
    static void MoveBasedOnInput(entt::registry &registry)
    {
        auto view = registry.view<CharachterController, Position>();

        for (auto [entt, charachterController, position] : view.each())
        {
            float deltaTime = GetFrameTime();

            if(IsKeyDown(KEY_W)){
                position.pos.y -= charachterController.speed * deltaTime;
            }
            if(IsKeyDown(KEY_S)){
                position.pos.y += charachterController.speed * deltaTime;
            }
            if(IsKeyDown(KEY_A)){
                position.pos.x -= charachterController.speed * deltaTime;
            }
            if(IsKeyDown(KEY_D)){
                position.pos.x += charachterController.speed * deltaTime;
            }
           
            
        }
    }
};