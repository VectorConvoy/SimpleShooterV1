#pragma once
#define _ENEMY_H

#include "Ship.h"

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
	~Enemy();

	void InitializeBullets();
	void SetBulletDirection(float nextDirection);
	void FireBullet();

	void CustomUpdate();
	void CustomRender();

	void SetDebugBehavior(int behavior);
	int GetDebugBehavior();

	void RespawnEnemy();
	void SetEnemyDestVector(Vector2 goalVector);
	void EnemyMove();

	void CreateBehaviorTree();
		
private:
	Bullet* mBullets[MAX_BULLETS];

	BehaviorTree* decisionTree;

	int debug_behavior;
		
};
