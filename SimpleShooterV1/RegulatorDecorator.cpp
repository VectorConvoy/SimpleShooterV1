/*
* A decorator class that wraps around a task
* 
* Adds a condition that triggers the task
* at specific intervals
* 
* So far not in use as of 11/17/20
*/
#include "RegulatorDecorator.h"

RegulatorDecorator::RegulatorDecorator()
{
}

RegulatorDecorator::RegulatorDecorator(Blackboard* board, Tasks* task, std::string aName, float UpdateTime) : super(board, task, aName)
{
	updateTime = UpdateTime;
}

RegulatorDecorator::~RegulatorDecorator()
{
	delete regulator;
	regulator = nullptr;
}

void RegulatorDecorator::DoAction()
{
	if (regulator->isReady())
	{
		task->DoAction();
	}
}

void RegulatorDecorator::Start()
{
	std::ostringstream oss;
	oss << "STARTING REGULATOR FOR TASK " << task->GetName();
	this->sLogger->Log(oss.str());
	
	task->Start();
	regulator = new Regulator(1.0f / updateTime);
}

void RegulatorDecorator::End()
{
	std::ostringstream oss;
	oss << "ENDING REGULATOR FOR TASK " << task->GetName();
	this->sLogger->Log(oss.str());
}
