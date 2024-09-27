#pragma once

#include <MethodHelperMacros.h>
#include <Vector2f.h>

namespace Components
{
	struct PreviousPositionComponent
	{
		Vector2f position;

		METHOD_ToString(PreviousPositionComponent, FIELD_ToString(position));
	};
}