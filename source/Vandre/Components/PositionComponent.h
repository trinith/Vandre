#pragma once

#include <MethodHelperMacros.h>
#include <Vector2f.h>

namespace Components
{
	struct PositionComponent
	{
		Vector2f position;

		METHOD_ToString(PositionComponent, FIELD_ToString(position));
	};
}