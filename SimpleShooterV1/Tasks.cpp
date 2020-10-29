#include "Tasks.h"

Tasks::Tasks()
{
}

Tasks::Tasks(Blackboard* enemyBoard)
{
	this->board = enemyBoard;
}

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
