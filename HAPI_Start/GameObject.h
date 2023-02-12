#pragma once
#include <HAPI_lib.h>
#include "Component.h"
#include "Animator.h"
#include "Collider.h"
#include "Gravity.h"
#include "Vector2.h"
#include "Gun.h"
#include "Paralax.h" 
#include "AI.h"

class GameObject
{
private:
	std::string tag = "null"; //gameObjects use tags as identifiers
	GameObject* parent=nullptr; // gameObjects can have a parent which links there position movement
	std::vector<GameObject*> children; //gameObjects can have children which get positions changed based on the movement of this gameObject
	Vector2 move; //move is updated based on the move of this gameObject the move is then applied to the child gameObjets

	bool isActive = true; // active state determines if the gameObject amd its components should be updated

	int width = 64;
	int height = 64;

public:
	Vector2 pos = Vector2(0,0); // pos represents the current position of the gameObject, which is in the top left of any sprite
	Vector2 lastPos = Vector2(0,0); // last pos is used to calculate the move applied to the child gameObjects
	std::vector<Component*> components; // a list of components which make up the gameObjets behavior

	virtual void Update();
	virtual ~GameObject() noexcept = default;

	void SetTag(std::string p_tag);
	std::string GetTag();

	void SetIsActive(bool state);

	void SetWidth(int p_width);
	void SetHeight(int p_height);

	int GetWidth();
	int GetHeight();

	bool GetIsActive();
	void SetParent(GameObject* p_parent);
	GameObject* GetParent();
	void AddChild(GameObject* p_child);
	void UpdateChildrenPositions();
	virtual void Reset();

	virtual void MemoryClean();

	Vector2 GetMove();

	template <typename T>
	T* GetComponentOfType()	//GetComponentOfType<Type>() - returns a component on the gameObject of the specified type 
	{
		for (Component* component : components)
		{
			if (typeid(T*).name() == component->id)
			{
				return (T*) component;
			}
		}

		return NULL;
	}
};

