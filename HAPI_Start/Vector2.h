#pragma once
#include <math.h>  
class Vector2
{
public:
	float x;
	float y;

	float magnitude = 0.0f; 

	Vector2(float xVal = 0, float yVal = 0)
	{
		x = xVal;
		y = yVal;
	}

	void CalcMagnitude();
	void Normalise();
};

