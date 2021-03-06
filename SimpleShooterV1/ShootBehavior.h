#pragma once
#define _SHOOTBEHAVIOR_H

#include "Behavior.h"
#include "ChanceDecorator.h"

class ShootBehavior : public Behavior
{
public:
	typedef Behavior super;

	ChanceDecorator* shootSequence;

	ShootBehavior();
	ShootBehavior(Blackboard* board);
	ShootBehavior(Blackboard* board, int chance);
	~ShootBehavior();

	void SetShootChance(int chance);
	int GetShootChance();

	void ConstructBehavior();

private:
	const std::string DEFAULT_NAME = "shoot";

	int shootChance;
	
};