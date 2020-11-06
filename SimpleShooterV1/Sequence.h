#pragma once
#define _SEQUENCE_H

#include "ParentTask.h"

class Sequence : public ParentTask
{
public:

	typedef ParentTask super;

	Sequence();
	//Sequence(Blackboard* enemyBoard);
	Sequence(Blackboard* enemyBoard, std::string aName);
	~Sequence();

	void ChildFailed();
	void ChildSucceeded();

private:

};