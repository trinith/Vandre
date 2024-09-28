#pragma once

#include <sol/sol.hpp>

class LuaManager
{
public:
	template<typename... TLibraries>
	LuaManager(TLibraries&&... libraries)
	{
		_lua.open_libraries(std::forward<TLibraries>(libraries)...);
	}

	LuaManager(const LuaManager&) = delete;
	LuaManager& operator=(const LuaManager&) = delete;

	LuaManager(LuaManager&&) noexcept;
	LuaManager& operator=(LuaManager&&) noexcept;

	sol::state& GetState() { return _lua; }
	const sol::state& GetState() const { return _lua; }

	void Execute(std::string_view scriptString);
	void ExecuteFile(const char* scriptFile);
	void CallLuaFunction(const char* luaFunction);
private:
	sol::state _lua;
};