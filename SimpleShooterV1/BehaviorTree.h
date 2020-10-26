#pragma once
#define _BEHAVIORTREE_H

#include "Blackboard.h"
#include "Selector.h"
#include "Sequence.h"
class BehaviorTree
{
public:
	BehaviorTree();
	BehaviorTree(Enemy* owner);
	~BehaviorTree();

	void CreateBehaviorTree();

	void AddToBehaviorTree(Sequence* seq);

	void StartBehavior();

	bool CheckFinished();

	


private:
	Blackboard* AIBoard;
	Selector* AISelector;

};