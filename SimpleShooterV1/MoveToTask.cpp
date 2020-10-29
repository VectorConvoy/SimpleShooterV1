#include "MoveToTask.h"

MoveToTask::MoveToTask(Blackboard* board) : super(board)

{

}

MoveToTask::MoveToTask(Blackboard* board, std::string aName) : super(board, aName)
{
}

MoveToTask::~MoveToTask()
{
}

bool MoveToTask::CheckConditions()
{
	bool check = board->GetEnemy()->GetActive();


	return check;
}

void MoveToTask::Start()
{
	logText = ("STARTING %s TASK", name);
	this->sLogger->Log(logText);
}

void MoveToTask::End()
{
	logText = ("ENDING %s TASK", name);
	this->sLogger->Log(logText);
}

void MoveToTask::DoAction()
{
	logText = ("PERFORMING %s TASK", name);
	this->sLogger->Log(logText);

	board->GetEnemy()->SetEnemyDestVector(board->GetMoveDirection());


	if (board->GetMoveDirection() != NULL)
	{
		this->controller->FinishWithSuccess();
	}
	else
	{
		this->controller->FinishWithFailure();
	}
}
