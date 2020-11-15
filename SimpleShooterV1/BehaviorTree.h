/*
* Behavior Tree components and logic based on the following
* http://magicscrollsofcode.blogspot.com/2010/12/behavior-trees-by-example-ai-in-android.html
*/

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
	enum class BEHAVIOR_TYPES { flee = 0, chase, chase_shoot, sentry, sniper};
	BehaviorTree();
	BehaviorTree(Enemy* owner);
	~BehaviorTree();

	void CreateBehaviorTree(BEHAVIOR_TYPES behavior = BEHAVIOR_TYPES::flee);

	void AddToBehaviorTree(Sequence* seq);
	void AddTaskToBehaviorTree(Tasks* task);
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