#pragma once
#include "Enemy.h"
#include "Player.h"
#define _VISIBILITYSTATUS_H

class VisibilityStatus
{
public:
	//void CheckEnemySight(Vector2 playerPos, Vector2 enemyPos,Enemy::DIRECTION direction);
	bool GetPlayerInSight();

	void SetSightDistance(int value) { sightDistance = value; };

private:
	bool playerInSight;
	int sightDistance;
};