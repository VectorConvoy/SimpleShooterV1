#include "MoveToTask.h"
#include <sstream>

//MoveToTask::MoveToTask(Blackboard* board) : super(board)
//
//{
//
//}

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
	std::ostringstream oss;
	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());
}

void MoveToTask::End()
{
	std::ostringstream oss;
	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}

void MoveToTask::DoAction()
{
	std::ostringstream oss;
	oss << "PERFORMING TASK " << name;
	this->sLogger->Log(oss.str());

	board->GetEnemy()->SetEnemyDestVector(board->GetMoveDirection());


	if (board->GetMoveDirection() != NULL || board->GetMoveDirection() == VEC2_ZERO)
	{
		this->controller->FinishWithSuccess();
	}
	else
	{
		this->controller->FinishWithFailure();
	}
}
