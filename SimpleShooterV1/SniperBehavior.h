#pragma once
#define _SNIPERBEHAVIOR_H

#include "Behavior.h"

class SniperBehavior : public Behavior
{
public:
	typedef Behavior super;

	SniperBehavior();
	SniperBehavior(Blackboard* board);
	~SniperBehavior();

	void SetFleeDist(float dist);
	float GetFleeDist();

	void SetChaseDist(float dist);
	float GetChaseDist();

private:
	const float DEFAULT_FLEE_DIST = 250.0f; //Flee until the distance between the player is this value
	const float DEFAULT_CHASE_DIST = 50.0f; //If the player is within this distance, chase the player instead
	
	
	float fleeDistance; //Determines how close the player needs to get before reaction
	float chaseDistance;
};