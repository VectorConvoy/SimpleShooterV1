#include "ResetDecorator.h"

ResetDecorator::ResetDecorator()
{
}

ResetDecorator::ResetDecorator(Blackboard* bboard, Tasks* newTask)
{
	super(bboard, newTask);

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