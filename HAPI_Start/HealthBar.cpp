#include "HealthBar.h"

void HealthBar::Update()
{
    for (size_t i = 0; i < curHearts; i++) // update all the remaining hearts
    {
        hearts[i]->Update();
    }
}

void HealthBar::RemoveHeart()
{
    curHearts--;
}

void HealthBar::Reset()
{
    curHearts = 7;

    for (size_t i = 0; i < curHearts; i++) // set all hearts to be active
    {
        hearts[i]->SetIsActive(true);
    }
}

void HealthBar::MemoryClean()
{
    std::cout << "Clean health " << std::endl;

    for (Heart* h : hearts)
    {
        h->MemoryClean();
        delete h;
    }

    for (Component*  c : components)
    {
        delete c;
    }
}
