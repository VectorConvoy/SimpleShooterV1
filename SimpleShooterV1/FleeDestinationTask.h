#pragma once
#define _FLEEDESTINATION_H


#include "Node.h"



class FleeDestinationTask : public Node
{
public:
	typedef Node super;

	//FleeDestinationTask(Blackboard* board);
	FleeDestinationTask(Blackboard* board, std::string aName);
	~FleeDestinationTask();

	bool CheckConditions();
	void Start();
	void End();
	void DoAction();

};