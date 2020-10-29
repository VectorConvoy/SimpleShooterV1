#include "BehaviorTree.h"
#include "FleeBehavior.h"
#include "GetPlayerTask.h"
#include <algorithm>

BehaviorTree::BehaviorTree()
{
	AIBoard = new Blackboard();
	AISelector = new Selector(AIBoard);
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

void BehaviorTree::CreateBehaviorTree(std::string behaviorType)
{

	std::transform(behaviorType.begin(), behaviorType.end(), behaviorType.begin(), [](unsigned char c) {return std::tolower(c); });

	

	if (behaviorType == "flee")
	{
		this->sLoggerInstance->Log("ADDING FLEE BEHAVIOR");
		AddBehaviorToBehaviorTree(new FleeBehavior(AIBoard));

	}



}

void BehaviorTree::AddToBehaviorTree(Sequence* seq)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(seq);
}

void BehaviorTree::AddBehaviorToBehaviorTree(Behavior* behaviorSeq)
{
	
	((ParentTaskController*)AISelector->GetControl())->AddTask(behaviorSeq->behaviorSequence);
}

void BehaviorTree::StartBehavior()
{
	this->sLoggerInstance->Log("STARTING BEHAVIOR");
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


