#pragma once

#include <Systems/System.h>

namespace Components
{
	struct PositionComponent;
	struct NextPositionComponent;
}

namespace Systems
{
	class PositionFinalizeSystem : public System
	{
	public:
		PositionFinalizeSystem(entt::registry& registry)
			: System{ registry }
		{
		}

	protected:
		void OnExecute(float dt) override;

	private:
		void TickEntity(
			float dt,
			entt::entity entity,
			std::string_view entityName,
			Components::PositionComponent& pos,
			const Components::NextPositionComponent& nextPos
		);
	};
}