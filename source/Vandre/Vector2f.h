#pragma once

#include <MethodHelperMacros.h>

template <typename TType>
struct Vector2
{
	TType x;
	TType y;

	METHOD_ToString(Vector2, FIELD_ToString(x), FIELD_ToString(y));
};

using Vector2f = Vector2<float>;
