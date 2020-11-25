#pragma once
#define _TASKS_H

#include "Logger.h"
#include "TaskController.h"
#include <sstream>

class Blackboard;

class Tasks
{
public:
	Logger* sLogger;

	Tasks();
	//Tasks(Blackboard* enemyBoard);
	Tasks(Blackboard* enemyBoard, std::string aName);
	~Tasks();

	std::string GetName();
	void SetBoard(Blackboard* newBoard);

	virtual bool CheckConditions() { return false; };
	virtual void Start() {};
	virtual void End() {};
	virtual void DoAction() {};

	virtual TaskController* GetControl() { return nullptr; };

protected:
	Blackboard* board;
	std::string name;
private:

};