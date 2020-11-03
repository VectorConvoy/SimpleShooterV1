#pragma once
#define _SEEKBEHAVIOR_H

#include "Behavior.h"
#include "CloseToPlayerDecorator.h"

class SeekBehavior : public Behavior
{
public:

	typedef Behavior super;

	CloseToPlayerDecorator* chaseSequence;

	SeekBehavior();
	SeekBehavior(Blackboard* board);
	~SeekBehavior();

	void SetSeekDist(float dist);
	float GetSeekDist();

private:
	const float SEEK_DISTANCE = 250.0f;

	float pursuitDist;
	

};