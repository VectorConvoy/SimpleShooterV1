#include "FleeDestinationTask.h"
#include <stdio.h>
#include <sstream>
#include "Blackboard.h"

//FleeDestinationTask::FleeDestinationTask(Blackboard* board) : super(board)
//{
//	
//}

FleeDestinationTask::FleeDestinationTask(Blackboard* board, std::string aName) : super(board, aName)
{

}

FleeDestinationTask::~FleeDestinationTask()
{
}

bool FleeDestinationTask::CheckConditions()
{
	bool check = (board->GetPlayer() != NULL && board->GetEnemy() != NULL);

	return check;
}

void FleeDestinationTask::Start()
{
	std::ostringstream oss;
	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());

}

void FleeDestinationTask::End()
{
	std::ostringstream oss;
	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}

void FleeDestinationTask::DoAction()
{
	std::ostringstream oss;

	oss << "PERFORMING TASK " << name;
	this->sLogger->Log(oss.str());

	Vector2 enemyPos = this->board->GetEnemy()->GetPosition();
	Vector2 playerPos = this->board->GetPlayer()->GetPosition();
	
	//Calculate Flee Vector
	Vector2 distanceSq = DistanceSquared(enemyPos, playerPos);
	Vector2 desiredVelocity = ((Vector2)enemyPos - playerPos).Normalized();

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
