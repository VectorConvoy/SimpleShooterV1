#pragma once
#define _FLEEDESTINATION_H


#include "Tasks.h"

class FleeDestinationTask : public Tasks
{
public:
	FleeDestinationTask(Blackboard* board);
	~FleeDestinationTask();

	bool CheckConditions();
	void Start();
	void End();
	void DoAction();

};