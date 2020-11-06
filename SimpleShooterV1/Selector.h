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