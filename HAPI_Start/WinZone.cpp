#include "WinZone.h"

void WinZone::Update()
{
	Rectangle rect = player->GetComponentOfType<Collider>()->boundingBox;

	if(GetComponentOfType<Collider>()->CheckCollisionSingle(rect))
	{
		const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
		if (keyData.scanCode['E']) // activate the win condition
		{
			activated = true;
		}
	}

	if(activated)
	{
		ProcessActivation();
	}

	GameObject::Update(); //update the base game object to update all components
}

void WinZone::Reset()
{
	activated = false;
	GetComponentOfType<Animator>()->currentAnimIndex = 0;
	timeSinceAnim = 0;
}

void WinZone::ProcessActivation()
{
	GetComponentOfType<Animator>()->currentAnimIndex = 1; //change the animation

	timeSinceAnim += Time::GetDeltaTime();
	if(timeSinceAnim >= animLength - 0.4)//set win when the animation is complete
	{
		player->GameWin();
	}
}

