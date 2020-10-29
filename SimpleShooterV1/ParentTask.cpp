#include "ParentTask.h"

ParentTask::ParentTask()
{
}

ParentTask::ParentTask(Blackboard* enemyBoard) : super(enemyBoard)
{
	CreateController();
}

ParentTask::ParentTask(Blackboard* enemyBoard, std::string aName) : super(enemyBoard, aName)
{
	CreateController();
}

ParentTask::~ParentTask()
{
}

void ParentTask::CreateController()
{
	controller = new ParentTaskController(this);
}

TaskController* ParentTask::GetControl()
{
	return controller;
}



bool ParentTask::CheckConditions()
{
	//log here
	return controller->subtasks.size() > 0;
}

void ParentTask::DoAction()
{
	logText = ("GOING DOWN PARENT TREE (%s)", this->name);
	this->sLogger->Log(logText);
	if (controller->Finished())
	{

		logText = ("PARENT TASK CONTROLLER IS DONE");
		this->sLogger->Log(logText);
		return;
	}

	if (controller->currentTask == NULL)
	{
		logText = ("CURRENT TASK IS NULL");
		this->sLogger->Log(logText);

		//Null check
		return;
	}

	if (!controller->currentTask->GetControl()->Started())
	{
		logText = ("CURRENT TASK (%s) HAS NOT BEEN STARTED; STARTING", controller->currentTask->GetName());
		this->sLogger->Log(logText);

		//Task has not been started so start it
		controller->currentTask->GetControl()->SafeStart();
	}
	else if (controller->currentTask->GetControl()->Finished())
	{
		logText = ("CURRENT TASK (%s) HAS FINISHED", controller->currentTask->GetName());
		this->sLogger->Log(logText); 

		//Task has finished so end it
		controller->currentTask->GetControl()->SafeEnd();

		if (controller->currentTask->GetControl()->Succeeded())
		{
			logText = ("CURRENT TASK (%s) SUCCEEDED", controller->currentTask->GetName());
			this->sLogger->Log(logText);
			this->ChildSucceeded();
		}
		else if (controller->currentTask->GetControl()->Failed())
		{
			logText = ("CURRENT TASK (%s) FAILED", controller->currentTask->GetName());
			this->sLogger->Log(logText);
			this->ChildFailed();
		}
	}
	else
	{
		controller->currentTask->DoAction();
	}
	
}

void ParentTask::Start()
{
	logText = ("STARTING PARENT TREE");
	this->sLogger->Log(logText);

	for (Tasks* temp : controller->subtasks)
	{
		if (temp->CheckConditions())
		{
			logText = ("FOUND NEW TASK (%s)", temp->GetName());
			this->sLogger->Log(logText);
			controller->currentTask = temp;
			break;
		}
	}

	//controller->currentTask = controller->subtasks.front();

	if (controller->currentTask == NULL)
	{
		logText = ("NO NEW TASK FOUND");
		this->sLogger->Log(logText);
	}

}

void ParentTask::End()
{
	logText = ("PARENT TREE FINISHED; ENDING......");
	this->sLogger->Log(logText);
	//Log task ending
}
