#define SOL_ALL_SAFETIES_ON 1

#include <entt.hpp>
#include <sol/sol.hpp>

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
	registry.emplace<VelocityComponent>(entity, velocity);

	return entity;
}

int main()
{
	Logger::WriteLine("Starting...");

	entt::registry registry;

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua["CreateTestEntity"] =
		[&registry](const std::string& entityName, float dx, float dy)
		{
			CreateEntity(registry, entityName, { dx, dy });
		};

	try
	{
		lua.script(R"(
			function _init()
				CreateTestEntity("luaEntityA", 0, 0)
				CreateTestEntity("luaEntityB", 1, 0)
				CreateTestEntity("luaEntityC", 0.75, 0)
			end
		)");
	}
	catch (const std::exception& e)
	{
		Logger::WriteLine(e.what());
	}

	std::string initFunction = "_init";
	if (lua[initFunction].valid())
		lua[initFunction].call();

	Systems::SystemRegistry systemRegistry;
	systemRegistry.RegisterSystem<Systems::PositionUpdateSystem>(registry);
	systemRegistry.RegisterSystem<Systems::PositionFinalizeSystem>(registry);
	systemRegistry.RegisterSystem<Systems::DeadEntityCleanupSystem>(registry);

	for (int i = 0; i < 4; i++)
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