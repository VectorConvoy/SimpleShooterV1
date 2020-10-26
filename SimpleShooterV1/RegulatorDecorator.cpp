#include "RegulatorDecorator.h"

RegulatorDecorator::RegulatorDecorator()
{
}

RegulatorDecorator::RegulatorDecorator(Blackboard* board, Tasks* task, float UpdateTime)
{
	super(board, task);
	updateTime = UpdateTime;
}

RegulatorDecorator::~RegulatorDecorator()
{
}

void RegulatorDecorator::DoAction()
{
	
}

void RegulatorDecorator::Start()
{
}

void RegulatorDecorator::End()
{
}
