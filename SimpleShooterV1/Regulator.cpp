#include "Regulator.h"
#include "graphics.h"


Regulator::Regulator()
{
    sTimer = Timer::Instance();

    updateSpeed = (float)(MILLISECONDS_TO_SECONDS / DEFAULT_FPS);
    lastUpdateTime = sTimer->DeltaTime();

}

Regulator::Regulator(float fps)
{
    sTimer = Timer::Instance();

    updateSpeed = (float)(MILLISECONDS_TO_SECONDS / fps);
    lastUpdateTime = sTimer->DeltaTime();
}

Regulator::~Regulator()
{
    sTimer = nullptr;
}

bool Regulator::isReady()
{
    bool ready = false;

    if (sTimer->DeltaTime() - lastUpdateTime > updateSpeed)
    {
        lastUpdateTime = sTimer->DeltaTime();
        ready = true;
    }

    return ready;
}
