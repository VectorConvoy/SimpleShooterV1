/*
* A decorator class to wrap a task class
* This adds a condition that is determined
* by RNG
*/
#include "ChanceDecorator.h"
#include <cstdlib>

ChanceDecorator::ChanceDecorator()
{
}

//ChanceDecorator::ChanceDecorator(Blackboard* board, Tasks* task, int chance): super(board, task)
//{
//	Initialize(chance);
//}

ChanceDecorator::ChanceDecorator(Blackboard* board, Tasks* task, std::string aName, int chance) : super(board, task, aName)
{
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
	std::string rng = (task->CheckConditions() && randomValue <= chanceValue ? "RNG CHECK PASSED" : "RNG CHECK FAILED");
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
