#include "DeadEntityCleanupSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/DestroyEntityComponent.h>

using namespace Components;
using namespace Systems;

void DeadEntityCleanupSystem::OnExecute(float dt)
{
	Logger::WriteLine("DeadEntityCleanupSystem::OnExecute");

	entt::registry& registry = GetRegistry();
	auto view = registry.view<DestroyEntityComponent>();

	auto indentScope = Logger::CreateIndentScope();
	for (auto entity : view)
	{
		Logger::WriteLine(EntityUtils::GetEntityName(registry, entity), " has been destroyed.");
		registry.destroy(entity);
	}
}