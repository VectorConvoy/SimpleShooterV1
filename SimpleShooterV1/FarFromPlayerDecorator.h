#pragma once
#define _FARFROMPLAYERDECORATOR_H

#include "TaskDecorator.h"

class FarFromPlayerDecorator : public TaskDecorator
{
public:

	typedef TaskDecorator super;

	FarFromPlayerDecorator();
	//CloseToPlayerDecorator(Blackboard* board, Tasks* newTask);
	FarFromPlayerDecorator(Blackboard* board, Tasks* newTask, std::string aName);
	//CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist);
	FarFromPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist, std::string aName);
	~FarFromPlayerDecorator();

	void DoAction();
	bool CheckConditions();

private:
	float Range;

};