/*
* A class to represent a flee-type behavior
* for the AI where the AI flees given a 
* panic distance
*/
#include "FleeBehavior.h"
#include "FaceAwayPlayerTask.h"
#include "FleeDestinationTask.h"
#include "MoveToTask.h"
#include "Sequence.h"

FleeBehavior::FleeBehavior()
{
	SetName(DEFAULT_NAME);
	panicDistance = PANIC_DISTANCE;
}

FleeBehavior::FleeBehavior(Blackboard* board)
{
	SetName(DEFAULT_NAME);
	panicDistance = PANIC_DISTANCE;

	SetBoard(board);
	SetValue(PANIC_DISTANCE);
}

FleeBehavior::FleeBehavior(Blackboard* board, float fleeDist)
{
	SetName(DEFAULT_NAME);
	panicDistance = fleeDist;

	SetBoard(board);
	SetValue(fleeDist);
}

FleeBehavior::~FleeBehavior()
{
	
}

void FleeBehavior::SetPanicDist(float dist)
{
	panicDistance = dist;

	SetValue(dist);
}

float FleeBehavior::GetPanicDist()
{
	return panicDistance;
}

void FleeBehavior::ConstructBehavior()
{
	behaviorSequence = new Sequence(GetBoard(), "Flee Sequence");

	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FaceAwayPlayerTask(GetBoard(), "Face Away from Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FleeDestinationTask(GetBoard(), "Get Flee Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(GetBoard(), "Move Enemy Tasks"));
}


