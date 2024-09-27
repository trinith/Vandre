#define SOL_ALL_SAFETIES_ON 1

#include <entt.hpp>
#include <sol/sol.hpp>

#include <VandreLogging.h>

#include <Components/DestroyEntityComponent.h>
#include <Components/NameComponent.h>
#include <Components/NextPositionComponent.h>
#include <Components/OnEntityDestroyedLuaCallbackComponent.h>
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
			return CreateEntity(registry, entityName, { dx, dy });
		};

	lua["RegisterCallback_OnEntityDestroyed"] =
		//[&registry](const entt::entity entity, std::function<void(entt::entity)> callback)
		[&registry](const entt::entity entity, sol::function callback)
		{
			if (!registry.valid(entity))
			{
				Logger::WriteLine("RegisterCallback_OnEntityDestroyed - Invalid entity supplied.");
				return;
			}

			if (!callback)
			{
				Logger::WriteLine("RegisterCallback_OnEntityDestroyed - No callback supplied.");
				return;
			}

			registry.emplace_or_replace<Components::OnEntityDestroyedLuaCallbackComponent>(entity, callback);
			Logger::WriteLine("RegisterCallback_OnEntityDestroyed - Successfully registered callback.");
		};

	try
	{
		lua.script(R"(
			function _init()
				local entityDefinitions = {
					CreateEntityDefinition("entityA", 0, 0),
					CreateEntityDefinition("entityB", 1, 0),
					CreateEntityDefinition("entityC", 0.75, 0)
				}

				for _, entityDef in pairs(entityDefinitions) do
					local entity = CreateTestEntity(entityDef.name, entityDef.dx, entityDef.dy);
					RegisterCallback_OnEntityDestroyed(entity, OnEntityDestroyed);
				end
			end

			function CreateEntityDefinition(name, dx, dy)
				return {
					name = name,
					dx = dx,
					dy = dy
				}
			end

			function OnEntityDestroyed(entity)
				print("Lua::OnEntityDestroyed - Entity " .. entity .. " has been destroyed.");
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