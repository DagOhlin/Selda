#include "scene.h"
#include "systems/drawable.h"
#include "systems/button.h"
#include "systems/characterControlSystem.h"
#include "systems/editorSystem.h"
#include "components/typeName.h"
#include <fstream>
#include <algorithm>
#include "systems/collisionSystem.h"
#include "systems/luaBehaviorSystem.h"

entt::registry &Scene::GetRegistry()
{
    return this->registry;
}

void Scene::Update()
{
    BehaviourSystem::Update(this->GetRegistry());
    DrawSystem::Draw(this->GetRegistry());
    ButtonSystem::Draw(this->GetRegistry());
    CollisionSystem::Update(this->GetRegistry());
    CharacterControlSystem::MoveBasedOnInput(this->GetRegistry());
    EditorSystem::Click(this->GetRegistry());
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

int Scene::Save(lua_State *)
{
    auto scene = Scene::Get();
    auto &reg = scene->GetRegistry();
    auto view = reg.view<Position, Sprite, TypeName>();
    std::vector<std::tuple<entt::entity, Position, Sprite, TypeName>> entities;

    for (auto [entity, pos, sprite, typeName] : view.each())
    {
        entities.push_back({entity, pos, sprite, typeName});
    }

    std::sort(entities.begin(), entities.end(), [](const std::tuple<entt::entity, Position, Sprite, TypeName> &a, const std::tuple<entt::entity, Position, Sprite, TypeName> &b)
              { return (std::get<1>(a).pos.x + std::get<1>(a).pos.y * 10000) < (std::get<1>(b).pos.x + std::get<1>(b).pos.y * 10000); });

    std::ofstream file("scenes/test.simon");

    auto start = entities.begin();
    if (start == entities.end())
        return 0;
    file << std::get<3>(*start).typeName;
    start++;
    float y = std::get<1>(*start).pos.y;
    for (auto o = start; start != entities.end(); start++)
    {
        if (std::get<1>(*start).pos.y != y)
        {
            y = std::get<1>(*start).pos.y;
            file << "\n";
            file << std::get<3>(*start).typeName;
        }
        else
        {
            file << "|" << std::get<3>(*start).typeName;
        }
    }
    return 0;
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
