#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Explosion.h"

class GameWin :
    public GameObject
{
private:
    Player* player;
    Explosion* explosion;
    bool gameWin = false;

public:
    GameWin(Player* p_player)
    {
        player = p_player;
        pos.y = 250;

        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
        Animator* animator = new Animator(this);
        animator->CreateNewAnim("GameWin_Static");
        components.push_back(animator);

        //----------------------------------------Explosion_SETUP----------------------------------------------------
        explosion = new Explosion();

        SetIsActive(false);
    }

    void MemoryClean();
    void Reset();
    void Update();
    bool GetGameWin();
    void CheckGameWin();
};

