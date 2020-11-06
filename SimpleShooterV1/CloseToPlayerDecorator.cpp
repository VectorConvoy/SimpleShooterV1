#include "CloseToPlayerDecorator.h"
#include "MathHelper.h"
#include "Blackboard.h"

CloseToPlayerDecorator::CloseToPlayerDecorator()
{
	HomingRange = 0.0f;
}

//CloseToPlayerDecorator::CloseToPlayerDecorator(Blackboard* board, Tasks* newTask) : super(board, newTask)
//{
//	HomingRange = 0.0f;
//}

CloseToPlayerDecorator::CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, std::string aName) : super(board, newTask, aName)
{
	HomingRange = 0.0f;
}

//CloseToPlayerDecorator::CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist) : super(board, newTask)
//{
//	HomingRange = 0.0f;
//}

CloseToPlayerDecorator::CloseToPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist, std::string aName) : super(board, newTask, aName)
{
	HomingRange = chaseDist;
}

CloseToPlayerDecorator::~CloseToPlayerDecorator()
{

}

void CloseToPlayerDecorator::DoAction()
{
	task->DoAction();
}

bool CloseToPlayerDecorator::CheckConditions()
{
	float chaseDistanceSquared = pow(HomingRange, 2);

	Vector2 distanceSq = DistanceSquared(board->GetEnemy()->GetPosition(), board->GetPlayer()->GetPosition());

	sLogger->Log(this->task->CheckConditions() && (distanceSq.Magnitude() >= chaseDistanceSquared) ? "ENEMY NOT CLOSE TO PLAYER; CHASING" : "ENEMY CLOSE TO PLAYER; DO NOT CHASE");

	return (this->task->CheckConditions() && (distanceSq.Magnitude() >= chaseDistanceSquared));
}
