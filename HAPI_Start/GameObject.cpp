#include "GameObject.h"

void GameObject::Update()
{
	if(isActive)
	{
		UpdateChildrenPositions(); //Moves the child gameObjects in relation to this gameObject

		for (Component* component : components) // Update all components
		{
			component->Process();
		}
		lastPos = pos;
	}
}

void GameObject::SetTag(std::string p_tag)
{
	tag = p_tag;
}

std::string GameObject::GetTag()
{
	return tag;
}

void GameObject::SetIsActive(bool state)
{
	isActive = state;
}

void GameObject::SetWidth(int p_width)
{
	width = p_width;
}

void GameObject::SetHeight(int p_height)
{
	height = p_height;
}

int GameObject::GetWidth()
{
	return width;
}

int GameObject::GetHeight()
{
	return height;
}

bool GameObject::GetIsActive()
{
	return isActive;
}

void GameObject::SetParent(GameObject* p_parent)
{
	parent = p_parent;
}

GameObject* GameObject::GetParent()
{
	return parent;
}

void GameObject::AddChild(GameObject* p_child)
{
	children.push_back(p_child);
}

void GameObject::UpdateChildrenPositions()
{
	move.x = pos.x - lastPos.x;
	move.y = pos.y - lastPos.y;

	for(GameObject* child : children) //Updates all child  gameObjcet positions in relation to this gameObject
	{
		if(child != nullptr)
		{
			child->pos.x += move.x;
			child->pos.y += move.y;
		}
	}
}

void GameObject::Reset()
{
}

void GameObject::MemoryClean()
{
	for(Component* component : components) // cleans components memory then deletes all components
	{
		component->MemoryClean();
		delete component;
	}
}

Vector2 GameObject::GetMove()
{
	return move;
}


