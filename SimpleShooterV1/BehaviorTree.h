#pragma once
#define _BEHAVIORTREE_H

#include "Blackboard.h"
#include "Selector.h"
#include "Sequence.h"

class Enemy;
class Behavior;

class BehaviorTree
{
public:
	BehaviorTree();
	BehaviorTree(Enemy* owner);
	~BehaviorTree();

	void CreateBehaviorTree(std::string behaviorType = "flee");

	void AddToBehaviorTree(Sequence* seq);
	void AddBehaviorToBehaviorTree(Behavior* behaviorSeq);
	void StartBehavior();
	void StopBehavior();
	void ResetBehavior();
	void DoBehavior();

	void SetActive(bool activity);
	bool GetActive();


	bool CheckStarted();
	bool CheckFinished();
	bool CheckFinishWithSuccess();
	bool CheckForFailure();
	


private:
	Blackboard* AIBoard;
	Tasks* GetPlayer;
	Selector* AISelector;
	Sequence* AISequence;
	Logger* sLoggerInstance;

	bool Active;

};