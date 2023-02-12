#pragma once
#include "GameObject.h"
class ParalaxBackground :
    public GameObject
{
private:
	std::vector<GameObject*> backgrounds;
	int repeatDist;

public:
	ParalaxBackground(GameObject* world, Vector2 initPos, std::string spriteID, float moveRate, int levelWidth)
    {
		pos = initPos;
		SetParent(world);
		world->AddChild(this);

		repeatDist = (SpriteManager::GetSprite(spriteID)->spriteSheetWidth);
		int numBackgrounds = ((levelWidth * 64) / repeatDist) + 1;

		//----------------BG----------------
		for (size_t i = 0; i < numBackgrounds; i++) // create and place backgrounds next to each other for the length of the level 
		{
			GameObject* bg = new GameObject();

			bg->pos.x = (float)(1200.0f * i);
			bg->SetParent(this);
			AddChild(bg);

			//----------------------------------------ANIMATORS_SETUP----------------------------------------------------
			Animator* a1 = new Animator(bg);
			a1->CreateNewAnim(spriteID);
			bg->components.push_back(a1);

			//----------------------------------------PARALAX_SETUP----------------------------------------------------
			Paralax* p1 = new Paralax(moveRate, bg);
			bg->components.push_back(p1);
			backgrounds.push_back(bg);
		}

    }

	void MemoryClean() {
		for (GameObject* bg : backgrounds) {
			bg->MemoryClean();
			delete bg;
		}
		GameObject::MemoryClean();
	}

	void Update();
};

