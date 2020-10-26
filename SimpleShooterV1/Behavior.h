#pragma once
#include "Sequence.h"
#define _BEHAVIOR_H

class Behavior
{
public:

	int priorityValue;
	Sequence* behaviorSequence;

	Behavior();
	~Behavior();

	void SetPriorityID(int priority);
	int GetPriorityID();


private:
};