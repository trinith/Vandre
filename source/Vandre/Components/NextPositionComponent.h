#pragma once

#pragma once

#include <MethodHelperMacros.h>
#include <Vector2f.h>

namespace Components
{
	struct NextPositionComponent
	{
		Vector2f position;

		METHOD_ToString(NextPositionComponent, FIELD_ToString(position));
	};
}