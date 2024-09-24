#pragma once

#include <Systems/System.h>

namespace Components
{
	struct NextPositionComponent;
	struct PositionComponent;
	struct VelocityComponent;
}

namespace Systems
{
	class PositionUpdateSystem : public System
	{
	public:
		PositionUpdateSystem(entt::registry& registry)
			: System{ registry }
		{
		}

	protected:
		void OnExecute(float dt) override;

	private:
		void TickEntity(
			float dt,
			std::string_view entityName,
			Components::NextPositionComponent& nextPos,
			const Components::PositionComponent& pos,
			const Components::VelocityComponent& vel
		);
	};
}