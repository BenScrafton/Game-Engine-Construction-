#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "HUD.h"

class Bullet :
    public GameObject
{
private:
    Vector2 direction = Vector2(1,0);
    bool isFriendly = false; //if isFriendly then it doesn't hurt the player
    float speed = 2000.0f;
    float lifeSpan = 3.0f;
    float timeAlive = 0;  

    HUD* hud;

public:
    Bullet(HUD* p_hud)
    {
        hud = p_hud;

        SetIsActive(false);
        SetTag("bullet");
        SpriteSheet* spriteSheet = SpriteManager::GetSprite("Bullet_Static");

        //----------------------------------------COLLIDER_SETUP----------------------------------------------------
        Rectangle rect = Rectangle(pos, (float)spriteSheet->spriteWidth, (float)spriteSheet->spriteHeight);
        using namespace std::placeholders;
        Collider* collider = new Collider(rect, std::bind(&Bullet::OnCollisionEnter, this, _1, _2), std::bind(&Bullet::OnCollisionExit, this, _1), this, false);
        components.push_back(collider);

        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
        Animator* animator = new Animator(this);
        animator->CreateNewAnim("Bullet_Static");
        components.push_back(animator);
    }
    
    void Update();
    void SetDirection(Vector2 p_direction);
    void SetIsFriendly(bool state);

    void OnCollisionEnter(GameObject* gameObject, CollisionDirection collisionDirection);
    void OnCollisionExit(GameObject* gameObject);
};

