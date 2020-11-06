#include "TaskController.h"
#include "Tasks.h"
#include <stdio.h>
#include <sstream>

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
	std::ostringstream oss;
	oss << "SETTING TASK  " << newTask->GetName() << " IN TASK CONTROLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());
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
	std::ostringstream oss;
	oss << "SAFE STARTING TASK CONTROLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());
	started = true;

	task->Start();

}

void TaskController::SafeEnd()
{
	std::ostringstream oss;
	oss << "SAFE ENDING TASK CONTROLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());
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
	std::ostringstream oss;
	oss << "INITIALIZING TASK CONTROLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());

	done = false;
	success = false;
	started = false;
}

void TaskController::FinishWithSuccess()
{
	success = true;
	done = true;

	std::ostringstream oss;
	oss << "TASK " << task->GetName() << " FINISHED SUCCESSFULLY FROM TASK CONTORLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());
}

void TaskController::FinishWithFailure()
{
	success = false;
	done = true;

	std::ostringstream oss;
	oss << "TASK " << task->GetName() << " FINISHED WITH FAILURE FROM TASK CONTROLLER " << this->name;
	this->sLoggerInstance->Log(oss.str());
	//log task
}
