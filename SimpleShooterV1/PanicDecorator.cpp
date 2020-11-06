#include "PanicDecorator.h"
#include "MathHelper.h"
#include "Blackboard.h"

PanicDecorator::PanicDecorator()
{
}

//PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask) : super(board, newTask)
//{
//	PanicDistanceValue = 0.0f;
//}

PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask, std::string aName) : super(board, newTask, aName)
{
	PanicDistanceValue = 0.0f;
}

//PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist) : super(board, newTask)
//{
//	PanicDistanceValue = panicDist;
//}

PanicDecorator::PanicDecorator(Blackboard* board, Tasks* newTask, float panicDist, std::string aName) : super(board, newTask, aName)
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

	Vector2 distanceSq = DistanceSquared(board->GetEnemy()->GetPosition(), board->GetPlayer()->GetPosition());

	return (this->task->CheckConditions() && (distanceSq.Magnitude() < panicDistanceSquared));
}

