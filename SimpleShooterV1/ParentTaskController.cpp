#include "ParentTaskController.h"

ParentTaskController::ParentTaskController()
{
}

ParentTaskController::ParentTaskController(Tasks* task) : super(task)
{
	
	currentTask = NULL;
}

ParentTaskController::~ParentTaskController()
{
	delete currentTask;
	currentTask = NULL;

	for (Tasks* task : subtasks)
	{
		delete task;
		task = NULL;
	}

	subtasks.clear();
}

void ParentTaskController::AddTask(Tasks* newTask)
{
	subtasks.push_back(newTask);
}

void ParentTaskController::Reset()
{
	TaskController::Reset();
	currentTask = subtasks.front();
}
