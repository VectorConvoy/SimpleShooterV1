#include "TaskController.h"
#include "Tasks.h"

TaskController::TaskController()
{
}

TaskController::TaskController(Tasks* task)
{
}

TaskController::~TaskController()
{
}

void TaskController::SetTask(Tasks* newTask)
{
	task = newTask;
}

Tasks* TaskController::GetTask()
{
	return nullptr;
}

void TaskController::SafeStart()
{	
	started = true;

	task->Start();

}

void TaskController::SafeEnd()
{
	done = false;
	started = false;
	task->End();
}

bool TaskController::Succeeded()
{
	return success;
}

bool TaskController::Failed()
{
	return !success;
}

bool TaskController::Started()
{
	return started;
}

bool TaskController::Finished()
{
	return done;
}

void TaskController::Reset()
{
	done = false;
}

void TaskController::Initialize()
{
	done = false;
	success = false;
	started = false;
}

void TaskController::FinishWithSuccess()
{
	success = true;
	done = true;
	//Log Task here
}

void TaskController::FinishWithFailure()
{
	success = false;
	done = true;

	//log task
}
