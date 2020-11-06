#include "Behavior.h"
#include "Sequence.h"

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

void Behavior::AddAdditionalSequence(Tasks* newTask)
{
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(newTask);
}
