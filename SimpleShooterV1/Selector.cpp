#include "Selector.h"

Selector::Selector()
{

}

Selector::Selector(Blackboard* board) : super(board)
{
	
}

Selector::~Selector()
{

}

Tasks* Selector::ChooseNewTask()
{
	Tasks* task = nullptr;
	bool found = false;

	int currentPos = -1;

	std::vector<Tasks*>::iterator itr = std::find(controller->subtasks.begin(), controller->subtasks.end(), controller->currentTask);

	if (itr != controller->subtasks.cend())
	{
		currentPos = std::distance(controller->subtasks.begin(), itr);
	}

	while (!found)
	{
		if (currentPos == controller->subtasks.size() - 1)
		{
			found = true;
			task = nullptr;
			break;
		}

		currentPos++;

		task = controller->subtasks.at(currentPos);

		if (task->CheckConditions())
		{
			found = true;
		}

	}

	return task;
}

void Selector::ChildSucceeded()
{
	controller->FinishWithFailure();	
}

void Selector::ChildFailed()
{
	controller->currentTask = ChooseNewTask();

	if (controller->currentTask == nullptr)
	{
		controller->FinishWithFailure();
	}
}
