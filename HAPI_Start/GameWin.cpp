#include "GameWin.h"

void GameWin::MemoryClean()
{
	explosion->MemoryClean();
	delete explosion;
	GameObject::MemoryClean();
}

void GameWin::Reset()
{
	gameWin = false;
	explosion->Reset();
	SetIsActive(false);

}

void GameWin::Update()
{
	CheckGameWin();

	if (gameWin) //display win screen when gameWin is true
	{
		explosion->Update();
		GameObject::Update();
	}
}

bool GameWin::GetGameWin()
{
	return gameWin;
}

void GameWin::CheckGameWin()
{
	if(player->GetHasWon() && gameWin == false) //if the player has won Activate game win
	{
		explosion->SetIsActive(true);
		SetIsActive(true);
		gameWin = true;
	}
}


