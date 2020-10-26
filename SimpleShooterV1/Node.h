#pragma once
#define _NODE_H

#include "Tasks.h"
#include "Blackboard.h"

class Node : public Tasks
{
public:
	typedef Tasks super;

	Node();
	Node(Blackboard* enemyBoard);
	~Node();

	void CreateController(); //Creates a task controller for this node

	//TaskController GetControl();
	TaskController* controller;

private:

protected:
	//TaskController controller;
};