#pragma once
#include "Tasks.h"
#define _BEHAVIOR_H



class Behavior
{
	bool operator <(const Behavior* behave) const
	{
		return (priorityValue < behave->priorityValue);
	}

public:

	Tasks* behaviorSequence;


	Behavior();
	~Behavior();

	void SetPriorityID(int priority);
	int GetPriorityID();

	void SetName(std::string name);
	std::string GetName();

	void SetBoard(Blackboard* newBoard);
	Blackboard* GetBoard();

	void SetValue(float newValue);
	float GetValue();

	void SetConditionType(std::string condType);
	std::string GetConditionType();

	void AddAdditionalSequence(Tasks* newTask);

	virtual void ConstructBehavior() {};


private:

	int priorityValue;  //The lower the number, the higher the priortiy

	std::string behaviorName;
	std::string conditionType;

	Blackboard* board;

	float value; //Represents a value
};


