#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bullet.h"
#include "WinZone.h"

class MapLoader
{
private:
	GameObject* world = nullptr;
	std::vector<GameObject*> tiles;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> players;
	std::vector<GameObject*> bullets;
	GameObject* winZone = nullptr;

	int levelWidth = 0;
	bool calculatedLevelWidth = false;
public:

	MapLoader(GameObject* p_world)
	{
		world = p_world;
	}
	void LoadMap(std::string filepath, std::string spriteSheetID, HUD* hud);
	void LoadCharacters(std::vector<Vector2> player_pos, std::vector<Vector2> enemy_pos, Vector2 winZone_pos, HUD* hud);
	int CalculateTileIndex(std::string& line, int i);	
	std::vector<GameObject*> GetTiles();
	std::vector<GameObject*> GetPlayers();
	std::vector<GameObject*> GetEnemies();
	std::vector<GameObject*> GetBullets();
	GameObject* GetWinZone();
	int GetLevelWidth();
	void MemoryClean();
};

