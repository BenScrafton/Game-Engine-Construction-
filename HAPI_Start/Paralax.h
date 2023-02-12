#pragma once
#include "Component.h"
#include "GameObject.h"

class Paralax :
    public Component
{
private:
    float paralaxFactor = 10;
    Vector2 lastPos=NULL;

public:
    Paralax(float p_paralaxFactor, GameObject* p_gameObject)
    {
        paralaxFactor = p_paralaxFactor;
        m_gameObject = p_gameObject;
        id = typeid(this).name();
    }

    void Process();
};

