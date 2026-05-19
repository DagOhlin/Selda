#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <lua.hpp>
#include <iostream>

#include "luabindings.h"
#include "components/luaBehavior.h"

struct BehaviourSystem
{
    inline static void Update(entt::registry &registry)
    {
        float deltaTime = GetFrameTime();
        auto view = registry.view<Behaviour>();
        lua_State* lueState = Lua::Get()->GetState();

        for (auto [entity, behaviour] : view.each())
        {
            lua_rawgeti(lueState, LUA_REGISTRYINDEX, behaviour.luaTableRef);
            
            lua_getfield(lueState, -1, "OnUpdate");
            
            if (lua_isfunction(lueState, -1))
            {
                lua_pushvalue(lueState, -2);  
                lua_pushnumber(lueState, deltaTime); 
                
                if (lua_pcall(lueState, 2, 0, 0) != LUA_OK) //we should do this everywhere
                {
                    std::cout << "Thing did not work; " << lua_tostring(lueState, -1) << "\n";
                    lua_pop(lueState, 1);
                }
            }
            else
            {
                lua_pop(lueState, 1);
            }
            
            lua_pop(lueState, 1); 
        }
    }
};