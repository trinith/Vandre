#pragma once

#include <entt.hpp>
#include <vector>
#include <sol/sol.hpp>

namespace Components
{
	struct OnVolumeOverlapLuaCallbackComponent
	{
		std::vector<sol::function> enterCallbacks;
		std::vector<sol::function> exitCallbacks;

		void FireEnterCallbacks(entt::entity volumeEntity, entt::entity entity) const
		{
			for (auto& callback : enterCallbacks)
				callback(volumeEntity, entity);
		}

		void FireExitCallbacks(entt::entity volumeEntity, entt::entity entity) const
		{
			for (auto& callback : exitCallbacks)
				callback(volumeEntity, entity);
		}
	};
}