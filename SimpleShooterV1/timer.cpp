#include "timer.h"

Timer* Timer::singleInstance = NULL;

Timer* Timer::Instance()
{
    if (singleInstance == NULL)
    {
        singleInstance = new Timer();
    }

    return singleInstance;
}

void Timer::Release()
{
    delete singleInstance;
    singleInstance = NULL;
}

void Timer::Reset()
{
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
    return mDeltaTime;
}

void Timer::SetTimeScale(float time)
{
    mTimeScale = time;
}

float Timer::GetTimeScale()
{
    return mTimeScale;
}

void Timer::Update()
{
    mElapsedTicks = SDL_GetTicks() - mStartTicks;
    mDeltaTime = mElapsedTicks * 0.001f; //Ticks are in milliseconds so we need to convert to seconds
}

Timer::Timer()
{
    Reset();
    mTimeScale = 1.0;

}

Timer::~Timer()
{
}
