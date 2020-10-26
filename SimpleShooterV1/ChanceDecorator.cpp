#include "ChanceDecorator.h"

ChanceDecorator::ChanceDecorator()
{
}

ChanceDecorator::ChanceDecorator(Blackboard* board, Tasks* task, int chance)
{
	super(board, task);
	Initialize(chance);
}

ChanceDecorator::~ChanceDecorator()
{
}

void ChanceDecorator::DoAction()
{
	task->DoAction();
}

bool ChanceDecorator::CheckConditions()
{
	randomValue = rand() % CHANCE_RANGE;

	return (task->CheckConditions() && randomValue <= chanceValue);
}

void ChanceDecorator::Initialize(int chance)
{
	srand((unsigned) time(0));

	if (chance > 100 || chance < 0)
	{
		//Chance value outside the range

		chance = DEFAULT_CHANCE; //Set the value to 50;
	}

	chanceValue = chance;
	
}
