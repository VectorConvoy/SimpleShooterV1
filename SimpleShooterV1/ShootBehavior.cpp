#include "ShootBehavior.h"
#include "ChanceDecorator.h"
#include "EnemyShootTask.h"
#include "FacePlayerTask.h"
#include "ChaseDestinationTask.h"
#include "Sequence.h"


ShootBehavior::ShootBehavior()
{
	
}

ShootBehavior::ShootBehavior(Blackboard* board)
{
	priorityValue = 0;

	behaviorSequence = new Sequence(board, "Shoot Sequence");
	behaviorSequence = new ChanceDecorator(board, behaviorSequence, "Chance Decorator");

	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(board, "Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(board, "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new EnemyShootTask(board, "Enemy Shoot Task"));
}

ShootBehavior::~ShootBehavior()
{
}

void ShootBehavior::SetShootChance(int chance)
{
	shootChance = chance;
}

int ShootBehavior::GetShootChance()
{
	return shootChance;
}
