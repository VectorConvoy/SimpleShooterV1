#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "SteeringBehaviors.h"
#include <memory>
#define _AIENGINE_H

class AIEngine
{
public:

	static enum BEHAVIOR {flee = 0, seek = 1};

	static AIEngine* Instance();
	static void Release();

	void ActivateAI();
	void SetPlayer(Player* thePlayer);
	void AddEnemy(std::shared_ptr<Enemy> enemy);
	void RemoveEnemy(std::shared_ptr<Enemy> enemy);
	void Update();

private:

	SteeringBehavior behaviors;

	Vector2 newTarget;

	static AIEngine* sInstance;

	std::vector<std::shared_ptr<Enemy>> enemies;

	Player* player;

	AIEngine();
	~AIEngine();
};