#pragma once
#define _TASKCONTROLLER_H

#include <string>
#include "Logger.h"

class Tasks;

class TaskController
{
public:
	TaskController();
	TaskController(Tasks* task);
	TaskController(Tasks* task, std::string aName);
	~TaskController();

	void SetTask(Tasks* newTask);
	Logger* GetLogger();

	void SafeStart(); //Start the controlled task 
	void SafeEnd(); //End the controlled task

	bool Succeeded();
	bool Failed();
	bool Started();
	bool Finished();
	
	void FinishWithSuccess();
	void FinishWithFailure();

	void Reset();

private:
	bool done; //Indicates whether or not a task is complete
	bool success; //Indicates whether or not the task succeeded
	bool started; //Indicates whether or not a task has started

	Tasks* task; //The task this controller is controlling
	Logger* sLoggerInstance;

	void Initialize(); //Initialize boolean variables



protected:
	std::string name;

};