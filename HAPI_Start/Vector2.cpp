#include "Vector2.h"

void Vector2::CalcMagnitude()
{
	magnitude = (float) (sqrt((x * x) + (y * y)));
}

void Vector2::Normalise()
{
	CalcMagnitude();

	x = x / magnitude;
	y = y / magnitude;
}
