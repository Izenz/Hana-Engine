#include "TimeManager.h"

TimeManager::TimeManager()
{
	total_ticks = 0;
	current_tick = 0;
	frame_count = 0;

	real_time_since_startup = 0.0f;
	real_delta_time = 0.0f;

	time = 0.0f;
	time_scale = 1.0f;
}

bool TimeManager::Init() {
	return true;
}

void TimeManager::Update() {
	UpdateGameClock();
	UpdateRealTimeClock();

	++frame_count;
}

void TimeManager::StartTimer() {
	// Save time on start_time;
}

float TimeManager::EndTimer() {
	// Return current time - start_time
	return real_delta_time;
}

void TimeManager::UpdateGameClock() {
	game_clock.Tick(time_scale);

	time = game_clock.GetDeltaTime();
}

void TimeManager::UpdateRealTimeClock() {
	rt_clock.Tick();

	real_time_since_startup = rt_clock.GetTimeSinceStart();
	real_delta_time = rt_clock.GetDeltaTime();
}

void TimeManager::SetGameTimeScale(float new_ts) {
	time_scale = new_ts;
}
