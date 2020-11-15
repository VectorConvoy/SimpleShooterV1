#include "SniperBehavior.h"
#include "PanicDecorator.h"
#include "GetPlayerTask.h"
#include "FleeDestinationTask.h"
#include "MoveToTask.h"
#include "Sequence.h"

SniperBehavior::SniperBehavior()
{

}

SniperBehavior::SniperBehavior(Blackboard* board)
{
	priorityValue = 0;
	
	fleeDistance = DEFAULT_FLEE_DIST;
	chaseDistance = DEFAULT_CHASE_DIST;

	behaviorSequence = new Sequence(board, "Sniper Sequence");
	behaviorSequence = new PanicDecorator(board, behaviorSequence, fleeDistance, "Panic Decorator");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FleeDestinationTask(board, "Get Flee Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));
}

SniperBehavior::~SniperBehavior()
{
}

void SniperBehavior::SetFleeDist(float dist)
{
}

float SniperBehavior::GetFleeDist()
{
	return 0.0f;
}

void SniperBehavior::SetChaseDist(float dist)
{
}
