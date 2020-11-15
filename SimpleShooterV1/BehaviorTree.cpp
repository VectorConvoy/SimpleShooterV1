#include "BehaviorTree.h"
#include "ChanceDecorator.h"
#include "FleeBehavior.h"
#include "SeekBehavior.h"
#include "ShootBehavior.h"
#include "IdleBehavior.h"
#include "GetPlayerTask.h"
#include "IdleTask.h"
#include <algorithm>

BehaviorTree::BehaviorTree()
{
	AIBoard = new Blackboard();
	AISelector = new Selector(AIBoard, "DEFAULT BEHAVIOR TREE");
	CreateBehaviorTree();
}

BehaviorTree::BehaviorTree(Enemy* owner)
{
	AIBoard = new Blackboard();
	AIBoard->SetEnemy(owner);
	GetPlayer = new GetPlayerTask(AIBoard, "Get Player Task");
	AISelector = new Selector(AIBoard, "AI Selector");

}

BehaviorTree::~BehaviorTree()
{
	delete AIBoard;
	AIBoard = nullptr;

	delete AISelector;
	AISelector = nullptr;
}

void BehaviorTree::CreateBehaviorTree(BEHAVIOR_TYPES behavior)
{

	//std::transform(behaviorType.begin(), behaviorType.end(), behaviorType.begin(), [](unsigned char c) {return std::tolower(c); });

	if (behavior == BEHAVIOR_TYPES::flee)
	{
		//this->sLoggerInstance->Log("ADDING FLEE BEHAVIOR");
		AddBehaviorToBehaviorTree(new FleeBehavior(AIBoard));

	}
	else if (behavior == BEHAVIOR_TYPES::chase)
	{
		//this->sLoggerInstance->Log("ADDING CHASE BEHAVIOR");
		AddBehaviorToBehaviorTree(new SeekBehavior(AIBoard));
	}
	else if (behavior == BEHAVIOR_TYPES::chase_shoot)
	{
		//this->sLoggerInstance->Log("ADDING CHASE & FIRE BEHAVIOR");
		SeekBehavior* temp = new SeekBehavior(AIBoard);
		temp->AddAdditionalSequence((new ShootBehavior(AIBoard))->behaviorSequence);
		AddBehaviorToBehaviorTree(temp);

		temp = nullptr;
	}
	else if (behavior == BEHAVIOR_TYPES::sentry)
	{
		AddBehaviorToBehaviorTree(new ShootBehavior(AIBoard));
	}
	else if (behavior == BEHAVIOR_TYPES::sniper)
	{
		SeekBehavior* seek = new SeekBehavior(AIBoard, 10.0f);
		CloseToPlayerDecorator* close = new CloseToPlayerDecorator(AIBoard, seek->behaviorSequence, 200.0f, "Seek Close To Player Decorator Sequence");

		FleeBehavior* flee = new FleeBehavior(AIBoard, 500.0f);
		ShootBehavior* shoot = new ShootBehavior(AIBoard, 5);

		AddTaskToBehaviorTree(close);

		//AddBehaviorToBehaviorTree(seek);
		AddBehaviorToBehaviorTree(flee);
		AddBehaviorToBehaviorTree(shoot);

		//AddBehaviorToBehaviorTree(new SeekBehavior(AIBoard));


	}

	//Add Idle Task so if AI does not pass any decorators simply have it idle at current position
	AddBehaviorToBehaviorTree(new IdleBehavior(AIBoard));
}

void BehaviorTree::AddToBehaviorTree(Sequence* seq)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(seq);
}

void BehaviorTree::AddTaskToBehaviorTree(Tasks* task)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(task);
}

void BehaviorTree::AddBehaviorToBehaviorTree(Behavior* behaviorSeq)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(behaviorSeq->behaviorSequence);
}



void BehaviorTree::StartBehavior()
{
	//this->sLoggerInstance->Log("STARTING BEHAVIOR");
	GetPlayer->DoAction(); //Run task to get the player
	if (!((ParentTaskController*)AISelector->GetControl())->Started())
	{
		ResetBehavior();
		((ParentTaskController*)AISelector->GetControl())->SafeStart();
	}

	Active = true;
}

void BehaviorTree::StopBehavior()
{
	((ParentTaskController*)AISelector->GetControl())->SafeEnd();
	((ParentTaskController*)AISelector->GetControl())->Reset();

	Active = false;

}

void BehaviorTree::ResetBehavior()
{
	((ParentTaskController*)AISelector->GetControl())->Reset();
	
	Active = false;
}

void BehaviorTree::DoBehavior()
{
	if (Active)
	{
		AISelector->DoAction();
	}

	if (AISelector->controller->currentTask == NULL)
	{
		ResetBehavior();
	}


}

void BehaviorTree::SetActive(bool activity)
{
	Active = activity;
}

bool BehaviorTree::GetActive()
{
	return Active;
}

bool BehaviorTree::CheckStarted()
{
	return ((ParentTaskController*)AISelector->GetControl())->Started();
}

bool BehaviorTree::CheckFinished()
{
	return ((ParentTaskController*)AISelector->GetControl())->Finished();
}

bool BehaviorTree::CheckFinishWithSuccess()
{
	return ((ParentTaskController*)AISelector->GetControl())->Succeeded();
}

bool BehaviorTree::CheckForFailure()
{
	return ((ParentTaskController*)AISelector->GetControl())->currentTask == nullptr;
}


