/*
* A class to represent the behavior of an AI
* Base class that contains a priority value and
* the sequence the AI should execute
*/
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

void Behavior::SetName(std::string name)
{
	behaviorName = name;
}

std::string Behavior::GetName()
{
	return behaviorName;
}

void Behavior::SetBoard(Blackboard* newBoard)
{
	board = newBoard;
	behaviorSequence->SetBoard(newBoard);
	//((ParentTask*)behaviorSequence)->SetBoardForAllSubtasks(newBoard);

	for (Tasks* aTask : ((ParentTaskController*)behaviorSequence->GetControl())->subtasks)
	{
		aTask->SetBoard(newBoard);
	}
}

Blackboard* Behavior::GetBoard()
{
	return board;
}

void Behavior::SetValue(float newValue)
{
	value = newValue;
}

float Behavior::GetValue()
{
	return value;
}

void Behavior::SetConditionType(std::string condType)
{
	conditionType = condType;
}

std::string Behavior::GetConditionType()
{
	return conditionType;
}

/// <summary>
/// Function to add a task/sequence to 
/// the AI's controller
/// </summary>
/// <param name="newTask"></param>
void Behavior::AddAdditionalSequence(Tasks* newTask)
{
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(newTask);
}

