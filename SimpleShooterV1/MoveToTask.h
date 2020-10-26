#pragma once
#define _MOVETOTASK_H

#include "Node.h"


class MoveToTask : public Node
{
public:

	MoveToTask(Blackboard* board);
	~MoveToTask();
	
	bool CheckConditions();
	void Start();
	void End();
	void DoAction();


private:

};