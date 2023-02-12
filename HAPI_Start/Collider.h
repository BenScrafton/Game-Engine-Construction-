#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Rectangle.h"
#include <functional>
#include <vector>

enum class CollisionDirection
{
    NONE,
    ABOVE,
    BELOW,
    LEFT,
    RIGHT
};

class Collider :
    public Component
{
private:
    std::function<void(GameObject*, CollisionDirection dir)> onCollisionEnterPtr; // a pointer to the m_gameObject's OnCollisionEnter() 
    std::function<void(GameObject*)> onCollisionExitPtr; // a pointer to the m_gameObject's OnCollisionExit() 

    std::vector<GameObject*> curCollidingGameObjects; // a list of the game objects currently colliding with this game object

    CollisionDirection curCollisionDir = CollisionDirection::NONE; // the most recent collision's direction

    bool isStatic = false; //if is static then the collider doesn't move and it's bounds are not recalculated

public:
    Rectangle boundingBox;
    static int iCollisions;

    static std::vector<Collider*> colliders; //a static list of all colliders, all colliders share this data

    Collider(Rectangle bounds, std::function<void(GameObject*, CollisionDirection dir)> onCollisionEnter_callback, 
             std::function<void(GameObject*)> onCollisionExit_callback,  
             GameObject* gameObject, bool p_isStatic)
    {
        boundingBox = bounds;
        m_gameObject = gameObject;
        isStatic = false;//p_isStatic;
        id = typeid(this).name();

        if(onCollisionEnter_callback != nullptr)//set up OnCollisionEnter() pointer
        {
            onCollisionEnterPtr = onCollisionEnter_callback;
        }

        if (onCollisionEnter_callback != nullptr)//set up OnCollisionExit() pointer
        {
            onCollisionExitPtr = onCollisionExit_callback;
        }

        colliders.push_back(this); //add this collider to the static collider list
    }

    CollisionDirection DetermineCollisionDirection(Collider* boxCollider);
    bool DetectCollision(Collider* boxCollider);
    void CheckCollisions();

    GameObject* CheckCollision(Rectangle boxCollider);

    bool CheckCollisionSingle(Rectangle boxCollider);

    CollisionDirection GetCurCollisionDir();
    bool CheckCollisionExit(GameObject* collider);
    void UpdateBoundsPos();
    void SetIsStatic(bool state);
    void Process();
};

