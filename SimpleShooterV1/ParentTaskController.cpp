#include "ParentTaskController.h"

ParentTaskController::ParentTaskController()
{
	currentTask = NULL;
}

ParentTaskController::ParentTaskController(Tasks* task) : super(task)
{
	currentTask = NULL;
}

ParentTaskController::ParentTaskController(Tasks* task, std::string aName) : super(task, aName)
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
	this->GetLogger()->Log(("ADDING TASK (%s) TO PARENT TASK CONTROLLER - %s", newTask->GetName(), this->name));
	subtasks.push_back(newTask);
}

void ParentTaskController::Reset()
{
	this->GetLogger()->Log(("RESETTING PARENT TASK CONTROLLER - %s", this->name));

	TaskController::Reset();
	currentTask = nullptr;
}
