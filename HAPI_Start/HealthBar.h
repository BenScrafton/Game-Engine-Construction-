#pragma once
#include "GameObject.h"
#include "Heart.h"

class HealthBar :
    public GameObject
{
private:
    std::vector<Heart*> hearts;
    int curHearts = 7;
public:
    HealthBar()
    {
        Vector2 offset = Vector2(275, 700);

        //health bar is made up of hearts
        for (size_t i = 0; i < curHearts; i++)//add hearts to the health bar
        {
            Heart* heart = new Heart();
            heart->pos = Vector2(offset.x + (i * 70), offset.y);
            hearts.push_back(heart);
        }
    }

    ~HealthBar() noexcept = default;

    void Update();
    void RemoveHeart();
    void Reset();
    void MemoryClean();
};

