#pragma once

#include <entt/entt.hpp>

class ObjectBuilder
{
public:
    template <typename T, typename... Args>
    ObjectBuilder &Add(T component, Args &&...args);
    void Build();
    friend class Scene;

private:
    ObjectBuilder(entt::registry &registry) : registry(registry), entity(registry.create()) {}
    entt::entity entity;
    entt::registry &registry;
};

class Scene
{
public:
    ObjectBuilder CreateObject();

private:
    entt::registry registry;
};

ObjectBuilder Scene::CreateObject()
{
    return ObjectBuilder(this->registry);
}

template <typename T, typename... Args>
[[nodiscard]] ObjectBuilder &ObjectBuilder::Add(T component, Args &&...args)
{
    this->registry.emplace<T>(this->entity, std::forward<Args>(args)...);
    return *this;
}

void ObjectBuilder::Build()
{
    return;
}