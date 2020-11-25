/*
* A class that acts as a base for simple tasks
* 
* Main component for the behavior tree
*/
#include "Tasks.h"

Tasks::Tasks()
{
}

//Tasks::Tasks(Blackboard* enemyBoard)
//{
//	this->board = enemyBoard;
//}

Tasks::Tasks(Blackboard* enemyBoard, std::string aName)
{
	this->board = enemyBoard;
	this->name = aName;

	this->sLogger = Logger::Instance();
}

Tasks::~Tasks()
{
}

std::string Tasks::GetName()
{
	return name;
}

void Tasks::SetBoard(Blackboard* newBoard)
{
	board = newBoard;
}
