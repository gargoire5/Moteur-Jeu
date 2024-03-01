#include "Incl.h"
#include "timer.h"
using Microsoft::WRL::ComPtr;
using namespace std;
using namespace DirectX;

Timer::Timer() {
    _fDeltaTime = 0.f;
    _fTotalTime = 0.f;
    DWORD  CurrTime = timeGetTime();
    _fPrevTime = CurrTime;
    _bStop = true;
}


float Timer::TotalTime() const
{
    //si pause stocker le temps dans une autre variable
    //sinon incrémenter totaltime de deltatime
    return _fTotalTime;
}

float Timer::DeltaTime() const
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

void Timer::Tick(HWND hWnd)
{


    if (_bStop == false) {
        DWORD  CurrTime = timeGetTime();
        _fDeltaTime = (CurrTime - _fPrevTime)/1000;

        _fPrevTime = CurrTime;
        _fTotalTime += _fDeltaTime;
    }

    wstring deltatime = to_wstring(_fDeltaTime);
    wstring totaltime = to_wstring(_fTotalTime);

    wstring windowText = L" hello" + deltatime + L"+" + totaltime;

    SetWindowText(hWnd, windowText.c_str());
    
}
