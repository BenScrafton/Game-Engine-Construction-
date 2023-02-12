#pragma once
#include <HAPI_lib.h>
#include "Renderer.h"
#include "Component.h"
#include "SpriteManager.h"
#include "Time.h"
#include <string>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

struct animation //the data structure for a single animation
{
	std::string spriteSheetID; //Reference to the sprite manager

	float animDuration;
	int currentFrame = 0;
	int defaultFrame = 0;
	float currentTimer = 0; 
};

class Animator:
	public Component
{
public:
	int screenWidth=1024;
	int screenHeight=768;

	std::vector<animation> animations;
	int currentAnimIndex = 0;

	float time = 0;

	Animator(GameObject* gameObject)
	{
		m_gameObject = gameObject;
		id = typeid(this).name();
	}

	void FlipHorizontal(bool flipState);
	void CreateNewAnim(std::string spriteSheetID, float animDuration = 0);
	void Render(int posX, int posY, int animIndex);
	
	void SetCurFrame(int curFrameIndex);
	void SetDefaultFrame(int defaultFrameIndex);
	void SetAnimIndex(int index);
	bool GetInverted();
	void Process();

private:
	bool inverted = false;
};

