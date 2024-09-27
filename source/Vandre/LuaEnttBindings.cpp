#include <LuaEnttBindings.h>

#include <EntityFactory.h>
#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components\OnEntityDestroyedLuaCallbackComponent.h>
#include <Components\OnVolumeOverlapLuaCallbackComponent.h>
#include <Components\DestroyEntityComponent.h>

namespace
{
	inline static bool IsEntityValid(std::string_view functionName, const entt::registry& registry, entt::entity entity)
	{
		if (!registry.valid(entity))
		{
			Logger::WriteLine(functionName, " - Invalid entity.");
			return false;
		}

		return true;
	}

	inline static bool IsCallbackValid(std::string_view functionName, sol::function callback)
	{
		if (!callback)
		{
			Logger::WriteLine("RegisterCallback_OnVolumeEntered - Empty callback.");
			return false;
		}

		return true;
	}
}

void LuaEnttBindings::SetupEntityCreateFunctions(sol::state& lua, entt::registry& registry)
{
	lua["CreateDynamicEntity"] =
		[&registry](const std::string& entityName, float x, float y, float dx, float dy)
		{
			return EntityFactory::CreateDynamicEntity(registry, entityName, { x, y }, { dx, dy });
		};

	lua["CreateStaticVolumeEntity"] =
		[&registry](const std::string& volumeName, float x, float y, float w, float h)
		{
			return EntityFactory::CreateStaticVolumeEntity(registry, volumeName, RectangleF{ x, y, w, h });
		};
}

void LuaEnttBindings::SetupEntityUtilityFunctions(sol::state& lua, entt::registry& registry)
{
	lua["GetEntityName"] =
		[&registry](const uint32_t entityId)
		{
			return EntityUtils::GetEntityName(registry, static_cast<entt::entity>(entityId));
		};

	lua["DestroyEntity"] =
		[&registry](const uint32_t entityId)
		{
			entt::entity entity = static_cast<entt::entity>(entityId);
			if (registry.valid(entity))
				registry.emplace_or_replace<Components::DestroyEntityComponent>(entity);
		};
}

void LuaEnttBindings::SetupCallbackFunctions(sol::state& lua, entt::registry& registry)
{
	lua["RegisterCallback_OnEntityDestroyed"] =
		[&registry](const entt::entity entity, sol::function callback)
		{
			if (!IsEntityValid("RegisterCallback_OnEntityDestroyed", registry, entity))
				return;

			if (!IsCallbackValid("RegisterCallback_OnEntityDestroyed", callback))
				return;

			registry.emplace_or_replace<Components::OnEntityDestroyedLuaCallbackComponent>(entity, callback);
			Logger::WriteLine("RegisterCallback_OnEntityDestroyed - Successfully registered callback.");
		};

	lua["RegisterCallback_OnVolumeEntered"] =
		[&registry](const entt::entity volumeEntity, sol::function callback)
		{
			if (!IsEntityValid("RegisterCallback_OnVolumeEntered", registry, volumeEntity))
				return;

			if (!IsCallbackValid("RegisterCallback_OnVolumeEntered", callback))
				return;

			auto& volumeOverlapComponent = registry.get_or_emplace<Components::OnVolumeOverlapLuaCallbackComponent>(volumeEntity);
			volumeOverlapComponent.enterCallbacks.emplace_back(std::move(callback));
			Logger::WriteLine("RegisterCallback_OnVolumeEntered - Successfully registered callback.");
		};

	lua["RegisterCallback_OnVolumeExited"] =
		[&registry](const entt::entity volumeEntity, sol::function callback)
		{
			if (!IsEntityValid("RegisterCallback_OnVolumeExited", registry, volumeEntity))
				return;

			if (!IsCallbackValid("RegisterCallback_OnVolumeExited", callback))
				return;

			auto& volumeOverlapComponent = registry.get_or_emplace<Components::OnVolumeOverlapLuaCallbackComponent>(volumeEntity);
			volumeOverlapComponent.exitCallbacks.emplace_back(std::move(callback));
			Logger::WriteLine("RegisterCallback_OnVolumeExited - Successfully registered callback.");
		};
}