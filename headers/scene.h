#pragma once

#include <entt/entt.hpp>

class ObjectBuilder
{
public:
    template <typename T, typename... Args>
    ObjectBuilder &Add(Args &&...args);
    void Build();
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
    ObjectBuilder CreateObject();
    entt::registry &GetRegistry();

private:
    entt::registry registry;
};

entt::registry &Scene::GetRegistry()
{
    return this->registry;
}
// Scene functions
ObjectBuilder Scene::CreateObject()
{
    return ObjectBuilder(this->registry);
}

// ObjectBuilder functions
template <typename T, typename... Args>
[[nodiscard]] ObjectBuilder &ObjectBuilder::Add(Args &&...args)
{
    this->registry.emplace<T>(this->entity, std::forward<Args>(args)...);
    return *this;
}

void ObjectBuilder::Build()
{
    return;
}