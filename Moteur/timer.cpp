#include "Incl.h"
#include "timer.h"
#include "Engine.h"

using namespace std;
using namespace DirectX;

Timer::Timer() {
    _fDeltaTime = 0.f;
    _fTotalTime = 0.f;
    _fPrevTime = 0.f;
    _bStop = true;
}


float Timer::TotalTime() const
{
    //si pause stocker le temps dans une autre variable
    //sinon incr�menter totaltime de deltatime
    return _fTotalTime;
}

float Timer::DeltaTime()
{
    return _fDeltaTime;
}

void Timer::Reset()
{
    _fTotalTime = 0;
    _fDeltaTime = 0;
    _fPrevTime = 0;
}

void Timer::Start()
{
        _bStop = false;
}

void Timer::Stop()
{
        _bStop = true;
}

void Timer::Tick()
{
    if (_bStop == false) {
        float CurrTime = timeGetTime();
        if (_fPrevTime != 0) {
            if (!Engine::Instance()->_bPaused)
            {
                if (Engine::Instance()->_bSlowMotion == true)
                {
                    _fDeltaTime = ((CurrTime - _fPrevTime) / 1000) / 2.5;
                }
                else
                {
                    _fDeltaTime = (CurrTime - _fPrevTime) / 1000;
                }
            }
            else
            {
                _fDeltaTime = 0;
            }
        }
        _fPrevTime = CurrTime;
        _fTotalTime += _fDeltaTime;
    }
}
