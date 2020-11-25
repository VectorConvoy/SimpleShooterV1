#pragma once
#define _PARENTTASK_H

#include "Tasks.h"
#include "ParentTaskController.h"
#include <sstream>

class ParentTask : public Tasks
{
public:
	typedef Tasks super;
	ParentTaskController* controller;

	ParentTask();
	//ParentTask(Blackboard* enemyBoard);
	ParentTask(Blackboard* enemyBoard, std::string aName);
	~ParentTask();

	void CreateController();
	TaskController* GetControl();

	bool CheckConditions();

	virtual void ChildSucceeded() {};
	virtual void ChildFailed() {};

	void DoAction();

	void Start();
	void End();

	void SetBoardForAllSubtasks(Blackboard* newBoard);



private:
	//ParentTaskController* controller;
};