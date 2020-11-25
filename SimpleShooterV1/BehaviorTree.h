/*
* Behavior Tree components and logic based on the following
* http://magicscrollsofcode.blogspot.com/2010/12/behavior-trees-by-example-ai-in-android.html
* 
* 
* Premise of the behavior tree is a tree of nodes
* The nodes contains a task that will be executed
* 
* The nodes are executed in order, left to right
* 
*/

#pragma once
#define _BEHAVIORTREE_H

#include "Blackboard.h"
#include "Selector.h"
#include "Sequence.h"
#include <pugixml.hpp>
#include "AIEngine.h"

class Enemy;
class Behavior;

class BehaviorTree
{
public:
	enum class BEHAVIOR_TYPES { flee = 0, chase, chase_shoot, sentry, sniper};
	BehaviorTree();
	BehaviorTree(Enemy* owner);
	~BehaviorTree();

	void SetBoardForBehaviors();
	
	void CreateBehaviorTree(BEHAVIOR_TYPES behavior = BEHAVIOR_TYPES::flee);
	void ConstructTree(std::string xmlFile);

	void LoadXML(std::string xmlFile);
	void ParseRoot(pugi::xml_node root);

	void ParseBehaviorXML(pugi::xml_node traitNode);
	void CreateDecorator(Behavior* behavior, pugi::xml_node conditionNode);

	void AddBehavior(std::string nameOfBehavior, int priority);

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

	AIEngine* sAIEngineInstance;

	bool Active;


	pugi::xml_document behaviorDoc;
};