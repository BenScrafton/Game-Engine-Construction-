#include "Player.h"

void Player::Update()
{
	if (isDead)
	{
		GetComponentOfType<Animator>()->SetAnimIndex(2);
		DeathSequence();
	}
	else if(!hasWon)
	{
		m_lastPos = Vector2(pos.x, pos.y);

		GetComponentOfType<Animator>()->SetAnimIndex(1);
		CheckKeyboardInputs();
		CheckControllerInputs();

		UpdateMuzzlePos();
		CheckAnimInverted();
	}

	GameObject::Update(); //update the base game object to update all the components
}

void Player::CheckKeyboardInputs()
{
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	const HAPI_TMouseData& mouseData = HAPI.GetMouseData();

	float deltaTime = Time::GetDeltaTime();
	float Move = speed * deltaTime; // move is the distance to move this frame, delta time is used so the move is frame rate independant

	if(keyData.scanCode['W']) //Jump
	{
		GetComponentOfType<Animator>()->SetAnimIndex(0);
		if(currentCollisionDir == CollisionDirection::BELOW)
		{
			GetComponentOfType<Gravity>()->SetCurrentVelocity(-1000.0f);
		}
	}

	if(keyData.scanCode['A']) // Left
	{
		GetComponentOfType<Animator>()->SetAnimIndex(0);
		if (currentCollisionDir != CollisionDirection::LEFT)
		{
			pos.x -= Move;		
		}
		direction = Direction::LEFT;
	}

	if (keyData.scanCode['D']) // Right
	{
		GetComponentOfType<Animator>()->SetAnimIndex(0);
		if (currentCollisionDir != CollisionDirection::RIGHT)
		{
			pos.x += Move;
		}
		direction = Direction::RIGHT;
	}

	if(mouseData.leftButtonDown) //Fire
	{
		GetComponentOfType<Gun>()->Fire("Data\\Sound\\player_fire_sound2.wav");
	}
}

void Player::CheckControllerInputs()
{
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	const HAPI_TMouseData& mouseData = HAPI.GetMouseData();

	float deltaTime = Time::GetDeltaTime();
	float Move = speed * deltaTime;

	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

	if (controllerData.digitalButtons[HK_DIGITAL_A]) //Jump
	{
		GetComponentOfType<Animator>()->SetAnimIndex(0);
		if (currentCollisionDir == CollisionDirection::BELOW)
		{
			GetComponentOfType<Gravity>()->SetCurrentVelocity(-1000.0f);
		}
	}

	if (abs(controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X]) > 10000)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 0) //Right
		{
			GetComponentOfType<Animator>()->SetAnimIndex(0);
			if (currentCollisionDir != CollisionDirection::RIGHT)
			{
				pos.x += (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] / 32767.0f) * 3;
			}
			direction = Direction::RIGHT;
		}
		else
		{
			GetComponentOfType<Animator>()->SetAnimIndex(0);
			if (currentCollisionDir != CollisionDirection::LEFT) //Left
			{
				pos.x += (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] / 32768.0f) * 3;
			}
			direction = Direction::LEFT;
		}
	}

	if (controllerData.digitalButtons[HK_DIGITAL_X]) //Fire
	{
		GetComponentOfType<Gun>()->Fire("Data\\Sound\\player_fire_sound2.wav");
	}
}

void Player::Die()
{
	isDead = true;
}

void Player::DeathSequence()
{
	timeSinceDeath += Time::GetDeltaTime(); //adds to the counter for the death animation

	if(timeSinceDeath > deathLength)
	{
		SetIsActive(false);
	}
}

void Player::Reset()
{
	health = 100;
	isDead = false;
	hasWon = false;
	SetIsActive(true);

	pos.x = startPos.x + GetParent()->pos.x;
	pos.y = startPos.y + GetParent()->pos.y;

	timeSinceDeath = 0;
}

void Player::GameWin()
{
	hasWon = true;
}

void Player::Damage(int d)
{
	if(!isDead)
	{
		hud->LoseHealth();
		health -= d;
	}
}

int Player::GetHealth()
{
	return health;
}

bool Player::GetIsDead()
{
	return isDead;
}

bool Player::GetHasWon()
{
	return hasWon;
}

void Player::CheckAnimInverted()
{
	if(direction == Direction::RIGHT) // Inverts the animation based on the direction the player is moving
	{
		GetComponentOfType<Animator>()->FlipHorizontal(false);
	}
	else
	{
		GetComponentOfType<Animator>()->FlipHorizontal(true);
	}
}

void Player::UpdateMuzzlePos()
{
	if(direction == Direction::LEFT)// Changes the muzzle pos based on the direction the player is moving
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

void Player::OnCollisionEnter(GameObject* gameObject, CollisionDirection dir)
{
	if(gameObject->GetTag() == "tile_collider") // Checks if the collision is on a Tile
	{
		currentCollisionDir = dir; 

		//Reset the players position based on the current collision direction
		if(dir == CollisionDirection::BELOW || dir == CollisionDirection::ABOVE)
		{
	
			if(dir == CollisionDirection::ABOVE)
			{
				pos = m_lastPos; 
			}
			else
			{
				pos.y = m_lastPos.y;
			}

			Gravity* g = GetComponentOfType<Gravity>();
			g->ResetVelocity(); //The falling velocity of the player is set back to 0
		}
		else
		{
			pos = m_lastPos;
		}
	}

	if(gameObject->GetTag() == "DeathZone") //Kill the player when colliding with a death zone
	{
		Die();
	}
}

void Player::OnCollisionExit(GameObject* gameObject)
{
	if(gameObject->GetTag() == "tile_collider")
	{
		currentCollisionDir = CollisionDirection::NONE;
	}
}