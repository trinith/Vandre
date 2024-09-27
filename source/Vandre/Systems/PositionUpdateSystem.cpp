#include "PositionUpdateSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/NextPositionComponent.h>
#include <Components/PositionComponent.h>
#include <Components/PreviousPositionComponent.h>
#include <Components/VelocityComponent.h>

using namespace Components;
using namespace Systems;

void PositionUpdateSystem::OnExecute(float dt)
{
	Logger::WriteLine("PositionUpdateSystem::OnExecute");
	auto& registry = GetRegistry();
	auto view = registry.view<const PositionComponent, const VelocityComponent>();

	auto indentScope = Logger::CreateIndentScope();
	for (auto entity : view)
	{
		TickEntity(
			dt,
			entity,
			view.get<const PositionComponent>(entity),
			view.get<const VelocityComponent>(entity)
		);
	}
}

void PositionUpdateSystem::TickEntity(
	float dt,
	entt::entity entity,
	const Components::PositionComponent& positionComponent,
	const Components::VelocityComponent& velocityComponent
)
{
	const Vector2f& position = positionComponent.position;
	const Vector2f velocity = velocityComponent.velocity;

	auto& registry = GetRegistry();
	const std::string entityName = EntityUtils::GetEntityName(registry, entity);

	registry.remove<Components::PreviousPositionComponent>(entity);

	if (velocity.x == 0 && velocity.y == 0)
	{
		Logger::WriteLine(entityName, " did not set next position, velocity is zero.");
		return;
	}

	Vector2 nextPosition{
		position.x + dt * velocity.x,
		position.y + dt * velocity.y
	};

	registry.emplace_or_replace<NextPositionComponent>(entity, nextPosition);
	Logger::WriteLine(entityName, " next position set to ", nextPosition, ".");
}