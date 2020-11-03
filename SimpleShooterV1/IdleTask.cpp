#include "IdleTask.h"

IdleTask::IdleTask()
{
}

IdleTask::IdleTask(Blackboard* blackboard) : super(blackboard)
{
}

IdleTask::IdleTask(Blackboard* blackboard, std::string aName) : super(blackboard, aName)
{
}

IdleTask::~IdleTask()
{
}

bool IdleTask::CheckConditions()
{
	bool check = (board->GetEnemy() != NULL) ? true : false;

	return check;
}

void IdleTask::DoAction()
{
	//Set the vector to the Zero Vector into the blackboard
	this->board->SetMoveDirection(VEC2_ZERO);

	if (this->board->GetMoveDirection() != NULL)
	{
		this->GetControl()->FinishWithSuccess();
	}
	else
	{
		this->GetControl()->FinishWithFailure();
	}
}

void IdleTask::Start()
{
	logText = ("STARTING %s TASK", name);
	this->sLogger->Log(logText);
}

void IdleTask::End()
{
	logText = ("ENDING %s TASK", name);
	this->sLogger->Log(logText);
}
