#pragma once
#include <HAPI_lib.h>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "MapLoader.h"
#include "Bullet.h"
#include "HUD.h"
#include "ParalaxBackground.h"
#include "GameOver.h"
#include "GameWin.h"
#include "DeathZone.h"
#include "WinZone.h"

class World :
    public GameObject
{
private:
    int screenWidth{ 1024 };
    int screenHeight{768};

    GameOver* gameOver = nullptr;
    GameWin* gameWin = nullptr;

    float fakePosX = 0;
     MapLoader mapLoader = MapLoader(this);
    std::vector<GameObject*> gameObjects;

    std::vector<std::vector<GameObject*>> layers;

    std::vector<GameObject*> background;
    std::vector<GameObject*> foreground;
    std::vector<GameObject*> midground;

    std::vector<GameObject*> tiles;
    std::vector<GameObject*> bullets;
    std::vector<GameObject*> players;
    std::vector<GameObject*> enemies;
    std::vector<GameObject*> gameEnd;
    std::vector<GameObject*> gameWinZone;
    float tCount = 0;
    int fps = 0;

public:

    World();
    void MemoryClean();
    void CheckGameOver();
    void Reset();
    void Update();
};

