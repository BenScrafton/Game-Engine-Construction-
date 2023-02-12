#include "GameOver.h"

void GameOver::Reset()
{
	gameOver = false;
	SetIsActive(false);
}

void GameOver::Update()
{
	CheckGameOver();

	if(gameOver) //start displaying the game over screen if gameOver
	{
		GameObject::Update();
	}
}

bool GameOver::GetGameOver()
{
	return gameOver;
}

void GameOver::CheckGameOver()
{
	if(!player->GetIsActive())
	{
		SetIsActive(true);
		gameOver = true;
	}
}
