#pragma once

#include <any>
#include <optional>
#include <string>
#include <unordered_map>

class DependencyContainer
{
public:
	template <typename TType, typename... TArgs>
	std::optional<std::reference_wrapper<TType>> AddComponent(TArgs&&... args)
	{
		std::any item = TType{ std::forward<TArgs>(args)... };
		auto emplaceResult = _components.try_emplace(item.type().name(), std::move(item));
		if (emplaceResult.second)
		{
			TType& emplacedItem = std::any_cast<TType&>(emplaceResult.first->second);
			return emplacedItem;
		}

		return std::nullopt;
	}

	template <typename TType>
	std::optional<std::reference_wrapper<TType>> GetComponent()
	{
		auto findResult = _components.find(typeid(TType).name());
		if (findResult != _components.end())
		{
			TType& item = std::any_cast<TType&>(findResult->second);
			return item;
		}

		return std::nullopt;
	}

private:
	std::unordered_map<std::string, std::any> _components;
};