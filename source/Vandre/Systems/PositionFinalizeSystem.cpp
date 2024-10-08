#include "PositionFinalizeSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/DestroyEntityComponent.h>
#include <Components/PositionComponent.h>
#include <Components/PreviousPositionComponent.h>
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
			registry,
			entity,
			view.get<PositionComponent>(entity),
			view.get<const NextPositionComponent>(entity)
		);
	}
}

void PositionFinalizeSystem::TickEntity(
	float dt,
	entt::registry& registry,
	entt::entity entity,
	Components::PositionComponent& positionComponent,
	const Components::NextPositionComponent& nextPositionComponent
)
{
	const std::string entityName = EntityUtils::GetEntityName(registry, entity);

	const Vector2f& nextPosition = nextPositionComponent.position;

	if (nextPosition.x >= 2)
	{
		Logger::WriteLine(entityName, " is out of bounds and will be flagged for removal.");
		registry.emplace_or_replace<DestroyEntityComponent>(entity);
	}
	else
	{
		const PreviousPositionComponent previousPosition = registry.emplace_or_replace<PreviousPositionComponent>(entity, positionComponent.position);
		positionComponent.position = nextPosition;
		Logger::WriteLine(entityName, " has moved from ", previousPosition.position, " to ", positionComponent.position, ".");
	}

	registry.remove<NextPositionComponent>(entity);
}