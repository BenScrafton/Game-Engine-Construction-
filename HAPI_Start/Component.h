#pragma once
#include <string>
class GameObject;

class Component
{
private:


public:
	virtual ~Component() noexcept = default;

	GameObject* m_gameObject=nullptr; // the game object the component is attached to
	std::string id; // the id used as a type  

	virtual void MemoryClean();
	virtual void Process() = 0; // process must be implemented
};

