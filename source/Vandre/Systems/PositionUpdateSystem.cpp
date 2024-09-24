#include "PositionUpdateSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/NextPositionComponent.h>
#include <Components/PositionComponent.h>
#include <Components/VelocityComponent.h>

using namespace Components;
using namespace Systems;

void PositionUpdateSystem::OnExecute(float dt)
{
	Logger::WriteLine("PositionUpdateSystem::OnExecute");
	auto& registry = GetRegistry();
	auto view = registry.view<NextPositionComponent, const PositionComponent, const VelocityComponent>();

	auto indentScope = Logger::CreateIndentScope();
	for (auto entity : view)
	{
		TickEntity(
			dt,
			EntityUtils::GetEntityName(registry, entity),
			view.get<NextPositionComponent>(entity),
			view.get<const PositionComponent>(entity),
			view.get<const VelocityComponent>(entity)
		);
	}
}

void PositionUpdateSystem::TickEntity(
	float dt,
	std::string_view entityName,
	NextPositionComponent& nextPos,
	const PositionComponent& pos,
	const VelocityComponent& vel
)
{
	if (vel.velocity.x == 0 && vel.velocity.y == 0)
	{
		Logger::WriteLine(entityName ," did not set next position, velocity is zero.");
		return;
	}

	nextPos.position = {
		pos.position.x + dt * vel.velocity.x,
		pos.position.y + dt * vel.velocity.y
	};

	Logger::WriteLine(entityName, " next position set to ", nextPos.position, ".");
}