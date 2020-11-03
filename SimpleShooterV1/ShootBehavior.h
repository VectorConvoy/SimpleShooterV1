#pragma once
#define _SHOOTBEHAVIOR_H

#include "Behavior.h"
#include "CloseToPlayerDecorator.h"

class ShootBehavior : public Behavior
{
public:
	typedef Behavior super;

	CloseToPlayerDecorator* chaseSequence;

	ShootBehavior();
	ShootBehavior(Blackboard* board);
	~ShootBehavior();

	void SetMinimumShootDist(float dist);
	float GetMinimumShootDist();

private:
	float minimumDistance;
	
};