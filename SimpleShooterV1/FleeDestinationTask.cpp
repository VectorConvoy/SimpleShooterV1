#include "FleeDestinationTask.h"

FleeDestinationTask::FleeDestinationTask(Blackboard* board)
{
}

FleeDestinationTask::~FleeDestinationTask()
{
}

bool FleeDestinationTask::CheckConditions()
{
	bool check = (this->board->GetPlayer() != NULL && this->board->GetEnemy() != NULL);

	return check;
}

void FleeDestinationTask::Start()
{
	//Log start
	printf("\n*****************************************************************************************************\n");
	printf("GETTING FLEE DESTINATION VECTOR");
	printf("\n*****************************************************************************************************\n");

}

void FleeDestinationTask::End()
{
	//Log end
	printf("\n*****************************************************************************************************\n");
	printf("FINISHED GETTING FLEE DESTINATION VECTOR");
	printf("\n*****************************************************************************************************\n");
}

void FleeDestinationTask::DoAction()
{
	Vector2 enemyPos = this->board->GetEnemy()->GetPosition();
	Vector2 playerPos = this->board->GetPlayer()->GetPosition();
	
	//Calculate Flee Vector
	Vector2 distanceSq = DistanceSquared(enemyPos, playerPos);
	Vector2 desiredVelocity = ((Vector2)enemyPos - playerPos).Normalized();

	//Save the vector to the blackboard
	this->board->SetMoveDirection(desiredVelocity);
	

}
