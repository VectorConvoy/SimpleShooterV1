#pragma once
#define _RESETDECORATOR_H

#include "TaskDecorator.h"

class ResetDecorator : public TaskDecorator
{


public:
	typedef TaskDecorator super;
	ResetDecorator();
	ResetDecorator(Blackboard* bboard, Tasks* newTask);
	~ResetDecorator();

	void DoAction();
};