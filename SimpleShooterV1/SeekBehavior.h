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
	SeekBehavior(Blackboard* board, float seekDist);
	SeekBehavior(Blackboard* board, float seekDist, TaskDecorator customDeco);
	~SeekBehavior();

	void SetSeekDist(float dist);
	float GetSeekDist();

private:
	const float SEEK_DISTANCE = 100; //Distance of how close the AI should be before it stops chasing or how far away the AI should be beforr it starts chasing

	float pursuitDist;
	

};