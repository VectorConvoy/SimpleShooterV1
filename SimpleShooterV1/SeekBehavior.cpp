/*
* A class to represent a seek behavior
* for the AI
* 
* Behavior that seeks out the player and chase them until
* a specific distance or indefinitely
*/

#include "SeekBehavior.h"
#include "Sequence.h"
#include "GetPlayerTask.h"
#include "MoveToTask.h"
#include "ChaseDestinationTask.h"
#include "FacePlayerTask.h"

SeekBehavior::SeekBehavior()
{
	SetName(DEFAULT_NAME);
	
}

SeekBehavior::SeekBehavior(Blackboard* board)
{
	SetPriorityID(0);
	pursuitDist = 0.0f;
	SetValue(0.0f);

}

SeekBehavior::SeekBehavior(Blackboard* board, float seekDist)
{
	SetPriorityID(0);
	pursuitDist = seekDist;
	SetValue(seekDist);

}

SeekBehavior::SeekBehavior(Blackboard* board, float seekDist, TaskDecorator customDeco)
{
	SetPriorityID(0);
	pursuitDist = seekDist;
	SetValue(seekDist);

}

SeekBehavior::~SeekBehavior()
{

}

void SeekBehavior::SetSeekDist(float dist)
{
	pursuitDist = dist;
}

float SeekBehavior::GetSeekDist()
{
	return pursuitDist;
}

void SeekBehavior::ConstructBehavior()
{
	behaviorSequence = new Sequence(GetBoard(), "Chase Sequence");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(GetBoard(), "Get Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(GetBoard(), "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(GetBoard(), "Move Enemy Tasks"));
}
