#include "../include/clock.h"

Clock::Clock()
	: _start(), _dt(), _ticking()
{
}

void Clock::start()
{
	if(!_ticking)
	{
		_ticking = true;
	}
}

void Clock::stop()
{
	if(_ticking)
	{
		_ticking = false;
	}
}

float Clock::tick()
{
	if(_ticking)
	{
		TimePoint t = SteadyClock::now();
		_dt = std::chrono::duration_cast<Milliseconds>(t - _start).count() / MS_PER_UPDATE;
		_start = t;
		return _dt;
	}
	return 0.0f;
}

bool Clock::is_ticking() const
{
	return _ticking;
}

float Clock::dt() const
{
	return _dt;
}
