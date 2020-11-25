/*
* A class based off the ParentTask class
* A component of the behavior tree
* 
* Similar to the sequence component but only executes
* a single task 
* 
* Mainly used to execute only a single task out of a group of them
* After the first task is executed, the others are ignored
*/
#pragma once
#define _SELECTOR_H

#include "ParentTask.h"

class Selector : public ParentTask
{
public:
	typedef ParentTask super;

	Selector();
	//Selector(Blackboard* board);
	Selector(Blackboard* board, std::string aName);
	~Selector();

	Tasks* ChooseNewTask();

	void ChildSucceeded();
	void ChildFailed();


};