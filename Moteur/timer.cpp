#include "timer.h"

Timer::Timer() {
    _fSecondsPerCount = 0.f;
    _fDeltaTime = -1.f;
}


float Timer::TotalTime() const
{
    return 0.0f;
}

float Timer::DeltaTime() const
{
    return _fDeltaTime;
}

void Timer::Reset()
{
}

void Timer::Start()
{
}

void Timer::Stop()
{
}

void Timer::Tick()
{
}
