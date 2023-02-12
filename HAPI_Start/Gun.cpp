#include "Gun.h"
#include "Bullet.h"

void Gun::SetFireRate(float rate)
{
	fireRate = rate;
}

void Gun::Fire(std::string filepath)
{
	if (cooldown < fireRate)
	{
		return;
	}

	cooldown = 0;

	Animator* animator = m_gameObject->GetComponentOfType<Animator>();

	int i = 0;

	HAPI_TSoundOptions options(0.3f, false, 0);
	if (!HAPI.PlaySound(filepath, options))
	{
		return;
	}

	for(GameObject* bullet : bullets)
	{
		i++;

		if(!bullet->GetIsActive())
		{
			if(animator->GetInverted()) //change the bullets direction if the animator is inverted 
			{
				m_gameObject->pos.x += 15;
				bulletDirection = Vector2(-1, 0);
			}
			else
			{
				m_gameObject->pos.x -= 15;
				bulletDirection = Vector2(1, 0);
			}

			m_gameObject->pos.y -= 3;
			
			//----------------FIRE BULLET--------------------------------
			((Bullet*)bullet)->SetIsFriendly(isFriendly);
			((Bullet*)bullet)->SetDirection(bulletDirection);
			bullet->pos.x = muzzlePos->x;
			bullet->pos.y = muzzlePos->y;
			bullet->SetIsActive(true);

			return;
		}
	}	
}

void Gun::Process()
{
	cooldown += Time::GetDeltaTime();

	if (animator == NULL) 
	{
		animator = m_gameObject->GetComponentOfType<Animator>();
	}	
}

