#pragma once
#define _GETPLAYERTASK_H

#include "Node.h"
#include "Blackboard.h"
#include "ScreenManager.h"

class GetPlayerTask : public Node
{
public:
	typedef Node super;

	GetPlayerTask();
	//GetPlayerTask(Blackboard* blackboard);
	GetPlayerTask(Blackboard* blackboard, std::string aName);
	~GetPlayerTask();

	bool CheckConditions();
	
	void DoAction();

	void Start();
	void End();
private:


protected:
};