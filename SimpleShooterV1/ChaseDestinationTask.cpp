#include "ChaseDestinationTask.h"
#include <sstream>

//ChaseDestinationTask::ChaseDestinationTask(Blackboard* board) : super(board)
//{
//
//}

ChaseDestinationTask::ChaseDestinationTask(Blackboard* board, std::string aName) : super(board, aName)
{
}

ChaseDestinationTask::~ChaseDestinationTask()
{
}

bool ChaseDestinationTask::CheckConditions()
{
	bool check = (board->GetPlayer() != NULL && board->GetEnemy() != NULL);

	return check;
}

void ChaseDestinationTask::Start()
{
	std::ostringstream oss;
	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());
}

void ChaseDestinationTask::End()
{
	std::ostringstream oss;
	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}

void ChaseDestinationTask::DoAction()
{
	Vector2 enemyPos = this->board->GetEnemy()->GetPosition();
	Vector2 playerPos = this->board->GetPlayer()->GetPosition();

	Vector2 desiredVelocity = ((Vector2)playerPos - enemyPos).Normalized();

	//Save the vector to the blackboard
	this->board->SetMoveDirection(desiredVelocity);

	if (desiredVelocity != NULL)
	{
		this->GetControl()->FinishWithSuccess();
	}
	else
	{
		this->GetControl()->FinishWithFailure();
	}
}
