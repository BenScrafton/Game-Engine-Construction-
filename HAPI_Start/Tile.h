
#include "GameObject.h"
class Tile :
    public GameObject
{
private:
    std::string spriteSheetID;
    int spriteIndex;

public:
    Tile(Vector2 p_pos, std::string p_spriteSheetID, int p_spriteIndex, bool isCollider)
    {
        SetTag("tile_collider");

        pos = p_pos;
        spriteSheetID = p_spriteSheetID;
        spriteIndex = p_spriteIndex;

        //ANIMATOR_SETUP
        Animator* animator = new Animator(this);
        animator->CreateNewAnim(spriteSheetID, 0);
        animator->SetDefaultFrame(p_spriteIndex);
        components.push_back(animator);
       
        //COLLIDER_SETUP

        if(isCollider)
        {
            float colliderWidth = (float)(SpriteManager::GetSprite(spriteSheetID)->spriteWidth);
            float colliderHeight = (float)(SpriteManager::GetSprite(spriteSheetID)->spriteHeight);

            Rectangle rect = Rectangle(pos, colliderWidth, colliderHeight);
            Collider* collider = new Collider(rect, nullptr, nullptr, this, true);
            components.push_back(collider);
        }

    }
};
