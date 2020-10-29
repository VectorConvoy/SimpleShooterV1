#pragma once
#define _TASKDECORATOR_H

#include "Tasks.h"

class TaskDecorator : public Tasks
{
public:
	typedef Tasks super;
	Tasks* task;

	TaskDecorator();
	TaskDecorator(Blackboard* board, Tasks* newTask);
	TaskDecorator(Blackboard* board, Tasks* newTask, std::string aName);
	~TaskDecorator();

	bool CheckConditions();

	void Start();
	void End();

	TaskController* GetControl();

private:
	void InitiateTask(Tasks* taskToInit);
};