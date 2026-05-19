#include <iostream>
#include <raylib.h>

#include "luabindings.h"
#include "scene.h"

#include "components/box.h"
#include "components/characterController.h"
#include "components/clickable.h"
#include "components/colour.h"
#include "components/position.h"
#include "components/speed.h"
#include "components/text.h"
#include "components/sprite.h"
#include "components/scale.h"
#include "components/boxCollider.h"
#include "components/velocity.h"

#include "components/typeName.h"
#include "components/selector.h"

#include "util.h"

Lua::Lua() : lua_state(luaL_newstate())
{
    luaL_openlibs(this->lua_state);
    this->MakeFunc(Lua::CreateEntity, "CreateEntity");
    this->MakeFunc(Lua::AddComponent, "AddComponent");
    this->MakeFunc(Lua::ClearScene, "ClearScene");
    this->MakeFunc(Lua::Quit, "Quit");
    this->MakeFunc(Lua::Save, "Save");
    this->MakeFunc(Lua::GetComponent, "GetComponent");
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

void Lua::PushFloat(float i)
{
    lua_pushnumber(this->lua_state, i);
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

bool Lua::PopBool(int index)
{
    bool data = lua_toboolean(this->lua_state, index);
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
        static size_t callBackNumber = 0;

        std::string funcName = std::string("Callback#") + std::to_string(callBackNumber++);
        lua_setglobal(lua_state, funcName.c_str());
        Scene::Get()->AddComponent<Clickable>(entity, funcName);
    }
    else if (component == "Text")
    {
        std::string text = lua->PopString(ic.Get());

        float x = lua->PopFloat(ic.Get());
        float y = lua->PopFloat(ic.Get());

        float fontSize = lua->PopFloat(ic.Get());

        unsigned char r = lua->PopInt(ic.Get());
        unsigned char g = lua->PopInt(ic.Get());
        unsigned char b = lua->PopInt(ic.Get());
        unsigned char a = lua->PopInt(ic.Get());

        Scene::Get()->AddComponent<Text>(entity, Color{r, g, b, a}, text, Vector2{x, y}, fontSize);
    }
    else if (component == "Sprite")
    {
        auto path = lua->PopString(ic.Get());

        Image image = LoadImage(path.c_str());
        Texture tex = LoadTextureFromImage(image);
        UnloadImage(image);

        Scene::Get()->AddComponent<Sprite>(entity, tex);
    }
    else if (component == "Scale")
    {
        float scale = lua->PopFloat(ic.Get());
        std::cout << scale << "\n";
        Scene::Get()->AddComponent<Scale>(entity, scale);
    }
    else if (component == "CharacterController")
    {
        float speed = lua->PopFloat(ic.Get());
        Scene::Get()->AddComponent<CharacterController>(entity, speed);
    }
    else if (component == "Velocity")
    {
        float maxVelocity = lua->PopFloat(ic.Get());
        float vX = lua->PopFloat(ic.Get());
        float vY = lua->PopFloat(ic.Get());

        Scene::Get()->AddComponent<Velocity>(entity, maxVelocity, Vector2{vX, vY});
    }
    else if (component == "BoxCollider")
    {
        float width = lua->PopFloat(ic.Get());
        float height = lua->PopFloat(ic.Get());
        float offsetX = lua->PopFloat(ic.Get());
        float offsetY = lua->PopFloat(ic.Get());
        bool solid = lua->PopBool(ic.Get());

        Scene::Get()->AddComponent<BoxCollider>(entity, Vector2{width, height}, Vector2{offsetX, offsetY}, solid);
    }
    else if (component == "TypeName")
    {
        std::string name = lua->PopString(ic.Get());
        Scene::Get()->AddComponent<TypeName>(entity, name);
    }
    else if (component == "Selector")
    {
        Scene::Get()->AddComponent<Selector>(entity);
    }
    else
        throw std::runtime_error(std::string("Dis is no component, here atleast") + std::string(component));

    auto func = lua_tocfunction(lua_state, -1);

    lua_settop(lua->GetState(), 0);

    return 0;
}

int Lua::GetComponent(lua_State *lua_state)
{

    auto ic = Incrementer(1);
    Lua *lua = Lua::Get();
    const entt::entity entity = (entt::entity)lua->PopInt(ic.Get());
    std::string component = lua->PopString(ic.Get());
    Scene *scene = Scene::Get();

    if (component == "Position")
    {
        auto pos = scene->GetComponent<Position>(entity).pos;
        lua->PushFloat(pos.x);
        lua->PushFloat(pos.y);
        return 2;
    }
    else if (component == "Box")
    {
        auto box = scene->GetComponent<Box>(entity).rectangle;
        lua->PushFloat(box.x);
        lua->PushFloat(box.y);
        lua->PushFloat(box.width);
        lua->PushFloat(box.height);
        return 4;
    }
    else if (component == "Colour")
    {
        auto colour = scene->GetComponent<Colour>(entity).color;
        lua->PushInt(colour.r);
        lua->PushInt(colour.g);
        lua->PushInt(colour.b);
        lua->PushInt(colour.a);
        return 4;
    }
    else if (component == "Speed")
    {
        auto speed = scene->GetComponent<Speed>(entity).speed;
        lua->PushFloat(speed.x);
        lua->PushFloat(speed.y);
        return 2;
    }
    else if (component == "Clickable")
    {
        auto funcName = scene->GetComponent<Clickable>(entity).luaFuncName;
        lua->PushString(funcName);
        return 1;
    }
    else if (component == "Text")
    {
        auto text = scene->GetComponent<Text>(entity);

        lua->PushInt(text.color.r);
        lua->PushInt(text.color.g);
        lua->PushInt(text.color.b);
        lua->PushInt(text.color.a);

        lua->PushString(text.text);

        lua->PushFloat(text.pos.x);
        lua->PushFloat(text.pos.y);

        lua->PushFloat(text.fontSize);

        return 8;
    }
    else if (component == "Sprite")
    {
        throw std::runtime_error("No :)");
    }
    else if (component == "Scale")
    {
        auto scale = scene->GetComponent<Scale>(entity).scale;
        lua->PushFloat(scale);
        return 1;
    }
    else if (component == "CharacterController")
    {
        throw std::runtime_error("No :)");
    }
    else if (component == "Velocity")
    {
        auto velocity = scene->GetComponent<Velocity>(entity);
        lua->PushFloat(velocity.maxVelocity);
        lua->PushFloat(velocity.velocity.x);
        lua->PushFloat(velocity.velocity.y);
        return 3;
    }
    else if (component == "BoxCollider")
    {
        auto boxCol = scene->GetComponent<BoxCollider>(entity);

        lua->PushFloat(boxCol.size.x);
        lua->PushFloat(boxCol.size.y);

        lua->PushFloat(boxCol.offset.x);
        lua->PushFloat(boxCol.offset.y);

        lua->PushBool(boxCol.solid);

        return 5;
    }
    else if (component == "TypeName")
    {
        auto typen = scene->GetComponent<TypeName>(entity).typeName;
        lua->PushString(typen);
        return 1;
    }
    else if (component == "Selector")
    {
        // Scene::Get()->GetComponent<Selector>(entity)._;
        throw std::runtime_error("No :)");
        // lua_pushnil
    }
    else
        throw std::runtime_error(std::string("Dis is no component, here atleast") + std::string(component));
    return 0;
}

int Lua::RemoveComponent(lua_State *lua_state)
{
    auto ic = Incrementer(1);
    Lua *lua = Lua::Get();
    const entt::entity entity = (entt::entity)lua->PopInt(ic.Get());
    std::string component = lua->PopString(ic.Get());
    Scene *scene = Scene::Get();

    if (component == "Position")
    {
        scene->RemoveComponent<Position>(entity);
    }
    else if (component == "Box")
    {
        scene->RemoveComponent<Box>(entity);
    }
    else if (component == "Colour")
    {
        scene->RemoveComponent<Colour>(entity);
    }
    else if (component == "Speed")
    {
        scene->RemoveComponent<Speed>(entity);
    }
    else if (component == "Clickable")
    {
        scene->RemoveComponent<Clickable>(entity);
    }
    else if (component == "Text")
    {
        scene->RemoveComponent<Text>(entity);
    }
    else if (component == "Sprite")
    {
        scene->RemoveComponent<Sprite>(entity);
    }
    else if (component == "Scale")
    {
        scene->RemoveComponent<Scale>(entity);
    }
    else if (component == "CharacterController")
    {
        scene->RemoveComponent<CharacterController>(entity);
    }
    else if (component == "Velocity")
    {
        scene->RemoveComponent<Velocity>(entity);
    }
    else if (component == "BoxCollider")
    {
        scene->RemoveComponent<BoxCollider>(entity);
    }
    else if (component == "TypeName")
    {
        scene->RemoveComponent<TypeName>(entity);
    }
    else if (component == "Selector")
    {
        scene->RemoveComponent<Selector>(entity);
    }
    else
        throw std::runtime_error(std::string("Dis is no component, here atleast") + std::string(component));
    return 0;
}

int Lua::ClearScene(lua_State *lua_state)
{
    Scene::Get()->Clear();
    return 0;
}

int Lua::Save(lua_State *lua_state)
{
    Scene::Get()->Save();
    return 0;
}

int Lua::Quit(lua_State *lua_state)
{
    CloseWindow();
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
