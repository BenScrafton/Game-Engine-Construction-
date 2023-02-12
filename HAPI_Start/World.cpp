#include "World.h"

World::World()
{
	HAPI_TSoundOptions options(0.5f, true, 0);
	if (!HAPI.PlaySound("Data\\Sound\\GameTheme.wav", options))
	{
		return;
	}

	SetTag("World");
	this->pos = Vector2(0, -1000);
	HUD* hud = new HUD;

	gameEnd.push_back(hud);
	
	//----------------------------------------LOADMAP_SETUP--------------------------------------------------------
	mapLoader.LoadMap("Data\\level11.txt", SpriteManager::GetSprite("Tile_Grass_Static")->id, hud);
	
	//----------------------------------------BACKGROUND_SETUP-----------------------------------------------------
	GameObject* sky = new GameObject;
	Animator* anim = new Animator(sky);
	anim->CreateNewAnim("Sky_Static");
	sky->components.push_back(anim);
	background.push_back(sky);
	
	//----------------------------------------DEATHZONE_SETUP-----------------------------------------------------
	DeathZone* deathZone = new DeathZone(Vector2(0,2500), 64000, 64000);
	deathZone->SetParent(this);
	this->AddChild(deathZone);
	background.push_back(deathZone);

	//----------------------------------------WINZONE_SETUP-----------------------------------------------------
	gameWinZone.push_back(mapLoader.GetWinZone());
	
	//----------------------------------------PARALAX_SETUP-----------------------------------------------------
	ParalaxBackground* pb = new ParalaxBackground(this, Vector2(0.0f, 600.0f), "Trees1_Static", 0.2f, 100);
	background.push_back(pb);
	
	ParalaxBackground* pb3 = new ParalaxBackground(this, Vector2(0.0f, 650.0f), "Trees3_Static", 0.25f, 100);
	background.push_back(pb3);

	ParalaxBackground* pb2 = new ParalaxBackground(this, Vector2(0.0f, 750.0f), "Trees2_Static", 0.3f, 100);
	background.push_back(pb2);


	//----------------------------------------TILES_SETUP-----------------------------------------------------
	tiles = mapLoader.GetTiles();
	
	//----------------------------------------BULLETS_SETUP-----------------------------------------------------
	bullets = mapLoader.GetBullets();

	//----------------------------------------CHARACTERS_SETUP--------------------------------------------------
	players = mapLoader.GetPlayers();
	enemies = mapLoader.GetEnemies();

	//----------------------------------------HUD_SETUP---------------------------------------------------------
	GameOver* gO = new GameOver((Player*)players[0]); //GameOver Screen
	gameOver = gO;
	gameEnd.push_back(gameOver);
	

	GameWin* gW = new GameWin((Player*)players[0]);//GameWin Screen
	gameWin = gW;
	gameEnd.push_back(gameWin);

	
	//----------------------------------------LAYERS_SETUP------------------------------------------------------
	layers.push_back(background);
	layers.push_back(tiles);
	layers.push_back(gameWinZone);
	layers.push_back(bullets);
	layers.push_back(enemies);
	layers.push_back(players);
	layers.push_back(gameEnd);

	HAPI.SetShowFPS(true, 0, 0);
}

void World::MemoryClean()
{
	for (std::vector<GameObject*> layer : layers)
	{
		for (GameObject* gameObject : layer)
		{
			gameObject->MemoryClean();
			delete gameObject;
		}
	}

	mapLoader.MemoryClean();
}

void World::CheckGameOver()
{
	if(gameOver->GetGameOver() || gameWin->GetGameWin())
	{
		const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

		if(keyData.scanCode['R'])
		{
			Reset();
		}

		const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

		if (controllerData.digitalButtons[HK_DIGITAL_B])
		{
			Reset();
		}
	}
}

void World::Reset()
{
	for(GameObject* player : players)
	{
		player->Reset();
	}

	for(GameObject* enemy : enemies)
	{
		enemy->Reset();
	}

	for(GameObject* gameObject : gameEnd)
	{
		gameObject->Reset();
	}

	for(GameObject* gameObject : gameWinZone)
	{
		gameObject->Reset();
	}
}

void World::Update()
{
	CheckGameOver();

	//World is moved to centre around the player acting as a camera

	//----------------------------------------CAMERA_CALCULATIONS------------------------------------------------------
	if(!((Player*)players[0])->GetIsDead())
	{
		int cameraSpeed = 500;

		#if defined _DEBUG
			cameraSpeed = 250;
		#endif


		if ((screenWidth / 2.0f) < players[0]->pos.x - 10)
		{
			pos.x -= cameraSpeed * Time::GetDeltaTime();
		}
		else if ((screenWidth / 2.0f) > players[0]->pos.x + 10)
		{
			pos.x += cameraSpeed * Time::GetDeltaTime();
		}

		if ((screenHeight / 2.0f) < players[0]->pos.y - 100)
		{
			pos.y -= cameraSpeed * Time::GetDeltaTime();
		}
		else if (((screenHeight / 2.0f) > players[0]->pos.y + 100))
		{
			pos.y += cameraSpeed * Time::GetDeltaTime();
		}
	}
	GameObject::Update();


	//----------------------------------------UPDATE_LAYERS------------------------------------------------------
	for(std::vector<GameObject*> layer : layers)
	{
		for(GameObject* gameObject : layer)
		{
			gameObject->Update();
		}
	}


}
