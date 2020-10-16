#pragma once
#define _BEHAVIOR_H

#include "Command.h"
#include <vector>
#include "Player.h"

class Behavior
{
public:

	Behavior();
	~Behavior();

	void SetPriorityID(int priority);
	int GetPriorityID();

	bool CloseToPlayer();
	bool FarFromPlayer();


private:
	int priorityID;

	Player* player;
};