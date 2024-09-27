#pragma once

#include <sol/sol.hpp>

namespace Components
{
	struct OnEntityDestroyedLuaCallbackComponent
	{
		sol::function _luaCallback;
	};
}