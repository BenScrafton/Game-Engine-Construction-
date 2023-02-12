#pragma once
#include "GameObject.h"

class Bullet;


class Gun :
    public Component
{
private:
    float fireRate = 1.0f; // amount of bullets fired per second
    float cooldown = 0; // a timer used for to control the fire rate
    Vector2* muzzlePos = nullptr;
    Vector2 bulletDirection;

    std::vector<GameObject*> bullets;
  
    bool isFriendly = false;
    Animator* animator;

public:
    
    Gun(GameObject* p_gameObject, std::vector<GameObject*> p_bullets, Vector2* p_muzzlePos, bool p_isFriendly)
    {
        muzzlePos = p_muzzlePos;
        isFriendly = p_isFriendly;
        m_gameObject = p_gameObject;

        bullets = p_bullets;
        id = typeid(this).name();
    }

    void SetFireRate(float rate);
    void Fire(std::string filepath);
    void Process();
};

