#pragma once
#include "Component.h"
#include "Rectangle.h"

class Enemy;

class AI :
    public Component
{
private:
    GameObject* enemy;

    int speed = 200;
    float jumpForce = -1000.0f;
    float attackRange = 500.0f;
    float stopDist = 200.0f;

    float patrolTime = 2.0f;
    float partolTimeComplete = 0.0f;
    bool stopped = false;
    float patrolStopTime = 2.0f;
    float patrolStopTimeComplete = 2.0f;

    int fallHeight = 4;
    int jumpHeight = 3;
    int jumpDist = 2;
    bool isJumping = false;

    int width = 0;
    int height = 0;

    float timeWaitToShoot = 0.7f;
    float timeSinceAgro = 0;

    Rectangle checkCollisionRect;
    bool checkRectSet = false;

    bool isDead = false;
    bool withinAttackRange = false;
    bool withinStopDist = false;

    float timeStep = 1/50.0f;
    float timeSinceLastProcess = 0;

    Vector2 distToPlayer;

    enum class Direction
    {
        LEFT,
        RIGHT
    };

    Direction direction;

public:

    AI(GameObject* p_gameObject, int p_width, int p_height, GameObject* p_enemy)
    {
        id = typeid(this).name();

        m_gameObject = p_gameObject;
        enemy = p_enemy;
        width = p_width;
        height = p_height;
    }

    void Process();
    void Reset();

    void SetIsDead(bool state);


    void UpdateCheckColliderPos();
    void CheckCollisionRectSetup();
    void CalcMoveDir();
    void CalculateDistToPlayer();

    bool CheckGroundToWalkOn(Vector2 dirPos);
    bool CheckCanJumpOverWall(Vector2 wallPos);
    bool CheckCanMove();
    bool CheckPos(Vector2 pos);
    bool CheckCanShoot();
    void CheckWithinAttackRange();
    void CheckWithinStopDist();
    void SetAnimInverted();

    void Shoot();
    void Jump();
    void Move();
};

