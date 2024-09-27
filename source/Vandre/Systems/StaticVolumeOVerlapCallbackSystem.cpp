#include "StaticVolumeOverlapCallbackSystem.h"

#include <EntityUtils.h>
#include <VandreLogging.h>
#include <Components/OnVolumeOverlapLuaCallbackComponent.h>
#include <Components/PositionComponent.h>
#include <Components/PreviousPositionComponent.h>
#include <Components/StaticVolumeComponent.h>

namespace Systems
{
	void StaticVolumeOverlapCallbackSystem::OnExecute(float dt)
	{
		Logger::WriteLine("StaticVolumeOverlapCallbackSystem::OnExecute");

		auto& registry = GetRegistry();
		auto staticVolumeView = registry.view<const Components::StaticVolumeComponent, const Components::OnVolumeOverlapLuaCallbackComponent>();
		auto movedEntitiesView = registry.view<const Components::PositionComponent, const Components::PreviousPositionComponent>();

		for (auto volumeEntity : staticVolumeView)
		{
			auto volumeIndent = Logger::CreateIndentScope();
			const std::string volumeName = EntityUtils::GetEntityName(registry, volumeEntity);
			Logger::WriteLine("Checking ", volumeName, " for entity overlap...");

			RectangleF volumeBounds = staticVolumeView.get<const Components::StaticVolumeComponent>(volumeEntity).bounds;
			const Components::OnVolumeOverlapLuaCallbackComponent& callbackComponent = staticVolumeView.get<Components::OnVolumeOverlapLuaCallbackComponent>(volumeEntity);

			for (auto movedEntity : movedEntitiesView)
			{
				auto entityIndent = Logger::CreateIndentScope();
				const std::string movedEntityName = EntityUtils::GetEntityName(registry, movedEntity);
				Logger::WriteLine("Checking ", movedEntityName, "...");

				const Vector2f& currentPos = movedEntitiesView.get<const Components::PositionComponent>(movedEntity).position;
				const Vector2f& previousPos = movedEntitiesView.get<const Components::PreviousPositionComponent>(movedEntity).position;

				if (!volumeBounds.Contains(previousPos) && volumeBounds.Contains(currentPos))
				{
					auto _ = Logger::CreateIndentScope();
					Logger::WriteLine(movedEntityName, " has entered ", volumeName, ", firing callbacks.");
					callbackComponent.FireEnterCallbacks(volumeEntity, movedEntity);
				}

				if (volumeBounds.Contains(previousPos) && !volumeBounds.Contains(currentPos))
				{
					auto _ = Logger::CreateIndentScope();
					Logger::WriteLine(movedEntityName, " has exited ", volumeName, ", firing callbacks.");
					callbackComponent.FireExitCallbacks(volumeEntity, movedEntity);
				}
			}
		}
	}
}