#include "SeekBehavior.h"
#include "Sequence.h"
#include "GetPlayerTask.h"
#include "MoveToTask.h"
#include "ChaseDestinationTask.h"
#include "FarFromPlayerDecorator.h"
#include "FacePlayerTask.h"

SeekBehavior::SeekBehavior()
{
}

SeekBehavior::SeekBehavior(Blackboard* board)
{
	priorityValue = 0;
	pursuitDist = 0.0f;

	behaviorSequence = new Sequence(board, "Chase Sequence");
	//behaviorSequence = new FarFromPlayerDecorator(board, behaviorSequence, SEEK_DISTANCE, "Chase Decorator");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(board, "Get Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(board, "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));

}

SeekBehavior::SeekBehavior(Blackboard* board, float seekDist)
{
	priorityValue = 0;
	pursuitDist = seekDist;

	behaviorSequence = new Sequence(board, "Chase Sequence");
	//behaviorSequence = new FarFromPlayerDecorator(board, behaviorSequence, seekDist, "Chase Decorator");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(board, "Get Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(board, "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));
}

SeekBehavior::SeekBehavior(Blackboard* board, float seekDist, TaskDecorator customDeco)
{
	priorityValue = 0;
	pursuitDist = seekDist;

	behaviorSequence = new Sequence(board, "Chase Sequence");
	//behaviorSequence = new FarFromPlayerDecorator(board, behaviorSequence, seekDist, "Chase Decorator");

	//((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new GetPlayerTask(board, "Get Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(board, "Get Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(board, "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new MoveToTask(board, "Move Enemy Tasks"));
}



SeekBehavior::~SeekBehavior()
{
	delete chaseSequence;
	chaseSequence = nullptr;
}

void SeekBehavior::SetSeekDist(float dist)
{
	pursuitDist = dist;
}

float SeekBehavior::GetSeekDist()
{
	return pursuitDist;
}
