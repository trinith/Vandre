#include <iostream>
#include <vector>

#include <entt.hpp>
#include <EntityUtils.h>
#include <MethodHelperMacros.h>
#include <VandreLogging.h>

#include <Components/DestroyEntityComponent.h>
#include <Components/NameComponent.h>
#include <Components/NextPositionComponent.h>
#include <Components/PositionComponent.h>
#include <Components/VelocityComponent.h>
#include <Systems/DeadEntityCleanupSystem.h>
#include <Systems/PositionFinalizeSystem.h>
#include <Systems/PositionUpdateSystem.h>
#include <Systems/SystemRegistry.h>

entt::entity CreateEntity(entt::registry& registry, std::string_view name, Vector2f velocity)
{
	using namespace Components;

	const entt::entity entity = registry.create();

	registry.emplace<NameComponent>(entity, std::string{ name });
	registry.emplace<PositionComponent>(entity, Vector2f{ 0.f, 0.f });
	registry.emplace<NextPositionComponent>(entity, Vector2f{ 0.f, 0.f });
	registry.emplace<VelocityComponent>(entity, velocity);

	return entity;
}

int main()
{
	Logger::WriteLine("Starting...");

	entt::registry registry;

	CreateEntity(registry, "entityA", { 0.f, 0.f });
	CreateEntity(registry, "entityB", { 1.f, 0.f });
	CreateEntity(registry, "entityC", { 0.f, 0.f });

	Systems::SystemRegistry systemRegistry;
	systemRegistry.RegisterSystem<Systems::PositionUpdateSystem>(registry);
	systemRegistry.RegisterSystem<Systems::PositionFinalizeSystem>(registry);
	systemRegistry.RegisterSystem<Systems::DeadEntityCleanupSystem>(registry);

	for (int i = 0; i < 5; i++)
	{
		Logger::WriteLine("TICK ", i, " - BEGIN");
		{
			auto indentScope = Logger::CreateIndentScope();
			systemRegistry.TickSystems(1.f);
		}
		Logger::WriteLine("TICK ", i, " - END");
		Logger::WriteLine();
	}

	return 0;
}