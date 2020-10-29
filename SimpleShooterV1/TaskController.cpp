#include "TaskController.h"
#include "Tasks.h"
#include <stdio.h>

TaskController::TaskController()
{
	sLoggerInstance = Logger::Instance();
	name = "UNKNOWN TASK CONTROLLER";
	Initialize();
}

TaskController::TaskController(Tasks* task)
{
	sLoggerInstance = Logger::Instance();
	name = "UNKNOWN TASK CONTROLLER";
	SetTask(task);
	Initialize();
}

TaskController::TaskController(Tasks* task, std::string aName)
{
	sLoggerInstance = Logger::Instance();
	name = aName;
	SetTask(task);
	Initialize();
}

TaskController::~TaskController()
{
	sLoggerInstance = nullptr;
}

void TaskController::SetTask(Tasks* newTask)
{
	this->sLoggerInstance->Log(("SETTING TASK (%s) IN TASK CONTROLLER - %s", newTask->GetName(), this->name));
	task = newTask;
}

Logger* TaskController::GetLogger()
{
	if (sLoggerInstance == nullptr)
	{
		sLoggerInstance = Logger::Instance();
	}
	return sLoggerInstance;
}

void TaskController::SafeStart()
{	
	
	this->sLoggerInstance->Log(("SAFE STARTING TASK CONTROLLER - %s", this->name));
	started = true;

	task->Start();

}

void TaskController::SafeEnd()
{
	this->sLoggerInstance->Log(("SAFE ENDING TASK CONTROLLER - %s", this->name));

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
	success = false;
	started = false;
}

void TaskController::Initialize()
{
	
	this->sLoggerInstance->Log(("INITIALIZING TASK CONTROLLER - %s", this->name));

	done = false;
	success = false;
	started = false;
}

void TaskController::FinishWithSuccess()
{
	success = true;
	done = true;
	//Log Task here
	this->sLoggerInstance->Log(("TASK (%s) FINISHED SUCCESSFULLY  FROM TASK CONTROLLER - %s", task->GetName(), this->name));

}

void TaskController::FinishWithFailure()
{
	success = false;
	done = true;
	this->sLoggerInstance->Log(("TASK (%s) FINISHED WITH FAILURE  FROM TASK CONTROLLER - %s", task->GetName(), this->name));

	//log task
}
