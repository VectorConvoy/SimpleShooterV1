#pragma once
#define _FLEEBEHAVIOR_H

#include "Behavior.h"

class FleeBehavior : public Behavior
{
public:

	typedef Behavior super;

	FleeBehavior();
	FleeBehavior(Blackboard* board);
	FleeBehavior(Blackboard* board, float fleeDist);
	~FleeBehavior();

	void SetPanicDist(float dist);
	float GetPanicDist();

	void ConstructBehavior();
	

private:
	const std::string DEFAULT_NAME = "flee";

	const float PANIC_DISTANCE = 250.0f;
	float panicDistance; //Determines how close the player needs to get before reaction

};