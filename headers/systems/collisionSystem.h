#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include "components/position.h"
#include "components/velocity.h"
#include "components/boxCollider.h"

struct CollisionSystem
{
    inline static void Update(entt::registry &registry)
    {
        float dt = GetFrameTime();

        auto dynamicView = registry.view<Position, Velocity, BoxCollider>();
        
        auto staticCollidersView = registry.view<Position, BoxCollider>(entt::exclude<Velocity>);

        for (auto [entity, pos, vel, collider] : dynamicView.each())
        {
            if (!collider.solid) continue; 

            
            if (vel.velocity.x != 0.0f)
            {
                Rectangle nextRectX = {
                    pos.pos.x + vel.velocity.x * dt,
                    pos.pos.y,
                    collider.size.x,
                    collider.size.y
                };

                for (auto [otherEntity, otherPos, otherCollider] : staticCollidersView.each())
                {
                    if (!otherCollider.solid) continue; 

                    Rectangle otherRect = {
                        otherPos.pos.x, otherPos.pos.y,
                        otherCollider.size.x, otherCollider.size.y
                    };

                    if (CheckCollisionRecs(nextRectX, otherRect))
                    {
                        vel.velocity.x = 0.0f; 
                        break; 
                    }
                }
            }

            
            if (vel.velocity.y != 0.0f)
            {
                Rectangle nextRectY = {
                    pos.pos.x + vel.velocity.x * dt, 
                    pos.pos.y + vel.velocity.y * dt,
                    collider.size.x,
                    collider.size.y
                };

                for (auto [otherEntity, otherPos, otherCollider] : staticCollidersView.each())
                {
                    if (!otherCollider.solid) continue; 

                    Rectangle otherRect = {
                        otherPos.pos.x, otherPos.pos.y,
                        otherCollider.size.x, otherCollider.size.y
                    };

                    if (CheckCollisionRecs(nextRectY, otherRect))
                    {
                        vel.velocity.y = 0.0f; 
                        break;
                    }
                }
            }
            
           // uppdate pos based on actuall velocity
            pos.pos.x += vel.velocity.x * dt;
            pos.pos.y += vel.velocity.y * dt;
        }
    }
};