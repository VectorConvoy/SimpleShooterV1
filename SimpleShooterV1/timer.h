#pragma once

#ifndef _TIMER_H
#define _TIMER_H
#include <SDL.h>

//Singleton

class Timer
{
public:
	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void SetTimeScale(float time);
	float GetTimeScale();

	void Update();

private:

	Timer();
	~Timer();

	static Timer* singleInstance;
	
	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;
};

#endif // !_TIMER_H
