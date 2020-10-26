#pragma once
#define _TASKS_H

#include "Blackboard.h"
#include "TaskController.h"
class Tasks
{
public:
	Tasks();
	Tasks(Blackboard* enemyBoard);
	~Tasks();

	virtual bool CheckConditions() { return false; };
	virtual void Start() {};
	virtual void End() {};
	virtual void DoAction() {};

	virtual TaskController* GetControl() { return nullptr; };

protected:
	Blackboard* board;

private:

};