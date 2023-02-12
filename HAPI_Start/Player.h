#pragma once
#include "GameObject.h"
#include <future>
#include "HUD.h"

class Player :
	public GameObject
{
private:
    int health = 100;
	float speed = 500;

	bool isDead = false;
	bool hasWon = false;

	float deathLength = 0.2f; //the length of the death animation
	float timeSinceDeath = 0.0f; // a counter for the time since the death

	std::vector<GameObject*> bullets;

	Vector2* muzzlePos = new Vector2(0,0); //muzzlePos is the position at which the bullet should be fired 
	Vector2 m_lastPos = Vector2(0, 0);
	Vector2 startPos; // startPos is used for reseting the game

	enum class Direction
	{
		LEFT,
		RIGHT,
	};

	Direction direction = Direction::RIGHT; // the direction in which the player is moving
	CollisionDirection currentCollisionDir = CollisionDirection::NONE; // the direction where the most recent collision is occuring

	float normalisedMoveValue = (float)cos(45);
	HUD* hud; // a pointer to the HUD with access to the health bar
	
public:
	Player(std::vector<GameObject*> p_bullets, Vector2 p_pos, HUD* p_hud)
	{
		hud = p_hud;
		pos = p_pos;
		startPos = pos;
		bullets = p_bullets;
		SetTag("player");
		SetIsActive(true);

		//----------------------------------------GRAVITY_SETUP-----------------------------------------------------
		float g = 2000.0f;
		Gravity* gravity = new Gravity(g, this);
		components.push_back(gravity);

		//----------------------------------------COLLIDER_SETUP-----------------------------------------------------
		SetWidth(64);
		SetHeight(68);

		Rectangle colliderBounds = Rectangle(Vector2(0, 0), 64, 68);
		using namespace std::placeholders;
		Collider* collider = new Collider(colliderBounds, std::bind(&Player::OnCollisionEnter, this, _1, _2), 
			std::bind(&Player::OnCollisionExit, this, _1), this, false);
		components.push_back(collider);
		//----------------------------------------ANIMATOR_SETUP----------------------------------------------------
		Animator* animator = new Animator(this);
		animator->CreateNewAnim("Player_Run_Anim", 0.3f);
		animator->CreateNewAnim("Player_Idle_Anim", 0.6f);
		animator->CreateNewAnim("Player_Death_Anim", deathLength);
		components.push_back(animator);

		//----------------------------------------GUN_SETUP---------------------------------------------------------
		Gun* gun = new Gun(this, bullets, muzzlePos, true);
		gun->SetFireRate(0.2f);
		components.push_back(gun);
	};

	void MemoryClean() 
	{
		delete muzzlePos;
		GameObject::MemoryClean();
	}

	void Update();
	void CheckKeyboardInputs();
	void CheckControllerInputs();

	void Die();
	void DeathSequence();
	void Reset();
	void GameWin();
	void Damage(int d);

	int GetHealth();
	bool GetIsDead();
	bool GetHasWon();
	void CheckAnimInverted();
	void CheckControllerRumble();
	void UpdateMuzzlePos();

	void OnCollisionEnter(GameObject* gameObject, CollisionDirection dir);
	void OnCollisionExit(GameObject* gameObject);
};


