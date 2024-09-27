#pragma once

#include <entt.hpp>
#include <string_view>

#include <Vector2f.h>
#include <RectangleF.h>

class EntityFactory
{
public:
	static entt::entity CreateDynamicEntity(entt::registry& registry, std::string_view name, Vector2f position, Vector2f velocity);
	static entt::entity CreateStaticVolumeEntity(entt::registry& registry, std::string_view name, RectangleF bounds);
};