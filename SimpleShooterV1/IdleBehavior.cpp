#include "IdleBehavior.h"
#include "Sequence.h"
#include "IdleTask.h"
#include "MoveToTask.h"

IdleBehavior::IdleBehavior()
{

}

IdleBehavior::IdleBehavior(Blackboard* board) 
{
	priorityValue = 0;

	behaviorSequence = new Sequence(board, "Idle Sequence");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new IdleTask(board, "Idle Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));
}

IdleBehavior::~IdleBehavior()
{
}
