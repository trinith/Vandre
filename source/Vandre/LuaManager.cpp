#include <LuaManager.h>

void LuaManager::Execute(std::string_view scriptString)
{
	_lua.script(scriptString);
}

void LuaManager::ExecuteFile(const char* scriptFile)
{
	_lua.script_file(scriptFile);
}

void LuaManager::CallLuaFunction(const char* luaFunction)
{
	if (!_lua[luaFunction].valid())
		throw std::runtime_error{ (std::stringstream{} << "Function " << luaFunction << " not found.").str() };

	auto result = _lua[luaFunction].call();
	if (!result.valid())
	{
		sol::error err = result;
		throw std::runtime_error{ (std::stringstream{} << "Call to " << luaFunction << " failed.\n" << err.what()).str() };
	}
}