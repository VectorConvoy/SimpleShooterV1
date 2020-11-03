#pragma once
#define _IDLETASK_H

#include "Node.h"

class IdleTask : public Node
{
public:

	typedef Node super;

	IdleTask();
	IdleTask(Blackboard* blackboard);
	IdleTask(Blackboard* blackboard, std::string aName);
	~IdleTask();

	bool CheckConditions();

	void DoAction();

	void Start();
	void End();
};