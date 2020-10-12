#pragma once
#define _ENEMY_H

#include "AnimatedTexture.h"
#include <vector>
#include "Bullet.h"
#include "Ship.h"
#include "Sequence.h"

class Enemy : public Ship
{
public:
	static const int MAX_BULLETS = 3;
	const std::string SHIP_NAME= "enemyship1.png";
	const std::string DEATH_ANIMATION = "ship_explosion.png";

	Enemy();
	~Enemy();

	void InitializeBullets();
	void SetBulletDirection(float nextDirection);
	void FireBullet();

	void CustomUpdate();
	void CustomRender();

	void RespawnEnemy();
	void SetEnemyDestVector(Vector2 goalVector);
	void EnemyMove();
		
private:
	Bullet* mBullets[MAX_BULLETS];

		
};
