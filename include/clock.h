#pragma once

#include <chrono>

typedef std::chrono::steady_clock SteadyClock;
typedef std::chrono::time_point<SteadyClock> TimePoint;
typedef std::chrono::duration<float, std::milli> Milliseconds;

#define MS_PER_UPDATE 1000

class Clock
{
public:
	Clock();
	
	void start();
	void stop();
	float tick();
	
	bool is_ticking() const;
	float dt() const;
private:
	TimePoint _start;
	TimePoint _paused;
	float _dt;
	bool _ticking;
};
