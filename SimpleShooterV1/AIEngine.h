#pragma once
#define _AIENGINE_H


#include <vector>
#include <memory>
#include "Blackboard.h"

class Enemy;
class Behavior;

class AIEngine
{
public:

	enum BEHAVIOR {flee = 0, seek = 1};

	static AIEngine* Instance();
	static void Release();

	void SetPlayer(Player* thePlayer);
	void AddEnemy(std::shared_ptr<Enemy> enemy);
	void RemoveEnemy(std::shared_ptr<Enemy> enemy);
	void ClearEnemies();

	void InitializeBehaviors();
	std::vector<std::shared_ptr<Behavior>> GetAllBehaviors();

	Behavior* GetSpecificBehavior(std::string name);
	void SortBehaviors();
	void SetPriorityForBehavior(std::string name, int priorityVal);
	void SetValueForBehavior(std::string name, float val);
	void SetConditionTypeForBehavior(std::string name, std::string condType);
	void ClearBehaviors();


	void Update();

private:

	//SteeringBehavior behaviors;

	Vector2 newTarget;

	static AIEngine* sInstance;

	std::vector<std::shared_ptr<Enemy>> enemies;

	std::vector<std::shared_ptr<Behavior>> allBehaviors; //Vector that contains all available behaviors

	Player* player;

	AIEngine();
	~AIEngine();
};
