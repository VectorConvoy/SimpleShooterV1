#include "TaskDecorator.h"

TaskDecorator::TaskDecorator()
{
}

TaskDecorator::TaskDecorator(Blackboard* board, Tasks* newTask) : super(board)
{
	InitiateTask(newTask);
}

TaskDecorator::TaskDecorator(Blackboard* board, Tasks* newTask, std::string aName) : super(board, aName)
{
	InitiateTask(newTask);
}

TaskDecorator::~TaskDecorator()
{
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

void TaskDecorator::InitiateTask(Tasks* taskToInit)
{
	task = taskToInit;

	task->GetControl()->SetTask(this);
}