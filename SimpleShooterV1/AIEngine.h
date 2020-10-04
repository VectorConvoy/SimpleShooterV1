#pragma once
#include <vector>
#include "Enemy.h"
#define _AIENGINE_H

class AIEngine
{
public:
	static AIEngine* Instance();
	static void Release();

	void ActivateAI();

private:

	static AIEngine* sInstance;

	std::vector<Enemy*> enemies;

	AIEngine();
	~AIEngine();
};