// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	running = true;
	paused = false;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}

void Timer::Pause()
{
	if (paused == false) {
		paused = true;
		paused_at = SDL_GetTicks();
	}
}

void Timer::UnPause()
{
	if (paused == true) {
		paused = false;
		unpaused_at = SDL_GetTicks();
		pausetime += (unpaused_at - paused_at);
	}
}

// ---------------------------------------------
Uint32 Timer::Read()
{
	if (running == true)
	{
		if (paused == true)
			return (paused_at * multiplier - started_at);
		else
			return (SDL_GetTicks() * multiplier - started_at) - pausetime;
	}
	else
	{
		return stopped_at * multiplier - started_at;
	}
}

Uint32 Timer::ReadSc()
{
	if (running == true)
	{
		if (paused == true)
			return ((paused_at * multiplier - started_at) / 1000);
		else
			return (((SDL_GetTicks() * multiplier - started_at) - pausetime) / 1000);
	}
	else
	{
		return ((stopped_at * multiplier - started_at) / 1000);
	}
}

void Timer::SetMultiplier(float t)
{
	if (t < 1)
		t = 1;
	multiplier = t;
}


