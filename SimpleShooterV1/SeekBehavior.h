#pragma once
#define _SEEKBEHAVIOR_H

#include "Behavior.h"

class SeekBehavior : public Behavior
{
public:

	void SetPursuitDist(float dist);
	float GetPursuitDist();

	Vector2 Seek();

private:

	float pursuitDist;

};