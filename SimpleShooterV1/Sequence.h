/*
* Based of the ParentTask class and contains several tasks
* These tasks will be executed in order, left to right
* 
* A component for the behavior tree to allow a number of tasks
* to be executed
*/
#pragma once
#define _SEQUENCE_H

#include "ParentTask.h"

class Sequence : public ParentTask
{
public:

	typedef ParentTask super;

	Sequence();
	//Sequence(Blackboard* enemyBoard);
	Sequence(Blackboard* enemyBoard, std::string aName);
	~Sequence();

	void ChildFailed();
	void ChildSucceeded();

private:

};