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
		
		if (OnEntityDestroyedLuaCallbackComponent* const luaCallbackComponent = registry.try_get<OnEntityDestroyedLuaCallbackComponent>(entity))
		{
			// This component is getting destroyed along with the entity, so we can move all the callbacks into the temporary vector.
			for (auto& callback : luaCallbackComponent->callbacks)
				deadEntityCallbacks.emplace_back(entity, std::move(callback));
		}

		registry.destroy(entity);
		Logger::WriteLine(entityName, " has been destroyed.");
	}

	// Now that the entity is destroyed, we can inform any listeners that the entity ids are no longer valid.
	for (const auto& [entity, callback] : deadEntityCallbacks)
	{
		if (callback)
			callback(entity);
	}
}