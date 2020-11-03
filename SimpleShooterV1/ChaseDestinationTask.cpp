#include "ChaseDestinationTask.h"

ChaseDestinationTask::ChaseDestinationTask(Blackboard* board)
{

}

ChaseDestinationTask::ChaseDestinationTask(Blackboard* board, std::string aName)
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
	logText = ("STARTING %s TASK", name);
	this->sLogger->Log(logText);
}

void ChaseDestinationTask::End()
{
	logText = ("ENDING %s TASK", name);
	this->sLogger->Log(logText);
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
