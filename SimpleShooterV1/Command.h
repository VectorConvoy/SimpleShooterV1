#pragma once
#include "Enemy.h"
#define _COMMAND_H

class Command
{
public:
	virtual bool Execute();

	virtual bool Execute(Enemy* enemy) = 0;
private:
	int priority;
};