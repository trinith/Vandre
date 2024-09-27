#define SOL_ALL_SAFETIES_ON 1

#include <entt.hpp>
#include <sol/sol.hpp>

#include <LuaEnttBindings.h>
#include <LuaManager.h>
#include <VandreLogging.h>

#include <Systems/DeadEntityCleanupSystem.h>
#include <Systems/PositionFinalizeSystem.h>
#include <Systems/PositionUpdateSystem.h>
#include <Systems/StaticVolumeOverlapCallbackSystem.h>
#include <Systems/SystemRegistry.h>

int main()
{
	Logger::WriteLine("Starting...");

	entt::registry registry;

	LuaManager luaManager{sol::lib::base};
	LuaEnttBindings::Initialize(luaManager.GetState(), registry);

	try
	{
		luaManager.ExecuteFile("scripts/test_script.lua");
		luaManager.CallLuaFunction("_init");
	}
	catch (const std::exception& e)
	{
		Logger::WriteLine(e.what());
	}

	Systems::SystemRegistry systemRegistry;
	systemRegistry.RegisterSystem<Systems::PositionUpdateSystem>(registry);
	systemRegistry.RegisterSystem<Systems::PositionFinalizeSystem>(registry);
	systemRegistry.RegisterSystem<Systems::StaticVolumeOverlapCallbackSystem>(registry);
	systemRegistry.RegisterSystem<Systems::DeadEntityCleanupSystem>(registry);

	Logger::WriteLine("BEGIN - Tick Simulation");
	{
		auto tickSimulationScope = Logger::CreateIndentScope();
		for (int i = 0; i < 4; i++)
		{
			Logger::WriteLine("BEGIN - Tick ", i);
			{
				auto tickScope = Logger::CreateIndentScope();
				systemRegistry.TickSystems(1.f);
			}
			Logger::WriteLine("END - Tick ", i);
		}
	}
	Logger::WriteLine("END - Tick Simulaton");

	return 0;
}