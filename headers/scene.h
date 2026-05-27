#pragma once
#include <entt/entt.hpp>
#include <lua.hpp>
#include <raylib.h>

class ObjectBuilder
{
public:
    template <typename T, typename... Args>
    inline ObjectBuilder &Add(Args &&...args);
    entt::entity Build();
    friend class Scene;

private:
    ObjectBuilder(entt::registry &registry) : registry(registry), entity(registry.create()) {}
    entt::entity entity;
    entt::registry &registry;
};

// Scene
class Scene
{
public:
    ObjectBuilder CreateEntity();
    void RemoveEntity(entt::entity entity);
    void Update();
    void Clear();

    template <typename T, typename... Args>
    inline void AddComponent(entt::entity entity, Args &&...args);
    template <typename T>
    inline T GetComponent(entt::entity entity);
    template <typename T>
    inline void RemoveComponent(entt::entity entity);
    entt::registry &GetRegistry();
    static Scene *Get();
    static void Save();

    Vector2 player{150, 220};

private:
    entt::registry registry;
};

// ObjectBuilder functions
template <typename T, typename... Args>
[[nodiscard]] ObjectBuilder &ObjectBuilder::Add(Args &&...args)
{
    this->registry.emplace<T>(this->entity, std::forward<Args>(args)...);
    return *this;
}

template <typename T, typename... Args>
void Scene::AddComponent(entt::entity entity, Args &&...args)
{
    this->registry.emplace_or_replace<T>(entity, std::forward<Args>(args)...);
}
template <typename T>
T Scene::GetComponent(entt::entity entity)
{
    return this->registry.get<T>(entity);
}

template <typename T>
void Scene::RemoveComponent(entt::entity entity)
{
    this->registry.remove<T>(entity);
}
