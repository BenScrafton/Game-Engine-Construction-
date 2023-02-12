#pragma once
#include "GameObject.h"
#include "HealthBar.h"
#include <string>
#include <fstream>
#include <sstream>

class HUD :
    public GameObject
{
private:
    HealthBar healthBar;
    int score = 0;
    std::string scoreTxt;

public:
    HUD();

    ~HUD() noexcept = default;

    void AddScore(int points);
    void LoseHealth();
    void ResetScore();
    void Reset();

    void MemoryClean();
    

    void Update();
};

