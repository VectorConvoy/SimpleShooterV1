#include "PanicDecorator.h"

PanicDecorator::PanicDecorator()
{
}

PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask) : super(board, newTask)
{
	PanicDistanceValue = 0.0f;
}

PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist) : super(board, newTask)
{
	PanicDistanceValue = panicDist;
}

PanicDecorator::~PanicDecorator()
{
}

void PanicDecorator::DoAction()
{
	task->DoAction();
}

bool PanicDecorator::CheckConditions()
{
	float panicDistanceSquared = pow(PanicDistanceValue, 2);
	//Vector2 distanceSq = DistanceSquared(entityPos, targetPos);
	Vector2 distanceSq = DistanceSquared(board->GetEnemy()->GetPosition(), board->GetPlayer()->GetPosition());

	
	
	return (TaskDecorator::CheckConditions() && (distanceSq.Magnitude() > panicDistanceSquared));
}

