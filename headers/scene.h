#pragma once

#include <entt/entt.hpp>
#include "systems/drawable.h"
#include "systems/button.h"
#include "systems/charachterControllSystem.h"

// #include <

class ObjectBuilder
{
public:
    template <typename T, typename... Args>
    ObjectBuilder &Add(Args &&...args);
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
    template <typename T>
    void AddComponent(entt::entity entity);
    inline static Scene *Get();

private:
    entt::registry registry;
    inline static std::unique_ptr<Scene> self;
};

entt::registry &Scene::GetRegistry()
{
    return this->registry;
}
inline void Scene::Update()
{
    DrawSystem::Draw(this->GetRegistry());
    ButtonSystem::Draw(this->GetRegistry());
    CharachterControllSystem::MoveBasedOnInput(this->GetRegistry());
}
inline Scene *Scene::Get()
{
    if (!Scene::self.get())
        Scene::self = std::make_unique<Scene>();
    return Scene::self.get();
}
// Scene functions
ObjectBuilder Scene::CreateEntity()
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

entt::entity ObjectBuilder::Build()
{
    return this->entity;
}

template <typename T>
inline void Scene::AddComponent(entt::entity entity)
{
    this->registry.emplace<T>(entity);
}
