#include "FleeBehavior.h"
#include "PanicDecorator.h"
#include "GetPlayerTask.h"
#include "FleeDestinationTask.h"
#include "MoveToTask.h"
#include "Sequence.h"

FleeBehavior::FleeBehavior()
{
	priorityValue = -1;
	panicDistance = PANIC_DISTANCE;
}

FleeBehavior::FleeBehavior(Blackboard* board)
{
	priorityValue = 0;
	panicDistance = PANIC_DISTANCE;

	behaviorSequence = new Sequence(board, "Flee Sequence");
	behaviorSequence = new PanicDecorator(board, behaviorSequence, PANIC_DISTANCE, "Panic Decorator");
	
	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FleeDestinationTask(board, "Get Flee Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));
}

FleeBehavior::~FleeBehavior()
{
	
}

void FleeBehavior::SetPanicDist(float dist)
{
	panicDistance = dist;
}

float FleeBehavior::GetPanicDist()
{
	return panicDistance;
}
