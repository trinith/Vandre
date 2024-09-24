#pragma once

#include <string>
#include <sstream>

template <typename TType>
static inline void AppendField(std::ostream& os, std::string_view fieldName, TType fieldValue)
{
	os << fieldName << "=" << fieldValue;
}

template <typename... TArgs, typename TType>
static inline void AppendField(std::ostream& os, std::string_view fieldName, TType fieldValue, TArgs... args)
{
	AppendField(os, fieldName, fieldValue);
	os << ", ";
	AppendField(os, args...);
}

#define FIELD_ToString(fieldName) #fieldName, fieldName

#define METHOD_ToString(classname, ...) \
	std::string ToString() const \
	{ \
		std::stringstream ss; \
		ss << "{"; \
		AppendField(ss, __VA_ARGS__); \
		ss << "}"; \
		return ss.str(); \
	} \
	\
	friend std::ostream& operator<<(std::ostream& os, const classname& obj) \
	{ \
		return os << obj.ToString(); \
	}
