#pragma once
#include "GameObject.h"
#include "Player.h"

class GameOver :
    public GameObject
{
private:
    Player* player;
    bool gameOver = false;

public:
    GameOver(Player* p_player)
    {
        player = p_player;
        pos.y = 250;

        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
        Animator* animator = new Animator(this);
        animator->CreateNewAnim("GameOver_Static");
        components.push_back(animator);

        SetIsActive(false);
    }

    void Reset();
    void Update();
    bool GetGameOver();
    void CheckGameOver();
};

