#pragma once
#define _AIENGINE_H


#include <vector>
#include <memory>
#include "Blackboard.h"

class Enemy;

class AIEngine
{
public:

	enum BEHAVIOR {flee = 0, seek = 1};

	static AIEngine* Instance();
	static void Release();

	void ActivateAI();
	void SetPlayer(Player* thePlayer);
	void AddEnemy(std::shared_ptr<Enemy> enemy);
	void RemoveEnemy(std::shared_ptr<Enemy> enemy);
	void Update();

private:

	//SteeringBehavior behaviors;

	Vector2 newTarget;

	static AIEngine* sInstance;

	std::vector<std::shared_ptr<Enemy>> enemies;

	Player* player;

	AIEngine();
	~AIEngine();
};