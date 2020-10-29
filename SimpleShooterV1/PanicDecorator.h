#pragma once
#define _PANICDECORATOR_H

#include "TaskDecorator.h"

class PanicDecorator : public TaskDecorator
{
public:
	typedef TaskDecorator super;

	PanicDecorator();
	PanicDecorator(Blackboard* board, Tasks* newTask);
	PanicDecorator(Blackboard* board, Tasks* newTask, std::string aName);
	PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist);
	PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist, std::string aName);
	~PanicDecorator();

	void DoAction();
	bool CheckConditions();

private:
	float PanicDistanceValue;
};