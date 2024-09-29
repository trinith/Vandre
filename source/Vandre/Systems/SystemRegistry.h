#pragma once

#include <entt.hpp>
#include <vector>
#include <Systems/System.h>

namespace Systems
{
	class SystemRegistry
	{
	public:
		SystemRegistry() = default;

		SystemRegistry(const SystemRegistry&) = delete;
		SystemRegistry& operator=(const SystemRegistry&) = delete;

		SystemRegistry(SystemRegistry&& other) noexcept
			: _systems{ std::move(other._systems) }
		{
		}

		SystemRegistry& operator=(SystemRegistry&& other) noexcept
		{
			_systems = std::move(other._systems);
			return *this;
		}

		template <typename TSystem, typename... TArgs>
		void RegisterSystem(TArgs&&... args)
		{
			static_assert(std::is_base_of<System, TSystem>::value, "TSystem must inherit from Systems::System.");
			_systems.emplace_back(std::make_unique<TSystem>(std::forward<TArgs>(args)...));
		}

		void TickSystems(float dt) const
		{
			for (auto& system : _systems)
				system->Execute(dt);
		}

	private:
		std::vector<std::unique_ptr<System>> _systems;
	};
}