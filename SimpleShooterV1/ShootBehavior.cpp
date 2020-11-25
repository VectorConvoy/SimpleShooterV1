/*
* A class to represent a shoot-type behavior
* 
* Behavior that mainly contains the sequence for the AI to shoot
* 
* Main parameter is the chance percentage which randomly determines
* whether or not the AI shoots. The lower the better as a high percentage means
* the AI will shoot more often which can lead to impossible scenarios
*/

#include "ShootBehavior.h"
#include "ChanceDecorator.h"
#include "EnemyShootTask.h"
#include "FacePlayerTask.h"
#include "ChaseDestinationTask.h"
#include "Sequence.h"


ShootBehavior::ShootBehavior()
{
	SetPriorityID(0);
	SetName(DEFAULT_NAME);
}

ShootBehavior::ShootBehavior(Blackboard* board)
{
	SetPriorityID(0);
}

ShootBehavior::ShootBehavior(Blackboard* board, int chance)
{
	SetPriorityID(0);

	shootChance = chance;

	SetValue( (float) chance);

}

ShootBehavior::~ShootBehavior()
{
}

void ShootBehavior::SetShootChance(int chance)
{
	shootChance = chance;
	SetValue((float)chance);
}

int ShootBehavior::GetShootChance()
{
	return shootChance;
}

void ShootBehavior::ConstructBehavior()
{

	behaviorSequence = new Sequence(GetBoard(), "Shoot Sequence");

	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new ChaseDestinationTask(GetBoard(), "Chase Destination Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new FacePlayerTask(GetBoard(), "Face Player Task"));
	((ParentTaskController*)behaviorSequence->GetControl())->AddTask(new EnemyShootTask(GetBoard(), "Enemy Shoot Task"));

}
