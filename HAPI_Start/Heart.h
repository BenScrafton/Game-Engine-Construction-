#pragma once
#include "GameObject.h"
class Heart :
    public GameObject
{
private:

public:
    Heart()
    {
        //----------------------------------------ANIMATOR_SETUP----------------------------------------------------
          Animator* animator = new Animator(this);
          animator->CreateNewAnim("Heart_Static");
          components.push_back(animator);
    }

    void MemoryClean() {
        std::cout << "Comps " << components.size() << std::endl;

        GameObject::MemoryClean();
    }


};

