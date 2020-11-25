/*
* A class that uses the Tasks class as a base
* 
* An extension of the Tasks class that allows for
* child tasks
*/

#include "ParentTask.h"
#include <sstream>

ParentTask::ParentTask()
{
}

//ParentTask::ParentTask(Blackboard* enemyBoard) : super(enemyBoard)
//{
//	CreateController();
//}

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
	std::ostringstream oss;
	if (controller->Finished())
	{
		return;
	}

	if (controller->currentTask == NULL)
	{
		oss << "CURRENT TASK IS NULL";
		this->sLogger->Log(oss.str());

		//Null check
		return;
	}

	if (!controller->currentTask->GetControl()->Started())
	{
		oss << "CURRENT TASK " << controller->currentTask->GetName() << " NOW STARTING";
		this->sLogger->Log(oss.str());

		//Task has not been started so start it
		controller->currentTask->GetControl()->SafeStart();
	}
	else if (controller->currentTask->GetControl()->Finished())
	{
		oss << "CURRENT TASK " << controller->currentTask->GetName() << " FINISHED";
		this->sLogger->Log(oss.str());

		std::ostringstream oss2;
		//Task has finished so end it
		controller->currentTask->GetControl()->SafeEnd();

		if (controller->currentTask->GetControl()->Succeeded())
		{
			oss2 << "CURRENT TASK " << controller->currentTask->GetName() << " SUCCEEDED";
			this->sLogger->Log(oss.str());
			this->ChildSucceeded();
		}
		else if (controller->currentTask->GetControl()->Failed())
		{
			oss2 << "CURRENT TASK " << controller->currentTask->GetName() << " FAILED";
			this->sLogger->Log(oss.str());
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
	std::ostringstream oss;

	for (Tasks* temp : controller->subtasks)
	{
		if (temp->CheckConditions())
		{
			oss << "FOUND NEW TASK " << temp->GetName();
			this->sLogger->Log(oss.str());

			controller->currentTask = temp;
			break;
		}
	}

	//controller->currentTask = controller->subtasks.front();

	if (controller->currentTask == NULL)
	{
		oss << "NO NEW TASK FOUND";
		this->sLogger->Log(oss.str());
	}

}

void ParentTask::End()
{
	std::ostringstream oss;
	oss << "PARENT TREE FINISHED";
	this->sLogger->Log(oss.str());
	//Log task ending
}

void ParentTask::SetBoardForAllSubtasks(Blackboard* newBoard)
{
	if (controller->subtasks.size() > 0)
	{
		for (Tasks* temp : controller->subtasks)
		{
			temp->SetBoard(newBoard);
		}
	}

}

