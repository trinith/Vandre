#pragma once

#include <optional>
#include <Vector2f.h>
#include <Systems/System.h>

namespace Components
{
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
			entt::registry& registry,
			entt::entity entity,
			const Components::PositionComponent& positionComponent,
			const Components::VelocityComponent& velocityComponent
		);
	};
}