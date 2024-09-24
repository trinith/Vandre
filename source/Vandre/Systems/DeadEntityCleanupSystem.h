#pragma once

#include <Systems/System.h>

namespace Systems
{
	class DeadEntityCleanupSystem : public System
	{
	public:
		DeadEntityCleanupSystem(entt::registry& registry)
			: System{ registry }
		{
		}

	protected:
		void OnExecute(float dt) override;
	};
}