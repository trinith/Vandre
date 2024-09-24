#pragma once

#include <MethodHelperMacros.h>

namespace Components
{
	struct VelocityComponent
	{
		Vector2f velocity{ 0.f, 0.f };

		METHOD_ToString(VelocityComponent, FIELD_ToString(velocity));
	};
}