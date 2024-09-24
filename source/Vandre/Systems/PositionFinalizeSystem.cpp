#include "PositionFinalizeSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/DestroyEntityComponent.h>
#include <Components/PositionComponent.h>
#include <Components/NextPositionComponent.h>

using namespace Components;
using namespace Systems;

void PositionFinalizeSystem::OnExecute(float dt)
{
	Logger::WriteLine("PositionFinalizeSystem::OnExecute");
	auto& registry = GetRegistry();
	auto view = registry.view<PositionComponent, const NextPositionComponent>();

	auto indentScope = Logger::CreateIndentScope();
	for (auto entity : view)
	{
		TickEntity(
			dt,
			entity,
			EntityUtils::GetEntityName(registry, entity),
			view.get<PositionComponent>(entity),
			view.get<const NextPositionComponent>(entity)
		);
	}
}

void PositionFinalizeSystem::TickEntity(float dt, entt::entity entity, std::string_view entityName, PositionComponent& pos, const NextPositionComponent& nextPos)
{
	auto& registry = GetRegistry();
	if (pos.position.x >= 3 && !registry.any_of<DestroyEntityComponent>(entity))
	{
		Logger::WriteLine(entityName, " is out of bounds and will be flagged for removal.");
		registry.emplace<DestroyEntityComponent>(entity);
		return;
	}

	Vector2f oldPos = pos.position;
	pos.position = nextPos.position;
	Logger::WriteLine(entityName, " has moved from ", oldPos, " to ", pos.position, ".");
}