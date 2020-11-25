/*
* A class that wraps around a task 
* to add additional functionality
* 
* Most uses add in a condition that 
* only executes the task if passed
* 
*/

#include "TaskDecorator.h"

TaskDecorator::TaskDecorator()
{
}

//TaskDecorator::TaskDecorator(Blackboard* board, Tasks* newTask) : super(board)
//{
//	InitiateTask(newTask);
//}

TaskDecorator::TaskDecorator(Blackboard* board, Tasks* newTask, std::string aName) : super(board, aName)
{
	InitiateTask(newTask);
}

TaskDecorator::~TaskDecorator()
{
	task = nullptr;
}

bool TaskDecorator::CheckConditions()
{
	return this->task->CheckConditions();
}

void TaskDecorator::Start()
{
	task->Start();
}

void TaskDecorator::End()
{
	task->End();
}

TaskController* TaskDecorator::GetControl()
{
	return task->GetControl();
}

Tasks* TaskDecorator::RemoveDecorator(TaskDecorator* deco)
{
	if (task != NULL)
	{
		return task;
	}
	else
	{
		return nullptr;
	}
}

void TaskDecorator::InitiateTask(Tasks* taskToInit)
{
	task = taskToInit;

	task->GetControl()->SetTask(this);
}
