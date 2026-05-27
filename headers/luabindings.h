#pragma once

#include <lua.hpp>
#include <string>
#include <memory>
class Lua
{
public:
    Lua();
    Lua(lua_State *L);
    ~Lua();

    void DoFile(const char *file);

    void PushBool(bool b);
    void PushInt(int i);
    void PushFloat(float i);
    void PushFunc(int (*f)(lua_State *));
    void PushString(std::string s);

    bool PopBool(int index = -1);
    int PopInt(int index = -1);
    std::string PopString(int index = -1);
    float PopFloat(int index = -1);

    void GetGlobal(const char *name);
    void SetGlobal(const char *name);

    void MakeFunc(int (*f)(lua_State *), const char *name);

    void DumpStack();

    // Lua functions
    static int CreateEntity(lua_State *lua_state);
    static int RemoveEntity(lua_State *lua_state);
    static int AddComponent(lua_State *lua_state);
    static int GetComponent(lua_State *lua_state);
    static int RemoveComponent(lua_State *lua_state);
    static int GetPlayerPos(lua_State *lua_state);
    static int ClearScene(lua_State *lua_state);
    static int Save(lua_State *lua_state);
    static int Quit(lua_State *lua_state);

    // Singleton
    static Lua *Get();
    lua_State *GetState();

private:
    lua_State *lua_state = nullptr;
    bool owns_lua_state = false;
};
