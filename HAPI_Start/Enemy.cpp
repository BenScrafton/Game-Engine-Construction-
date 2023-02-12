#include "Enemy.h"

void Enemy::Update()
{
	m_lastPos = Vector2(pos.x, pos.y);

	if(isDead)
	{
		DeathSequence();
	}

	GameObject::Update(); //update the base game object to update all the components
	UpdateMuzzlePos(); 
}

void Enemy::UpdateMuzzlePos()
{
	if (direction == Direction::LEFT)// Changes the muzzle pos based on the direction the enemy is moving
	{
		muzzlePos->x = pos.x;
		muzzlePos->y = pos.y + 38;
	}
	else
	{
		muzzlePos->x = pos.x + 64;
		muzzlePos->y = pos.y + 38;
	}
}

void Enemy::Die()
{
	if(!isDead)
	{
		isDead = true;
		GetComponentOfType<AI>()->SetIsDead(true);

		if (!HAPI.PlaySound("Data\\Sound\\enemy_death_sound2.wav"))
		{
			return;
		}
	}
}

void Enemy::DeathSequence()
{
	timeAfterDeath += Time::GetDeltaTime(); //adds to the counter for the death animation

	if(timeAfterDeath >= deathLength)
	{
		SetIsActive(false);
	}
}

void Enemy::Reset()
{
	isDead = false;
	GetComponentOfType<AI>()->SetIsDead(isDead);
	GetComponentOfType<AI>()->Reset();
	SetIsActive(true);

	timeAfterDeath = 0;

	pos.x = startPos.x + GetParent()->pos.x;
	pos.y = startPos.y + GetParent()->pos.y;

	GetComponentOfType<Gravity>()->ResetVelocity();
}

void Enemy::Shoot()
{
	GetComponentOfType<Gun>()->Fire("Data\\Sound\\enemy_fire_sound.wav");
}

bool Enemy::GetIsDead()
{
	return isDead;
}

void Enemy::OnCollisionEnter(GameObject* gameObject, CollisionDirection dir)
{
	if (gameObject->GetTag() == "tile_collider")
	{
		curCollisionDir = dir;

		//Reset the enemy position based on the current collision direction
		if (dir == CollisionDirection::BELOW || dir == CollisionDirection::ABOVE)
		{
			Gravity* g = GetComponentOfType<Gravity>();
			if (dir == CollisionDirection::ABOVE)
			{
				GetComponentOfType<Gravity>()->SetCurrentVelocity(-1 * GetComponentOfType<Gravity>()->GetCurrentVelocity() * 0.5);
				pos.y = m_lastPos.y;
				pos.x = m_lastPos.x;
			}
			else
			{
				g->ResetVelocity();
				pos.y = m_lastPos.y;
			}

			//The falling velocity of the enemy is set back to 0
		}
		else
		{
			pos = m_lastPos;
		}
	}

	if (gameObject->GetTag() == "DeathZone") //Kill the enemy when colliding with a death zone
	{
		Die();
	}
}

void Enemy::OnCollisionExit(GameObject* gameObject)
{
	if(gameObject->GetTag() == "tile_collider")
	{
		curCollisionDir = CollisionDirection::NONE;
	}
}
