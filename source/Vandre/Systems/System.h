#pragma once

#include <entt.hpp>

namespace Systems
{
	class System
	{
	public:
		System(entt::registry& registry)
			: _registry{ registry }
		{
		}

		void Execute(float dt)
		{
			OnExecute(dt);
		}

		entt::registry& GetRegistry() { return _registry; }
		const entt::registry& GetRegistry() const { return _registry; }

	protected:
		virtual void OnExecute(float dt) = 0;

	private:
		entt::registry& _registry;
	};
}