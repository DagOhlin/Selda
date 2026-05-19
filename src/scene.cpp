#include "scene.h"
#include "systems/drawable.h"
#include "systems/button.h"
#include "systems/characterControlSystem.h"
#include "systems/collisionSystem.h"

entt::registry &Scene::GetRegistry()
{
    return this->registry;
}

void Scene::Update()
{
    DrawSystem::Draw(this->GetRegistry());
    ButtonSystem::Draw(this->GetRegistry());
    CollisionSystem::Update(this->GetRegistry());
    CharacterControlSystem::MoveBasedOnInput(this->GetRegistry());
}

void Scene::Clear()
{
    this->registry.clear();
}

Scene *Scene::Get()
{
    static std::unique_ptr<Scene> self = std::make_unique<Scene>();

    return self.get();
}
// Scene functions
ObjectBuilder Scene::CreateEntity()
{
    return ObjectBuilder(this->registry);
}

entt::entity ObjectBuilder::Build()
{
    return this->entity;
}
