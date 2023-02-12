#pragma once
#include "GameObject.h"
#include "Player.h"

class WinZone :
    public GameObject
{
private:

    Player* player = nullptr;
    Collider* winCollider = nullptr;

    float animLength = 1.5f;
    float timeSinceAnim = 0;

    bool activated = false;

public:
    WinZone(Vector2 p_pos, float p_width, float p_height, GameObject* player)
    {
        SetTag("WinZone");
        this->player = ((Player*)player);
        pos = p_pos;

        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
        Animator* animator = new Animator(this);
        animator->CreateNewAnim("Plunger_Static");
        animator->CreateNewAnim("Plunger_Anim", animLength);
        components.push_back(animator);

        //----------------------------------------COLLIDER_SETUP----------------------------------------------------
        Rectangle colliderBounds = Rectangle(pos, p_width, p_height);
        using namespace std::placeholders;
        Collider* collider = new Collider(colliderBounds, nullptr, nullptr, this, true);
        components.push_back(collider);
    }

    void MemoryClean() 
    {
        delete winCollider;
        GameObject::MemoryClean();
    }

    void Update();
    void Reset();
    void ProcessActivation();

};

