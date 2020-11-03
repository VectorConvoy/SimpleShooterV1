#include "RegulatorDecorator.h"

RegulatorDecorator::RegulatorDecorator()
{
}

RegulatorDecorator::RegulatorDecorator(Blackboard* board, Tasks* task, float UpdateTime) : super(board, task)
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
	logText = ("STARTING REGULATOR FOR TASK %s", task->GetName());
	this->sLogger->Log(logText);
	
	task->Start();
	regulator = new Regulator(1.0f / updateTime);
}

void RegulatorDecorator::End()
{
	logText = ("ENDING REGULATOR FOR TASK %s", task->GetName());
	this->sLogger->Log(logText);
}
