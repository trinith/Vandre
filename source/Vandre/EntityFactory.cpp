#include "EntityFactory.h"

#include <Components/NameComponent.h>
#include <Components/PositionComponent.h>
#include <Components/StaticVolumeComponent.h>
#include <Components/VelocityComponent.h>

entt::entity EntityFactory::CreateDynamicEntity(entt::registry& registry, std::string_view name, Vector2f position, Vector2f velocity)
{
	using namespace Components;

	const entt::entity entity = registry.create();

	registry.emplace<NameComponent>(entity, std::string{ name });
	registry.emplace<PositionComponent>(entity, position);
	registry.emplace<VelocityComponent>(entity, velocity);

	return entity;
}

entt::entity EntityFactory::CreateStaticVolumeEntity(entt::registry& registry, std::string_view name, RectangleF bounds)
{
	using namespace Components;

	const entt::entity entity = registry.create();
	registry.emplace<NameComponent>(entity, std::string{ name });
	registry.emplace<StaticVolumeComponent>(entity, bounds);

	return entity;
}