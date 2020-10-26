#pragma once
#define _PANICDECORATOR_H

#include "TaskDecorator.h"

class PanicDecorator : public TaskDecorator
{
public:
	typedef TaskDecorator super;

	PanicDecorator();
	PanicDecorator(Blackboard* board, Tasks* newTask);
	PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist);
	~PanicDecorator();

	void DoAction();
	bool CheckConditions();

private:
	float PanicDistanceValue;
};