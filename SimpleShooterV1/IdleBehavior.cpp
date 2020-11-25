/*
* A class to represent an idle behavior
* for the AI
* 
* Mainly added to the end of a specific type of behavior
* so the AI simply idles if all other conditions have failed
*/

#include "IdleBehavior.h"
#include "Sequence.h"
#include "IdleTask.h"
#include "MoveToTask.h"

IdleBehavior::IdleBehavior()
{
	SetPriorityID(0);
	SetName(DEFAULT_NAME);
}

IdleBehavior::IdleBehavior(Blackboard* board) 
{
	SetPriorityID(-1);
	SetName(DEFAULT_NAME);
}

IdleBehavior::~IdleBehavior()
{

}

void IdleBehavior::ConstructBehavior()
{
	behaviorSequence = new Sequence(GetBoard(), "Idle Sequence");

	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new IdleTask(GetBoard(), "Idle Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(GetBoard(), "Move Enemy Tasks"));
}
