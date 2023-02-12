#include "MapLoader.h"

void MapLoader::LoadMap(std::string filepath, std::string spriteSheetID, HUD* hud)
{	
	//all game objects are parented to the world so when the world moves so does everything else

	tiles.clear();

	SpriteSheet* spriteSheet = SpriteManager::GetSprite(spriteSheetID);

	std::fstream mapFile;
	mapFile.open(filepath);
	if(mapFile.is_open())
	{
		std::string line;
		int lineCount = 0;
		std::string curVal;

		std::vector<Vector2> enemy_pos;
		std::vector<Vector2> player_pos;
		Vector2 winZone_pos;

		while(std::getline(mapFile, line))
		{
			int tileCount = 0;
			curVal = "";

			for (size_t i = 0; i < line.length(); i++) // loop through txt file line by line creating tiles in the corresponding positions
			{
				if(line[i] == ',')
				{
					if(lineCount > 0)
					{
						levelWidth++;
					}

					Vector2 tile_pos = Vector2((float)(tileCount * spriteSheet->spriteWidth), (float)(lineCount * spriteSheet->spriteHeight));

					if(curVal == "0e")//enemy
					{
						enemy_pos.push_back(tile_pos);
					}
					else if(curVal == "0p")//player
					{
						player_pos.push_back(tile_pos);
					}
					else if(curVal == "0w")//win zone
					{
						winZone_pos = Vector2(tile_pos);
					}
					else//tile
					{
						bool isCollider = false;

						if (curVal.back() == 'c')
						{
							isCollider = true;
							curVal.pop_back();
						}

						if (stoi(curVal) > 0)
						{
							Tile* tile = new Tile(tile_pos, spriteSheetID, stoi(curVal) - 1, isCollider);

							tile->SetParent(world);
							world->AddChild(tile);
							tiles.push_back(tile);

							if(isCollider)
							{
								tile->GetComponentOfType<Collider>()->SetIsStatic(true);
							}

						}
					}


					tileCount++;
					curVal = "";
				}
				else
				{
					curVal = curVal + line[i];
				}
			}
			lineCount++;
		}

		LoadCharacters(player_pos, enemy_pos, winZone_pos, hud);
	}
	else
	{
		std::cout << "NOT LOADED" << std::endl;
	}
}

void MapLoader::LoadCharacters(std::vector<Vector2> player_pos, std::vector<Vector2> enemy_pos, Vector2 winZone_pos, HUD* hud)
{

	for (size_t i = 0; i < 100; i++) // load bullets
	{
		Bullet* bullet = new Bullet(hud);
		bullet->SetParent(world); 
		world->AddChild(bullet);
		bullets.push_back(bullet);
	}

	for(Vector2 pos : player_pos)// load players
	{
		Player* player = new Player(bullets, pos, hud);
		player->SetParent(world);
		world->AddChild(player);
		players.push_back(player);
	}

	int i = 0;

	for (Vector2 pos : enemy_pos)// load enemies
	{
		Enemy* enemy = new Enemy(bullets, pos, players[0]);
		enemy->SetParent(world);
		world->AddChild(enemy);
		enemies.push_back(enemy);
	}

	winZone = new WinZone(winZone_pos, 64, 64, players[0]);// load winzone
	winZone->SetParent(world);
	world->AddChild(winZone);
}

int MapLoader::CalculateTileIndex(std::string& line, int index)
{
	int tileIndex = 0;

	if (line[index] != 0)
	{
		std::string sNum{ line[index], line[index + 1] };
		tileIndex = std::stoi(sNum);
	}
	else
	{
		std::string sNum{ line[index + 1] };
		tileIndex = std::stoi(sNum);
	}
	return tileIndex;
}

std::vector<GameObject*> MapLoader::GetTiles()
{
	return tiles;
}

std::vector<GameObject*> MapLoader::GetPlayers()
{
	return players;
}

std::vector<GameObject*> MapLoader::GetEnemies()
{
	return enemies;
}

std::vector<GameObject*> MapLoader::GetBullets()
{
	return bullets;
}

GameObject* MapLoader::GetWinZone()
{
	return winZone;
}

int MapLoader::GetLevelWidth()
{
	return levelWidth;
}

void MapLoader::MemoryClean()
{
	std::cout << "Clean map" << std::endl;
}