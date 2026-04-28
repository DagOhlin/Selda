#pragma once
#include <entt/entt.hpp>

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
    entt::registry &GetRegistry();
    void Update();
    template <typename T, typename... Args>
    inline void AddComponent(entt::entity entity, Args &&...args);
    static Scene *Get();

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
    this->registry.emplace<T>(entity, std::forward<Args>(args)...);
}
