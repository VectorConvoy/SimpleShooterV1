#pragma once
#define _CHASEDESTINATION_H

#include "Node.h"

class ChaseDestinationTask : public Node
{
public:
	typedef Node super;

	ChaseDestinationTask(Blackboard* board);
	ChaseDestinationTask(Blackboard* board, std::string aName);
	~ChaseDestinationTask();

	bool CheckConditions();
	void Start();
	void End();
	void DoAction();
};