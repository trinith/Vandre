#pragma once

#include <entt.hpp>
#include <string>

#if defined(ENTITY_NAME_CHECK)
#include <Components/NameComponent.h>
#endif

namespace EntityUtils
{
	inline std::string GetEntityName(const entt::registry& registry, entt::entity entity)
	{
#if defined(ENTITY_NAME_CHECK)
		if (registry.any_of<Components::NameComponent>(entity))
			return "Entity{" + registry.get<const Components::NameComponent>(entity).name + "}";
#endif

		return "Entity{" + std::to_string(static_cast<uint32_t>(entity)) + "}";
	}
}