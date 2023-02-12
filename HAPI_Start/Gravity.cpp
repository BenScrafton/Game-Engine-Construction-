#include "Gravity.h"

float Gravity::GetGravity()
{
    return gravity;
}

void Gravity::SetGravity(float g)
{
    gravity = g;
}

void Gravity::SetCurrentVelocity(float velocity)
{
    curVelocity = velocity;
}

float Gravity::GetCurrentVelocity()
{
    return curVelocity;
}

void Gravity::ResetVelocity()
{
    curVelocity = 0.0f;
}

void Gravity::Process()
{
    // move distance calculated by: s = ut + 0.5(at^2)
    m_gameObject->pos.y += (float)((curVelocity * Time::GetDeltaTime()) + (0.5 * gravity * Time::GetDeltaTime() * Time::GetDeltaTime()));
    curVelocity += gravity * Time::GetDeltaTime();//increment current velocity
}
