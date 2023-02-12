#pragma once
#include "GameObject.h"
class DeathZone :
    public GameObject
{
private:

public:

    DeathZone(Vector2 p_pos, float p_width, float p_height)
    {
        pos = p_pos;
        SetTag("DeathZone");

        //----------------------------------------COLLIDER_SETUP-----------------------------------------------------
        Rectangle colliderBounds = Rectangle(pos, p_width, p_height);

        using namespace std::placeholders;
        Collider* collider = new Collider(colliderBounds, nullptr, nullptr, this, true);
        components.push_back(collider);
    }
};

