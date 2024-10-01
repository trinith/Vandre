#pragma once

#include <sol/sol.hpp>

namespace Components
{
	struct OnEntityDestroyedLuaCallbackComponent
	{
		std::vector<sol::function> callbacks;
	};
}