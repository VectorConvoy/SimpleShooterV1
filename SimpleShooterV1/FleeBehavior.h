#pragma once
#define _FLEEBEHAVIOR_H

#include "Behavior.h"
#include "PanicDecorator.h"

class FleeBehavior : public Behavior
{
public:

	typedef Behavior super;

	PanicDecorator* fleeSequence;

	FleeBehavior();
	FleeBehavior(Blackboard* board);
	~FleeBehavior();

	void SetPanicDist(float dist);
	float GetPanicDist();



private:
	const float PANIC_DISTANCE = 250.0f;
	float panicDistance; //Determines how close the player needs to get before reaction

};