#pragma once

#include <MethodHelperMacros.h>

namespace Components
{
	struct NameComponent
	{
		std::string name;

		METHOD_ToString(NameComponent, FIELD_ToString(name));
	};
}