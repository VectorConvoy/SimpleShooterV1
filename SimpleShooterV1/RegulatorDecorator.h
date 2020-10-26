#pragma once
#define _REGULATOR_H

#include "TaskDecorator.h"

class RegulatorDecorator : public TaskDecorator
{
public:
	typedef TaskDecorator super;
	RegulatorDecorator();
	RegulatorDecorator(Blackboard* board, Tasks* task, float UpdateTime);
	~RegulatorDecorator();

	void DoAction();

	void Start();
	void End();

private:
	float updateTime; //In frames (0.1 = 10 frames)
};