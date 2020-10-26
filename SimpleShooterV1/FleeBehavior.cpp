#include "FleeBehavior.h"
#include "PanicDecorator.h"
#include "GetPlayerTask.h"
#include "FleeDestinationTask.h"
#include "MoveToTask.h"

FleeBehavior::FleeBehavior()
{
	priorityValue = -1;
	panicDistance = PANIC_DISTANCE;
}

FleeBehavior::FleeBehavior(Blackboard* board)
{
	priorityValue = 0;
	panicDistance = PANIC_DISTANCE;

	behaviorSequence = new Sequence(board);
	fleeSequence = new PanicDecorator(board, behaviorSequence, PANIC_DISTANCE);
	
	((ParentTaskController*)fleeSequence->GetControl())->AddTask(new GetPlayerTask(board));
	((ParentTaskController*)fleeSequence->GetControl())->AddTask(new FleeDestinationTask(board));
	((ParentTaskController*)fleeSequence->GetControl())->AddTask(new MoveToTask(board));
}

FleeBehavior::~FleeBehavior()
{
	delete fleeSequence;
	fleeSequence = nullptr;
}

void FleeBehavior::SetPanicDist(float dist)
{
	panicDistance = dist;
}

float FleeBehavior::GetPanicDist()
{
	return panicDistance;
}
