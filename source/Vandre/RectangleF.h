#pragma once

#include <Vector2f.h>

template<typename T>
struct Rectangle
{
	Vector2<T> position;
	Vector2<T> size;

	METHOD_ToString(Rectangle, FIELD_ToString(position), FIELD_ToString(size));

	bool Contains(Vector2<T> p)
	{
		return p.x >= position.x
			&& p.y >= position.y
			&& p.x <= position.x + size.x
			&& p.y <= position.y + size.y;
	}
};

using RectangleF = Rectangle<float>;