#pragma once

#include <Systems\System.h>

namespace Systems
{
	class StaticVolumeOverlapCallbackSystem : public Systems::System
	{
	public:
		StaticVolumeOverlapCallbackSystem(entt::registry& registry)
			: System(registry)
		{
		}

	protected:
		void OnExecute(float dt) override;
	};
}