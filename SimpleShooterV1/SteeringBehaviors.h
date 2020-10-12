#pragma once
#include "MathHelper.h"
#define _STEERINGBEHAVIORS_H

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();

	Vector2 Seek(Vector2 entityPos, Vector2 targetPos);
	Vector2 Flee(Vector2 entityPos, Vector2 targetPos, float panicDistance = 100);
private:
};