#pragma once
#include "GameObject.h"
class Explosion :
    public GameObject
{
private:
    float explosionLength = 0.75; //explosion animation length
    float timeSinceExplosion = 0; //explosion animation timer

public:
    Explosion()
    {
        pos = Vector2(-420, -100);

        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
        Animator* animator = new Animator(this);

        animator->CreateNewAnim("Explosion2_Anim", explosionLength);
        animator->CreateNewAnim("Explosion_Static");

        components.push_back(animator);

        SetIsActive(false);
    }

    void Reset();
    void Update();

};

