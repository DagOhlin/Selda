#include "scene.h"
#include "systems/drawable.h"
#include "systems/button.h"
#include "systems/charachterControllSystem.h"

entt::registry &Scene::GetRegistry()
{
    return this->registry;
}

void Scene::Update()
{
    DrawSystem::Draw(this->GetRegistry());
    ButtonSystem::Draw(this->GetRegistry());
    CharachterControllSystem::MoveBasedOnInput(this->GetRegistry());
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
