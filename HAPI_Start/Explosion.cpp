#include "Explosion.h"

void Explosion::Reset()
{
	timeSinceExplosion = 0;

	SetIsActive(false);
	GetComponentOfType<Animator>()->SetAnimIndex(0);
}

void Explosion::Update()
{
	if(GetIsActive())
	{
		if(timeSinceExplosion == 0)
		{
			HAPI_TSoundOptions options(2.0f, false, 0);
			if (!HAPI.PlaySound("Data\\Sound\\explosion_sound.wav", options))
			{
				return;
			}
		}

		timeSinceExplosion += Time::GetDeltaTime(); //increment timer

		if(timeSinceExplosion > explosionLength)
		{
			GetComponentOfType<Animator>()->SetAnimIndex(1);//change the animation after the 1st explosion anim is complete
		}

		GameObject::Update(); //update the base gameObject to update all the components
	}
}
