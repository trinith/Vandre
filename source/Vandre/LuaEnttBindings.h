#pragma once

#include <entt.hpp>
#include <sol/sol.hpp>

class LuaEnttBindings
{
public:
	static void Initialize(sol::state& lua, entt::registry& registry)
	{
		SetupEntityCreateFunctions(lua, registry);
		SetupEntityUtilityFunctions(lua, registry);
		SetupCallbackFunctions(lua, registry);
	}

private:
	static void SetupEntityCreateFunctions(sol::state& lua, entt::registry& registry);
	static void SetupEntityUtilityFunctions(sol::state& lua, entt::registry& registry);
	static void SetupCallbackFunctions(sol::state& lua, entt::registry& registry);
};