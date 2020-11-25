#pragma once
#define _ENEMY_H

#include "Ship.h"
#include "EnemyType.h"

class Blackboard;
class BehaviorTree;

class Enemy : public Ship
{
public:
	static const int MAX_BULLETS = 3;
	const std::string SHIP_NAME= "enemyship1.png";
	const std::string DEATH_ANIMATION = "ship_explosion.png";
	const int SPEED_MULTIPLIER = 1;

	Enemy();
	Enemy(EnemyType* type);
	~Enemy();

	void InitializeBullets();
	void SetBulletDirection(Vector2 direction);
	bool FireBullet();

	void CustomUpdate();
	void CustomRender();

	void SetDebugBehavior(int behavior);
	int GetDebugBehavior();

	void RespawnEnemy();
	void SetEnemyDestVector(Vector2 goalVector);
	void SetAngle(float newAngle);
	void EnemyMove();

	void CreateBehaviorTree();

	void SetEnemyType(EnemyType* typeToSet);
	EnemyType* GetEnemyType();
		
private:
	//Bullet* mBullets[MAX_BULLETS];

	std::vector<Bullet*> mBullets;

	EnemyType* enemyType;

	int debug_behavior;
		
};
