#include "FarFromPlayerDecorator.h"
#include "Blackboard.h"
#include "MathHelper.h"

FarFromPlayerDecorator::FarFromPlayerDecorator()
{
	Range = 0.0f;
}

FarFromPlayerDecorator::FarFromPlayerDecorator(Blackboard* board, Tasks* newTask, std::string aName) : super(board, newTask, aName)
{
	Range = 0.0f;
}

FarFromPlayerDecorator::FarFromPlayerDecorator(Blackboard* board, Tasks* newTask, float chaseDist, std::string aName) : super(board, newTask, aName)
{
	Range = chaseDist;
}

FarFromPlayerDecorator::~FarFromPlayerDecorator()
{
}

void FarFromPlayerDecorator::DoAction()
{
	task->DoAction();
}

bool FarFromPlayerDecorator::CheckConditions()
{
	float distanceSquared = pow(Range, 2);

	Vector2 distanceSq = DistanceSquared(board->GetEnemy()->GetPosition(), board->GetPlayer()->GetPosition());

	sLogger->Log(this->task->CheckConditions() && (distanceSq.Magnitude() >= distanceSquared) ? "PLAYER FAR ENOUGH" : "PLAYER NOT FAR ENOUGH");

	return (this->task->CheckConditions() && (distanceSq.Magnitude() >= distanceSquared));
}
