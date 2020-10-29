#pragma once
#define _PATROLBEHAVIOR_H


#include "Behavior.h"
#include "MathHelper.h"

class PatrolBehavior : public Behavior
{
public:
	
	Vector2 Wander(Vector2 entityPos, Vector2 targetPos);

private:
	double patrolRadius;
	double patrolDistance;
	double patrolJitter;

	Vector2 target;


};