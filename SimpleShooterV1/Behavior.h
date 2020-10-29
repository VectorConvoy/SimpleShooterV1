#pragma once
#include "Tasks.h"
#define _BEHAVIOR_H

class Behavior
{
public:

	int priorityValue;
	Tasks* behaviorSequence;

	Behavior();
	~Behavior();

	void SetPriorityID(int priority);
	int GetPriorityID();


private:
};