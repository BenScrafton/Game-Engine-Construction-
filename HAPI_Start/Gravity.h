#pragma once
#include "Component.h"
#include "Time.h"
#include "GameObject.h"

class Gravity :
    public Component
{
private:

    float gravity = 9.81f;
    float curVelocity = 0.0f;

public:
    Gravity(float p_gravity, GameObject* p_gameObject)
    {
        m_gameObject = p_gameObject;
        gravity = p_gravity;
        curVelocity = 0.0f;
        id = typeid(this).name();
    }

    float GetGravity();
    void SetGravity(float g);

    void SetCurrentVelocity(float velocity);
    float GetCurrentVelocity();
    void ResetVelocity();
    void Process();
};

