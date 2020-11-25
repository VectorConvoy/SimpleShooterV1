#pragma once
#define _IDLEBEHAVIOR_H

#include "Behavior.h"

class IdleBehavior : public Behavior
{
public:

	typedef Behavior super;

	IdleBehavior();
	IdleBehavior(Blackboard* board);
	~IdleBehavior();

	void ConstructBehavior();

private:
	const std::string DEFAULT_NAME = "idle";

};