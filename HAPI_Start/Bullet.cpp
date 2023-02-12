#include "Bullet.h"

void Bullet::Update()
{
	if(GetIsActive())
	{
		timeAlive += Time::GetDeltaTime(); //increment the timeAlive timer
		if(lifeSpan < timeAlive) //deactivate the bullet when its life time is over
		{
			SetIsActive(false);
			timeAlive = 0;
		}

		//Move the bulley in the direction vector
		pos.x += direction.x * speed * Time::GetDeltaTime();
		pos.y += direction.y * speed * Time::GetDeltaTime();
	}

	GameObject::Update(); //update the base game object to update all components
}

void Bullet::SetDirection(Vector2 p_direction)
{
	direction = p_direction;
}

void Bullet::SetIsFriendly(bool state)
{
	isFriendly = state;
}

void Bullet::OnCollisionEnter(GameObject* gameObject, CollisionDirection collisionDirection)
{
	if (GetIsActive())
	{
		if (isFriendly)
		{
			if (gameObject->GetTag() == "enemy")//kill the enemy and add to score
			{
				((Enemy*)gameObject)->Die();
				hud->AddScore(10);
				SetIsActive(false); //deactivate the bullet
			}
		}
		else
		{
			if (gameObject->GetTag() == "player")//damage the player
			{
				((Player*)gameObject)->Damage(15);

				if(((Player*)gameObject)->GetHealth() <= 0)
				{
					((Player*)gameObject)->Die();// kill the player
				}

				SetIsActive(false);//deactivate the bullet
			}
		}

		if (gameObject->GetTag() == "tile_collider")
		{
			SetIsActive(false);//deactivate the bullet
		}
	}
}

void Bullet::OnCollisionExit(GameObject* gameObject)
{

}


