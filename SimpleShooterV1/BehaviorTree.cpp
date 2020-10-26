#include "BehaviorTree.h"

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
	AISelector = new Selector(AIBoard);

}

BehaviorTree::~BehaviorTree()
{
	delete AIBoard;
	AIBoard = nullptr;

	delete AISelector;
	AISelector = nullptr;
}

void BehaviorTree::CreateBehaviorTree()
{
	//AISelector = new Selector(AIBoard);
}

void BehaviorTree::AddToBehaviorTree(Sequence* seq)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(seq);
}

void BehaviorTree::StartBehavior()
{
	if (!((ParentTaskController*)AISelector->GetControl())->Started())
	{
		((ParentTaskController*)AISelector->GetControl())->Reset();
		((ParentTaskController*)AISelector->GetControl())->SafeStart();

	}
}

bool BehaviorTree::CheckFinished()
{
	return ((ParentTaskController*)AISelector->GetControl())->Finished();
}
