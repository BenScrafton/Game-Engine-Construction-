#pragma once
#include "GameObject.h"

class Enemy:
	public GameObject
{
public:
	float fireRate = 0.5f;
	float timeSinceShoot = 0;

	bool isDead = false;
	float deathLength = 0.8f; // the length of the death animation
	float timeAfterDeath = 0.0f; // a counter for the time since the death

	Vector2* muzzlePos = new Vector2(0, 0);
	Vector2 m_lastPos = Vector2(0, 0);
	Vector2 startPos;
	CollisionDirection curCollisionDir = CollisionDirection::NONE; // the direction where the most recent collision is occuring

	std::vector<GameObject*> bullets;

	enum class Direction
	{
		LEFT,
		RIGHT,
	};

	Direction direction = Direction::RIGHT; // the direction in which the player is moving

public:
	Enemy(std::vector<GameObject*> p_bullets, Vector2 p_startPos, GameObject* player)
	{
		startPos = p_startPos;
		pos = startPos;
		bullets = p_bullets;

		SetTag("enemy");
		SetIsActive(true);

		//----------------------------------------GRAVITY_SETUP-----------------------------------------------------
		float g = 2000.0f;
		Gravity* gravity = new Gravity(g, this);
		components.push_back(gravity);
		
		//----------------------------------------AI_SETUP----------------------------------------------------------
		AI* ai = new AI(this, 64, 64, player);
		components.push_back(ai);

		//----------------------------------------COLLIDER_SETUP----------------------------------------------------
		//SetWidth(64);
		//SetHeight(68);

		Rectangle colliderBounds = Rectangle(Vector2(0, 0), 64, 68);

		using namespace std::placeholders;
		Collider* collider = new Collider(colliderBounds, std::bind(&Enemy::OnCollisionEnter, this, _1, _2), std::bind(&Enemy::OnCollisionExit, this, _1), this, false);
		components.push_back(collider);

		//----------------------------------------ANIMATOR_SETUP----------------------------------------------------
		Animator* animator = new Animator(this);
		animator->CreateNewAnim("Enemy_Run_Anim", 0.5f);
		animator->CreateNewAnim("Enemy_Idle_Anim", 0.8f);
		animator->CreateNewAnim("Enemy_Death_Anim", deathLength);
		components.push_back(animator);

		
		//----------------------------------------GUN_SETUP---------------------------------------------------------
		Gun* gun = new Gun(this, bullets, muzzlePos, false);
		gun->SetFireRate(0.1f);
		components.push_back(gun);
	}

	void MemoryClean() 
	{
		delete muzzlePos;
		GameObject::MemoryClean();
	}


	void Update();
	void UpdateMuzzlePos();
	void Die();
	void DeathSequence();
	void Reset();
	void Shoot();
	bool GetIsDead();
	void OnCollisionEnter(GameObject* gameObject, CollisionDirection dir);
	void OnCollisionExit(GameObject* gameObject);
};

