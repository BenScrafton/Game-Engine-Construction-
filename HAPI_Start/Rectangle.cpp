#include "Rectangle.h"

void Rectangle::RecalculateBounds(Vector2 pos)
{
	TL_Bound = pos;
	TR_Bound = Vector2(TL_Bound.x + width, TL_Bound.y);
	BL_Bound = Vector2(TL_Bound.x, TL_Bound.y + height);
	BR_Bound = Vector2(TL_Bound.x + width, TL_Bound.y + height);
}
