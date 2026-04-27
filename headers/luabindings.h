#pragma once

#include <lua.hpp>
#include <string>
#include <scene.h>
#include <memory>
#include "components/speed.h"

class Lua
{
public:
    Lua();
    ~Lua();

    void DoFile(const char *file);

    void PushBool(bool b);
    void PushInt(int i);
    void PushFunc(int (*f)(lua_State *));
    void PushString(std::string s);

    void GetGlobal(const char *name);
    void SetGlobal(const char *name);

    void MakeFunc(int (*f)(lua_State *), const char *name);

    void DumpStack();

    // Lua functions
    static int CreateEntity(lua_State *lua_state);
    static int AddComponent(lua_State *lua_state);

    // Singleton
    static Lua *Get();

private:
    lua_State *lua_state = nullptr;
    static std::unique_ptr<Lua> self;
};

Lua::Lua() : lua_state(luaL_newstate())
{
    luaL_openlibs(this->lua_state);
    this->MakeFunc(Lua::CreateEntity, "CreateEntity");
}

Lua::~Lua()
{

    lua_close(this->lua_state);
}

inline void Lua::PushBool(bool b)
{
    lua_pushboolean(this->lua_state, b);
}

inline void Lua::PushInt(int i)
{
    lua_pushinteger(this->lua_state, i);
}

inline void Lua::PushFunc(int (*f)(lua_State *))
{
    lua_pushcfunction(this->lua_state, f);
}

inline void Lua::PushString(std::string s)
{
    lua_pushstring(this->lua_state, s.data());
}

inline void Lua::DoFile(const char *file)
{
    luaL_dofile(this->lua_state, file);
}

inline void Lua::GetGlobal(const char *name)
{
    lua_getglobal(this->lua_state, name);
}

inline void Lua::SetGlobal(const char *name)
{
    lua_setglobal(this->lua_state, name);
}

inline void Lua::MakeFunc(int (*f)(lua_State *), const char *name)
{
    this->PushFunc(f);
    this->SetGlobal(name);
}

inline void Lua::DumpStack()
{
    int top = lua_gettop(this->lua_state);

    std::cout << "Lua stack (" << top << " items):\n";

    for (int i = 1; i <= top; ++i)
    {
        int t = lua_type(this->lua_state, i);

        std::cout << i << ": " << lua_typename(this->lua_state, t);

        switch (t)
        {
        case LUA_TSTRING:
            std::cout << " = \"" << lua_tostring(this->lua_state, i) << "\"";
            break;

        case LUA_TBOOLEAN:
            std::cout << " = " << (lua_toboolean(this->lua_state, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:
            std::cout << " = " << lua_tonumber(this->lua_state, i);
            break;

        default:
            break;
        }

        std::cout << "\n";
    }
}

inline int Lua::CreateEntity(lua_State *lua_state)
{
    auto entity = Scene::Get()->CreateEntity().Build();
    lua_pushnumber(lua_state, (int)entity);

    return 1;
}

inline int Lua::AddComponent(lua_State *lua_state)
{
    const entt::entity entity = (entt::entity)lua_tointeger(lua_state, -1);
    const char *component = lua_tostring(lua_state, -1);
    if (component == "Position")
        Scene::Get()->AddComponent<Position>(entity);
    else if (component == "Speed")
        Scene::Get()->AddComponent<Speed>(entity);
    else
        throw std::runtime_error("Dis is no component, here atleast");

    return 0;
}

inline Lua *Lua::Get()
{
    if (!Lua::self.get())
        Lua::self = std::make_unique<Lua>();
    return Lua::self.get();
}
