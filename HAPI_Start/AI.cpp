#include "AI.h"
#include "GameObject.h"
#include "Enemy.h"

void AI::Process()
{
	////TIME_STEP----------------------------------------------------------------
	//timeSinceLastProcess += Time::GetDeltaTime();
	//if(timeStep > timeSinceLastProcess)
	//{
	//	return;
	//}
	//timeSinceLastProcess = 0;
	////--------------------------------------------------------------------------

	if (isDead)
	{
		m_gameObject->GetComponentOfType<Animator>()->SetAnimIndex(2);
		return;
	}

	CalculateDistToPlayer();
	CheckCollisionRectSetup();
	CalcMoveDir();

	CheckWithinAttackRange();
	CheckWithinStopDist();

	if(CheckCanShoot())
	{
		Shoot();
	}

	if(CheckCanMove())
	{
		m_gameObject->GetComponentOfType<Animator>()->currentAnimIndex = 0;//Walking anim
		Move();
	}
	else
	{
		m_gameObject->GetComponentOfType<Animator>()->currentAnimIndex = 1;//Idle anim
	}

	SetAnimInverted();
}

void AI::UpdateCheckColliderPos()
{
	checkCollisionRect.RecalculateBounds(m_gameObject->pos);
}

void AI::CheckCollisionRectSetup()
{
	if (!checkRectSet)
	{
		checkCollisionRect = Rectangle(m_gameObject->pos, (float)width, (float)height);
		checkRectSet = true;
	}
	else
	{
		UpdateCheckColliderPos();
	}
}

void AI::CalcMoveDir()
{
	if(!withinAttackRange)//patrol mode 
	{
		partolTimeComplete += Time::GetDeltaTime();

		if(patrolTime < partolTimeComplete && !stopped)
		{
			partolTimeComplete = 0.0f;
			stopped = true;

		}
		else if (stopped)
		{
			patrolStopTimeComplete += Time::GetDeltaTime();

			if (patrolStopTime < patrolStopTimeComplete)
			{
				if (direction == Direction::RIGHT)
				{
					direction = Direction::LEFT;
				}
				else
				{
					direction = Direction::RIGHT;
				}

				stopped = false;
				patrolStopTimeComplete = 0.0f;
				partolTimeComplete = 0.0f;
			}
		}
	}
	else//chase mode 
	{
		stopped = false;
		patrolStopTimeComplete = 0.0f;

		if(distToPlayer.x < 10)
		{
			return;
		}

		if (enemy->pos.x > m_gameObject->pos.x) 
		{
			direction = Direction::RIGHT;
		}
		else
		{
			direction = Direction::LEFT;
		}
	}
}

void AI::CalculateDistToPlayer()
{
	distToPlayer.x = abs(enemy->pos.x - m_gameObject->pos.x);
	distToPlayer.y = abs(enemy->pos.x - m_gameObject->pos.x);
}

bool AI::CheckGroundToWalkOn(Vector2 dirPos)
{
	dirPos.y += height;

	if(CheckPos(dirPos))
	{
		return true;
	}

	return false;
}

bool AI::CheckCanJumpOverWall(Vector2 wallPos)
{
	wallPos = Vector2(wallPos.x, wallPos.y - jumpHeight * height);

	if (CheckPos(wallPos))
	{
		return false;
	}

	return true;
}

bool AI::CheckCanMove()
{
	if(!withinAttackRange)
	{
		return false;
	}

	if(stopped) // when patroling
	{
		return false;
	}

	if(withinStopDist) // when attacking 
	{
		if((enemy->pos.y <= m_gameObject->pos.y + (height/2)) && (enemy->pos.y >= m_gameObject->pos.y - height) && 
			!(m_gameObject->GetComponentOfType<Collider>()->GetCurCollisionDir() == CollisionDirection::NONE)) // check within y line of sight and in mid air
		{
			return false;
		}
	}


	Vector2 wallCheckPos = Vector2(m_gameObject->pos.x, m_gameObject->pos.y - 1);
	Vector2 floorCheckPos = Vector2(m_gameObject->pos.x, m_gameObject->pos.y + height);
	Vector2 jumpCheckPos = Vector2(m_gameObject->pos.x, m_gameObject->pos.y + height);

	if(direction == Direction::LEFT)
	{
		wallCheckPos.x -= width + 32;
		floorCheckPos.x -= width + 32;
		jumpCheckPos.x -= width + 32;
	}
	else
	{
		wallCheckPos.x += width + 32;
		floorCheckPos.x += width + 32;
		jumpCheckPos.x += width + 32;
	}

	//----------------------Check if AI is mid air-----------------------------------------------------------------------------------
	if(m_gameObject->GetComponentOfType<Collider>()->GetCurCollisionDir() == CollisionDirection::NONE && !CheckPos(wallCheckPos)) // if the enemy is mid air and there is no wall in the way
	{
		return true;
	}
	//---------------------------------------------------------------------------------------------------------------------------------
	
	//----------------------Check if AI is has ground to walk on----------------------------------------------------------------------
	if (!CheckPos(floorCheckPos)) // if there is no ground to walk on
	{
		bool somethingToFallOn = false;

		for (size_t i = 0; i < fallHeight; i++)// check if there is something to all onto
		{
			floorCheckPos.y += height;
			if (CheckPos(floorCheckPos))
			{
				somethingToFallOn = true;
			}
		}

		if(!somethingToFallOn)// if there is nothing to fall on
		{
			for (size_t i = 0; i < jumpDist; i++)//check if there is a gap to jump over
			{
				if (direction == Direction::LEFT)
				{
					jumpCheckPos.x -= width;
				}
				else
				{
					jumpCheckPos.x += width;
				}



				if (CheckPos(jumpCheckPos))
				{
					Jump();
				}
			}
		
			return false;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------

	//----------------------Check if AI has a wall in the way--------------------------------------------------------------------------
	if(CheckPos(wallCheckPos)) //if there is a wall in the way
	{
		if(CheckCanJumpOverWall(wallCheckPos)) // if can jump over the wall
		{
			Jump();
		}
		return false;
	}
	//---------------------------------------------------------------------------------------------------------------------------------

	return true;
}

bool AI::CheckPos(Vector2 pos) 
{
	GameObject* collider = nullptr;

	checkCollisionRect.RecalculateBounds(pos);
	collider = m_gameObject->GetComponentOfType<Collider>()->CheckCollision(checkCollisionRect);

	if (collider != nullptr)
	{
		if (collider->GetTag() == "tile_collider")
		{
			return true;
		}
	}

	return false;
}

bool AI::CheckCanShoot()
{
	if (withinAttackRange && enemy->GetIsActive())
	{
		if((enemy->pos.y <= m_gameObject->pos.y + (height/2.0f)) && (enemy->pos.y >= m_gameObject->pos.y - height)) // check if the player is within y range
		{
			timeSinceAgro += Time::GetDeltaTime();

			if(timeSinceAgro > timeWaitToShoot)
			{
				return true;
			}
		}
	}
	return false;
}

void AI::CheckWithinAttackRange()
{
	if ((distToPlayer.x < attackRange) && (distToPlayer.y < attackRange))
	{
		withinAttackRange = true;
	}
	else
	{
		withinAttackRange = false;
	}
}

void AI::CheckWithinStopDist()
{
	if ((distToPlayer.x < stopDist))
	{
		withinStopDist = true;
	}
	else
	{
		withinStopDist = false;
	}
}

void AI::SetIsDead(bool state)
{
	isDead = state;
}

void AI::Reset()
{
	timeSinceAgro = 0;
}

void AI::SetAnimInverted()
{
	if(direction == Direction::LEFT)
	{
		m_gameObject->GetComponentOfType<Animator>()->FlipHorizontal(true);
	}
	else if(direction == Direction::RIGHT)
	{
		m_gameObject->GetComponentOfType<Animator>()->FlipHorizontal(false);
	}
}

void AI::Shoot()
{
	m_gameObject->GetComponentOfType<Gun>()->Fire("Data\\Sound\\enemy_fire_sound.wav");
}

void AI::Jump()
{
	m_gameObject->pos.y -= 1;

	if(((Enemy*)m_gameObject)->curCollisionDir == CollisionDirection::BELOW)
	{
		isJumping = true;
		m_gameObject->GetComponentOfType<Gravity>()->SetCurrentVelocity(jumpForce);
	}
}

void AI::Move()
{
	if(direction == Direction::LEFT)
	{
		((Enemy*)m_gameObject)->direction = Enemy::Direction::LEFT;

		m_gameObject->pos.x -= speed * Time::GetDeltaTime();
	}
	else if(direction == Direction::RIGHT)
	{
		((Enemy*)m_gameObject)->direction = Enemy::Direction::RIGHT;

		m_gameObject->pos.x += speed * Time::GetDeltaTime();
	}
}
