#pragma once
#define _MOVETOTASK_H

#include "Node.h"


class MoveToTask : public Node
{
public:
	typedef Node super;

	//MoveToTask(Blackboard* board);
	MoveToTask(Blackboard* board, std::string aName);

	~MoveToTask();
	
	bool CheckConditions();
	void Start();
	void End();
	void DoAction();


private:

};