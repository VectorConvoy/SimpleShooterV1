#include "Sequence.h"

Sequence::Sequence()
{
}

//Sequence::Sequence(Blackboard* enemyBoard) : super(enemyBoard)
//{
//	
//}

Sequence::Sequence(Blackboard* enemyBoard, std::string aName) : super(enemyBoard, aName)
{

}

Sequence::~Sequence()
{

}

void Sequence::ChildFailed()
{
	controller->FinishWithFailure();
}

void Sequence::ChildSucceeded()
{
	int currentPos = -1;

	std::vector<Tasks*>::iterator itr = std::find(controller->subtasks.begin(), controller->subtasks.end(), controller->currentTask);

	if (itr != controller->subtasks.cend())
	{
		currentPos = std::distance(controller->subtasks.begin(), itr);
	}

	if (currentPos == controller->subtasks.size() - 1)
	{
		controller->FinishWithSuccess();
	}
	else
	{
		controller->currentTask = controller->subtasks.at(currentPos + 1);

		if (!controller->currentTask->CheckConditions())
		{
			controller->FinishWithFailure();
		}
	}
}
