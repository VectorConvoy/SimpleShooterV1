#pragma once
#include "timer.h"
#define _REGULATOR_H

class Regulator
{
public:

	Regulator();
	Regulator(float fps);
	~Regulator();

	bool isReady();


private:
	const static int MILLISECONDS_TO_SECONDS = 1000;
	const static int DEFAULT_FPS = 60;

	Timer* sTimer;
	
	float updateSpeed;
	float lastUpdateTime;

};