#pragma once
#include <iostream>
#include "Vector2.h"

class Rectangle
{
public:
	Vector2 TL_Bound; // Also acts as the position
	Vector2 BL_Bound;

	Vector2 TR_Bound;
	Vector2 BR_Bound;

	float width;
	float height;

	Rectangle(Vector2 p_topLeftPos = Vector2(0,0), float p_width = 0.0f, float p_height = 0.0f)
	{
		width = p_width;
		height = p_height;

		TL_Bound = p_topLeftPos;
		TR_Bound = Vector2(TL_Bound.x + width, TL_Bound.y);
		
		BL_Bound = Vector2(TL_Bound.x, TL_Bound.y + height);
		BR_Bound = Vector2(TL_Bound.x + width, TL_Bound.y + height);	
	}

	void RecalculateBounds(Vector2 pos);

private:

};

