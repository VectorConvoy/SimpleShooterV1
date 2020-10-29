#include "Behavior.h"

Behavior::Behavior()
{
	behaviorSequence = nullptr;
}

Behavior::~Behavior()
{

}

void Behavior::SetPriorityID(int priority)
{
	priorityValue = priority;
}

int Behavior::GetPriorityID()
{
	return priorityValue;
}
