#pragma once

class Timer
{
public:
	Timer();
	float TotalTime()const; // in seconds
	float DeltaTime(); // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.
private:
	float _fDeltaTime;
	float _fTotalTime;
	float _fPrevTime;
	bool _bStop;
};

