#include "ParentTask.h"

ParentTask::ParentTask()
{
}

ParentTask::ParentTask(Blackboard* enemyBoard) : super(enemyBoard)
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
	if (controller->Finished())
	{
		return;
	}

	if (controller->currentTask == NULL)
	{
		//Null check
		return;
	}

	if (!controller->currentTask->GetControl()->Started())
	{
		//Task has not been started so start it
		controller->currentTask->GetControl()->SafeStart();
	}
	else if (controller->currentTask->GetControl()->Finished())
	{
		//Task has finished so end it
		controller->currentTask->GetControl()->SafeEnd();

		if (controller->currentTask->GetControl()->Succeeded())
		{
			this->ChildSucceeded();
		}
		
		if (controller->currentTask->GetControl()->Failed())
		{
			this->ChildFailed();
		}
		else
		{
			controller->currentTask->DoAction();
		}
	}
}

void ParentTask::Start()
{
	//Log here
	controller->currentTask = controller->subtasks.front();

	if (controller->currentTask == NULL)
	{
		//Null check
	}

}

void ParentTask::End()
{
	//Log task ending
}
