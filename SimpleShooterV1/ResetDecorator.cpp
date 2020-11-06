#include "ResetDecorator.h"

ResetDecorator::ResetDecorator()
{
}

ResetDecorator::ResetDecorator(Blackboard* bboard, Tasks* newTask, std::string aName) : super(bboard, newTask, aName)
{


}

ResetDecorator::~ResetDecorator()
{
}

void ResetDecorator::DoAction()
{
	task->DoAction();

	if (task->GetControl()->Finished())
	{
		task->GetControl()->Reset();
	}
}
