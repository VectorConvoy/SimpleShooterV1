#pragma once
#include "MathHelper.h"
#define _BLACKBOARD_H

#include "Player.h"
#include "Enemy.h"

class Blackboard
{
public:
	Blackboard();
	~Blackboard();

	void SetEnemy(Enemy* enemy);
	Enemy* GetEnemy();

	void SetPlayer(Player* player);
	Player* GetPlayer();

	void SetPlayerPos(Vector2 pos);
	Vector2 GetPlayerPos();

	void SetMoveDirection(Vector2 dest);
	Vector2 GetMoveDirection();

private:
	Enemy* AIOwner; //Enemy that owns this blackboard

	Vector2 moveDirection; //Vector destination of where the enemy should move to

	Player* player; //Keep track of Player

	Vector2 playerPos;

	//ScreenManager* instance;

};