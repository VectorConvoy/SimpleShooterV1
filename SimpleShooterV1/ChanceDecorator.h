#pragma once
#define _CHANCEDECORATOR_H

#include "TaskDecorator.h"
#include <ctime>

class ChanceDecorator : public TaskDecorator
{
public:
	typedef TaskDecorator super;

	ChanceDecorator();
	//ChanceDecorator(Blackboard* board, Tasks* task, int chance = 10);
	ChanceDecorator(Blackboard* board, Tasks* task, std::string aName, int chance = 5);

	~ChanceDecorator();

	void DoAction();
	bool CheckConditions();

private:
	const int CHANCE_RANGE = 100;
	const int DEFAULT_CHANCE = 5;

	int chanceValue; //Value to represent what the chances are the action will be performed out of 100
	int randomValue; //Value that will be used to compare with the chance value to determine if the action will be performed

	void Initialize(int chance);
};