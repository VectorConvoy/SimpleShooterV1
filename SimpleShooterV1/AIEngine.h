#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "SteeringBehaviors.h"
#define _AIENGINE_H

class AIEngine
{
public:
	static AIEngine* Instance();
	static void Release();

	void ActivateAI();
	void SetPlayer(Player* thePlayer);
	void AddEnemy(Enemy* enemy);
	void Update();

private:

	SteeringBehavior behaviors;

	Vector2 newTarget;

	static AIEngine* sInstance;

	std::vector<Enemy*> enemies;

	Player* player;

	AIEngine();
	~AIEngine();
};