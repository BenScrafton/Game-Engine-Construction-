#include "ParalaxBackground.h"
void ParalaxBackground::Update()
{
	for(GameObject* bg : backgrounds)
	{
		bg->Update();
	}

	GameObject::Update();// update base game object to update all components
}


