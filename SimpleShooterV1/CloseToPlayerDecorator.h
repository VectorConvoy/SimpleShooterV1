#pragma once
#define _CLOSETOPLAYERDECORATOR_H

#include "TaskDecorator.h"

class CloseToPlayerDecorator : public TaskDecorator
{
public:
	typedef TaskDecorator super;

	CloseToPlayerDecorator();
	CloseToPlayerDecorator(Blackboard* board, Tasks* newTask);
	CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, std::string aName);
	CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist);
	CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist, std::string aName);
	~CloseToPlayerDecorator();

	void DoAction();
	bool CheckConditions();

private: 
	float HomingRange; //Distance of how far the player should be before the AI stops or alternatively how close the AI should get to the player before stopping
};