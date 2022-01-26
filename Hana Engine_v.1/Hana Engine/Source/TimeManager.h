#pragma once
#include "Globals.h"
#include "SDL.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include "imgui.h"

#define REAL_TIME_SCALE 1.0f

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
			current_tick = SDL_GetTicks();
			dt = float(current_tick - total_ticks) * time_scale;
			total_ticks = current_tick;
		}
	}
	float GetDeltaTime() const {
		return isPaused ? 0.0f : dt;
	}

	void Start() {
		isPaused = false;
		start_time = SDL_GetTicks();
	}

	UINT32 Read() {
		current_tick = isPaused ? current_tick : SDL_GetTicks();
		return current_tick - start_time;
	}

	void Stop() {
		isPaused = true;
		dt = 0.0f;
		total_ticks = current_tick;
	};

	UINT32 GetTimeSinceStart() const {
		return current_tick;
	}

	void AddWaitingTime(float waitingTime) {
		total_ticks += UINT32(waitingTime);
	}
};

/* Same as Timer but using more precise methods to get time in (µs) */
struct PerformanceTimer {
private:
	UINT64 total_ticks, current_tick, start_time;
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

	UINT64 Read() {
		return current_tick - start_time;
	}

	void Stop() {
		isPaused = true;
		dt = 0.0f;
		total_ticks = current_tick;
	}

	UINT64 GetTimeSinceStart() {
		return current_tick;
	}
};

class TimeManager {

public:

	/********** Functions **********/
	TimeManager();
	bool Init();
	void Update();

	void CapFps(unsigned fpsLimit);
	void DrawTimeWindow(bool* p_bool);

	// Real-time clock
	void StartRealClock();
	float ReadRealClock();

	float GetRealDeltaTime() const;
	float GetRealTimeSinceStart() const;

	// Game clock
	void StartGameClock();
	float ReadGameClock();
	void StopGameClock();

	void SetGameTimeScale(float new_ts);
	float GetGameDeltaTime() const;
	float GetFPScount() const;

	// Frames clock
	void StartFramesClock();
	float ReadFramesClock();
	void StopFramesClock();


private:

	/********** Functions **********/

	void UpdateRealTimeClock();
	void UpdateGameClock();
	void UpdateFPS();

	/********** Attributes **********/

	UINT32 total_ticks, current_tick;
	unsigned frame_count;			// app graphics frames since game start
	unsigned last_frame;

	// Real-time clock: Unstoppable clock that keeps the ms from application start
	Timer rt_clock;

	float real_time_since_startup;	// seconds since game start (Real Time Clock)
	float real_delta_time;			// last frame time expressed in seconds(Real Time Clock)

	// Game clock: : Is the speed at which our simulated world updates
	Timer game_clock;

	float time;						// second since game start (Game Clock)
	float time_scale = 1.0f;		// scale at which time is passing (Game Clock)

	Timer frames_clock; 
};

extern TimeManager* Time;
