#include "DeadEntityCleanupSystem.h"

#include <iostream>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/OnEntityDestroyedLuaCallbackComponent.h>
#include <Components/DestroyEntityComponent.h>

using namespace Components;
using namespace Systems;

void DeadEntityCleanupSystem::OnExecute(float dt)
{
	Logger::WriteLine("DeadEntityCleanupSystem::OnExecute");

	entt::registry& registry = GetRegistry();
	auto view = registry.view<DestroyEntityComponent>();

	std::vector<std::tuple<entt::entity, sol::function>> deadEntityCallbacks;

	auto indentScope = Logger::CreateIndentScope();

	// Destroy entities.
	for (auto entity : view)
	{
		const std::string entityName = EntityUtils::GetEntityName(registry, entity);
		
		if (const OnEntityDestroyedLuaCallbackComponent* const luaCallbackComponent = registry.try_get<OnEntityDestroyedLuaCallbackComponent>(entity))
			deadEntityCallbacks.emplace_back(entity, luaCallbackComponent->luaCallback);

		registry.destroy(entity);
		Logger::WriteLine(entityName, " has been destroyed.");
	}

	// Notify any listeners that the entity was destroyed.
	for (const auto& [entity, callback] : deadEntityCallbacks)
	{
		if (callback)
			callback(entity);
	}
}