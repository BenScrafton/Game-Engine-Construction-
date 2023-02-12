#include "HUD.h"

HUD::HUD()
{
	pos.y = 700;
	pos.x = 350;
}

void HUD::AddScore(int points)
{
	score += points;
}

void HUD::LoseHealth()
{
	healthBar.RemoveHeart();
}

void HUD::ResetScore()
{
	score = 0;
}

void HUD::Reset()
{
	healthBar.Reset();
	ResetScore();
}

void HUD::MemoryClean() {
	healthBar.MemoryClean();
	GameObject::MemoryClean();
}

void HUD::Update()
{	

	//Render the score
	std::string value = std::to_string(score);
	scoreTxt = "SCORE: " + value;
	HAPI.RenderText(0, 0, HAPI_TColour(255, 0, 0), scoreTxt, 40, eBold);
	
	healthBar.Update(); // update the health bar 

	GameObject::Update(); // update base game object to update all components
}


