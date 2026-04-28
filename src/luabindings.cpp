#include <iostream>

#include "luabindings.h"
#include "scene.h"

#include "components/box.h"
#include "components/charachterController.h"
#include "components/clickable.h"
#include "components/colour.h"
#include "components/position.h"
#include "components/speed.h"
#include "util.h"

Lua::Lua() : lua_state(luaL_newstate())
{
    luaL_openlibs(this->lua_state);
    this->MakeFunc(Lua::CreateEntity, "CreateEntity");
    this->MakeFunc(Lua::AddComponent, "AddComponent");
}

Lua::~Lua()
{

    lua_close(this->lua_state);
}

void Lua::PushBool(bool b)
{
    lua_pushboolean(this->lua_state, b);
}

void Lua::PushInt(int i)
{
    lua_pushinteger(this->lua_state, i);
}

void Lua::PushFunc(int (*f)(lua_State *))
{
    lua_pushcfunction(this->lua_state, f);
}

void Lua::PushString(std::string s)
{
    lua_pushstring(this->lua_state, s.data());
}

int Lua::PopInt(int index)
{
    int data = lua_tointeger(this->lua_state, index);
    return data;
}

std::string Lua::PopString(int index)
{
    const char *dataC = lua_tostring(this->lua_state, index);
    std::string data = std::string(dataC);
    return data;
}

void Lua::DoFile(const char *file)
{
    luaL_dofile(this->lua_state, file);
}

float Lua::PopFloat(int index)
{
    float data = lua_tonumber(this->lua_state, index);
    return data;
}

void Lua::GetGlobal(const char *name)
{
    lua_getglobal(this->lua_state, name);
}

void Lua::SetGlobal(const char *name)
{
    lua_setglobal(this->lua_state, name);
}

void Lua::MakeFunc(int (*f)(lua_State *), const char *name)
{
    this->PushFunc(f);
    this->SetGlobal(name);
}

void Lua::DumpStack()
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

int Lua::CreateEntity(lua_State *lua_state)
{
    auto entity = Scene::Get()->CreateEntity().Build();
    std::cout << "Created entity " << "entity" << "\n";

    lua_pushnumber(lua_state, (int)entity);

    return 1;
}

int Lua::AddComponent(lua_State *lua_state)
{
    auto ic = Incrementer(1);
    Lua *lua = Lua::Get();
    const entt::entity entity = (entt::entity)lua->PopInt(ic.Get());
    std::string component = lua->PopString(ic.Get());

    std::cout << "Adding component " << component << " To entity " << (int)entity << "\n";

    if (component == "Position")
    {
        float x = lua->PopFloat(ic.Get());
        float y = lua->PopFloat(ic.Get());

        Scene::Get()->AddComponent<Position>(entity, x, y);
    }
    else if (component == "Box")
    {
        float x = lua->PopFloat(ic.Get());
        float y = lua->PopFloat(ic.Get());
        float width = lua->PopFloat(ic.Get());
        float height = lua->PopFloat(ic.Get());

        Scene::Get()->AddComponent<Box>(entity, x, y, width, height);
    }
    else if (component == "Colour")
    {
        unsigned char r = lua->PopInt(ic.Get());
        unsigned char g = lua->PopInt(ic.Get());
        unsigned char b = lua->PopInt(ic.Get());
        unsigned char a = lua->PopInt(ic.Get());

        Scene::Get()->AddComponent<Colour>(entity, r, g, b, a);
    }
    else if (component == "Speed")
    {
        float speed = lua->PopInt(ic.Get());
        Scene::Get()->AddComponent<Speed>(entity, speed);
    }
    else if (component == "Clickable")
    {
        std::string funcName = lua->PopString(ic.Get());
        lua_setglobal(lua_state, funcName.data());
        Scene::Get()->AddComponent<Clickable>(entity, funcName);
    }
    else
        throw std::runtime_error(std::string("Dis is no component, here atleast") + std::string(component));

    auto func = lua_tocfunction(lua_state, -1);

    lua_settop(lua->GetState(), 0);

    return 0;
}

Lua *Lua::Get()
{
    static std::unique_ptr<Lua> lua = std::make_unique<Lua>();
    return lua.get();
}

lua_State *Lua::GetState()
{
    return this->lua_state;
}
