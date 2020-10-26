#include "Behavior.h"

Behavior::Behavior()
{
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
