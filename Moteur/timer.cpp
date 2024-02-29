#include "Incl.h"
#include "timer.h"


Timer::Timer() {
    _fSecondsPerCount = 0.f;
    _fDeltaTime = 0.f;
    
}


float Timer::TotalTime() const
{
    //si pause stocker le temps dans une autre variable
    //sinon incrémenter totaltime de deltatime
    
    DWORD  = timeGetTime();
    if (_bStop == false)
    {
        float GetTime = _fTotalTime;
    }
    else if (_bStop == true) {

    }
    return 0.0f;
}

float Timer::DeltaTime() const
{
    return _fDeltaTime;
}

void Timer::Reset()
{
    _fTotalTime = 0;
    
}

void Timer::Start()
{
    if (_bStop == false) {
        _bStop = true;
    }
}

void Timer::Stop()
{
    if (_bStop == false) {
        _bStop = true;
    }
}

void Timer::Tick()
{
}
