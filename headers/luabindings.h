#pragma once

#include <lua.hpp>
#include <string>

class Lua
{
public:
    Lua();
    ~Lua();

    void PushBool(bool b);
    void PushInt(int i);
    void PushFunc(int (*f)(lua_State *));
    void PushString(std::string s);
    void DoFile(const char *file);

    void GetGlobal(const char *name);

    void DumpStack();

private:
    lua_State *lua_state;
};

Lua::Lua() : lua_state(luaL_newstate())
{
    luaL_openlibs(this->lua_state);
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
