#pragma once
#define _FLEEBEHAVIOR_H

#include "Behavior.h"

class FleeBehavior : public Behavior
{
public:

	void SetPanicDist(float dist);
	float GetPanicDist();


	Vector2 Flee();

private:
	float panicDistance; //Determines how close the player needs to get before reaction

};