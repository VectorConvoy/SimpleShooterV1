#pragma once
#define _PARENTTASKCONTROLLER_H

#include "TaskController.h"
#include "Tasks.h"
#include <vector>

class ParentTaskController : public TaskController
{

public:
	typedef TaskController super;
	std::vector<Tasks*> subtasks;
	Tasks* currentTask;


	ParentTaskController();
	ParentTaskController(Tasks* task);
	~ParentTaskController();

	void AddTask(Tasks* newTask);
	void Reset();

};