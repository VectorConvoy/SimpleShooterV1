#pragma once
#define _ENEMYSHOOT_H

#include "Node.h"

class EnemyShootTask : public Node
{
public:
	typedef Node super;

	//EnemyShootTask(Blackboard* board);
	EnemyShootTask(Blackboard* board, std::string aName);
	~EnemyShootTask();

	bool CheckConditions();
	void Start();
	void End();
	void DoAction();
};