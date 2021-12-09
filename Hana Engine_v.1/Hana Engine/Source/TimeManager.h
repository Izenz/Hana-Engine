#pragma once
#include "Globals.h";
#include "SDL.h"

/* Simple Timer struct to handle measurements in (ms) */
struct Timer {
private:
	UINT32 total_ticks, current_tick, start_time;
	float dt;
	bool isPaused;
public:
	Timer() {
		total_ticks = 0;
		current_tick = 0;
		start_time = 0;

		dt = 0.0f;

		isPaused = false;
	}
	void Tick(float time_scale) {
		if (!isPaused) {
			current_tick = SDL_GetTicks() * time_scale;
			dt = current_tick - total_ticks;
			total_ticks = current_tick;
		}
	}
	float GetDeltaTime() {
		return isPaused ? 0.0f : dt;
	}

	void Start() {
		isPaused = false;
		start_time = current_tick;
	}

	float Read() {
		return current_tick - start_time;
	}

	void Stop() {
		isPaused = true;
		dt = 0.0f;
		total_ticks = current_tick;
	};

	float GetTimeSinceStart() {
		return current_tick;
	}
};

/* Same as Timer but using more precise methods to get time in (µs) */
struct PerformanceTimer {
private:
	UINT32 total_ticks, current_tick, start_time;
	float dt;
	bool isPaused;
public:
	PerformanceTimer() {
		total_ticks = 0;
		current_tick = 0;
		start_time = 0;

		dt = 0.0f;

		isPaused = false;
	}
	void Tick() {
		if (!isPaused) {
			total_ticks = current_tick;
			current_tick = SDL_GetPerformanceCounter();
			dt = (float)((current_tick - total_ticks) * 1000 / (float)SDL_GetPerformanceFrequency());
		}
	}

	float GetDeltaTime() {
		return isPaused ? 0.0f : dt;
	}

	void Start() {
		isPaused = false;
		start_time = current_tick;
	}

	float Read() {
		return current_tick - start_time;
	}

	void Stop() {
		isPaused = true;
		dt = 0.0f;
		total_ticks = current_tick;
	}

	float GetTimeSinceStart() {
		return current_tick;
	}
};

class TimeManager {

public:

	/********** Functions **********/
	TimeManager();
	bool Init();
	void Update();

	void StartTimer();
	float EndTimer();

	void SetGameTimeScale(float new_ts);

	float GetRealDeltaTime();

private:

	/********** Functions **********/

	void UpdateRealTimeClock();
	void UpdateGameClock();
	
	/********** Attributes **********/

	UINT32 total_ticks, current_tick;
	unsigned frame_count;			// app graphics frames since game start

	// Real-time clock: Unstoppable clock that keeps the ms from application start
	PerformanceTimer rt_clock;

	float real_time_since_startup;	// seconds since game start (Real Time Clock)
	float real_delta_time;			// last frame time expressed in seconds(Real Time Clock)

	// Game clock: : Is the speed at which our simulated world updates
	Timer game_clock;

	float time;						// second since game start (Game Clock)
	float time_scale = 1.0f;		// scale at which time is passing (Game Clock)
};
