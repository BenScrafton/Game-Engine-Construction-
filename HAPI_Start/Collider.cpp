#include "Collider.h"

std::vector<Collider*> Collider::colliders;

int Collider::iCollisions=0;

CollisionDirection Collider::DetermineCollisionDirection(Collider* boxCollider)
{
    float xDif = 0;
    float yDif = 0;

    if(!isStatic)
    {
        xDif = m_gameObject->pos.x - m_gameObject->lastPos.x;
        yDif = m_gameObject->pos.y - m_gameObject->lastPos.y;
    }

    if(boundingBox.BL_Bound.y - yDif < boxCollider->boundingBox.TL_Bound.y)
    {
        return CollisionDirection::BELOW;
    }
    else if(boundingBox.TL_Bound.y - yDif > boxCollider->boundingBox.BL_Bound.y)
    {
        return CollisionDirection::ABOVE;
    }
    else if(boundingBox.BR_Bound.x - xDif < boxCollider->boundingBox.BL_Bound.x)
    {
        return CollisionDirection::RIGHT;
    }
    else if(boundingBox.BL_Bound.x -xDif > boxCollider->boundingBox.BR_Bound.x)
    {
        return CollisionDirection::LEFT;
    }

    return CollisionDirection::NONE;
}

bool Collider::DetectCollision(Collider* boxCollider)
{
    if(!boxCollider->m_gameObject->GetIsActive())
    {
        return false;
    }
    
    if (boundingBox.BL_Bound.x < boxCollider->boundingBox.BL_Bound.x - 100
        || boundingBox.BL_Bound.x > boxCollider->boundingBox.BL_Bound.x + 100
        || boundingBox.BL_Bound.y > boxCollider->boundingBox.BL_Bound.y + 100
        || boundingBox.BL_Bound.y < boxCollider->boundingBox.BL_Bound.y - 100) // if the other collider is not within 100px of this collider then stop the collision check
    {
        if(boundingBox.BL_Bound.y < 1200)
        {
            return false;
        }
    }

    if ((boundingBox.BL_Bound.y >= boxCollider->boundingBox.TL_Bound.y && boundingBox.TL_Bound.y <= boxCollider->boundingBox.BL_Bound.y )
    && ((boundingBox.BL_Bound.x <= boxCollider->boundingBox.BR_Bound.x) && (boundingBox.BR_Bound.x >= boxCollider->boundingBox.BL_Bound.x))) // if the collider is within this colliders bounds
    {
        if (onCollisionEnterPtr != nullptr)
        {
            curCollidingGameObjects.push_back(boxCollider->m_gameObject);
            curCollisionDir = DetermineCollisionDirection(boxCollider); //calculate the collision direction
            onCollisionEnterPtr(boxCollider->m_gameObject, curCollisionDir); //call the colliders OnCollisionEnter()
        }
        return true;
    }

    if(CheckCollisionExit(boxCollider->m_gameObject))
    {
        curCollisionDir = CollisionDirection::NONE;
        onCollisionExitPtr(boxCollider->m_gameObject);  //call the colliders OnCollisionExit()
    }

    return false;
}



void Collider::CheckCollisions()
{
    for(Collider* collider:colliders) // check all the colliders in the static list for a collision
    {
        if(collider != this) // dont check this collider against this collider 
        {
            if(DetectCollision(collider))
            {
                return;
            }
        }
    }
}

GameObject* Collider::CheckCollision(Rectangle boxCollider)
{
    for (Collider* collider : colliders)
    {
        if (collider != this)
        {
            if ((collider->boundingBox.BL_Bound.y >= boxCollider.TL_Bound.y && collider->boundingBox.TL_Bound.y <= boxCollider.BL_Bound.y)
                && ((collider->boundingBox.BL_Bound.x <= boxCollider.BR_Bound.x) && (collider->boundingBox.BR_Bound.x >= boxCollider.BL_Bound.x))) //checks for collision
            {
                return collider->m_gameObject;
            }   
        }
    }
    return nullptr;
}

bool Collider::CheckCollisionSingle(Rectangle boxCollider)
{
    if ((this->boundingBox.BL_Bound.y >= boxCollider.TL_Bound.y && this->boundingBox.TL_Bound.y <= boxCollider.BL_Bound.y)
        && ((this->boundingBox.BL_Bound.x <= boxCollider.BR_Bound.x) && (this->boundingBox.BR_Bound.x >= boxCollider.BL_Bound.x))) //Checks if a box collider is colliding within this box collider
    {
        return true;
    }
    return false;
}

CollisionDirection Collider::GetCurCollisionDir()
{
    return curCollisionDir;
}

bool Collider::CheckCollisionExit(GameObject* collider)
{
    int i = 0;

    for(GameObject* gameObject : curCollidingGameObjects)
    {
        if(gameObject == collider)
        {
            curCollidingGameObjects.erase(curCollidingGameObjects.begin()+i);//deletes the collider exited from the list
            return true;
        }
        i++;
    }
    return false;
}

void Collider::Process()
{

    
    UpdateBoundsPos();
    
    if (!isStatic)
    {
        CheckCollisions();
    }
}

void Collider::UpdateBoundsPos()
{  
    //recalculates the collider bounds based on the position of the components gameObject
    boundingBox.RecalculateBounds(m_gameObject->pos);
}

void Collider::SetIsStatic(bool state)
{
    isStatic = state;
}
