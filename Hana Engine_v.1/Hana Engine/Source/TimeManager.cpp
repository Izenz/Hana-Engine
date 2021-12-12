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

void TimeManager::CapFps(unsigned fpsLimit) const {
	// Limit fps to 'fpsLimit':
	// Calculate how many ms we have to draw each frame
	// If we have extra time, wait.
}

// Real-Time Clock

void TimeManager::StartRealClock() {
	rt_clock.Start();
}

float TimeManager::ReadRealClock() const {
	return rt_clock.Read() * MSTOSEC;
}

void TimeManager::UpdateRealTimeClock() {
	rt_clock.Tick(REAL_TIME_SCALE);

	real_time_since_startup = rt_clock.GetTimeSinceStart();
	real_delta_time = rt_clock.GetDeltaTime();
}

float TimeManager::GetRealDeltaTime() const {
	return real_delta_time;
}

// Game Clock

void TimeManager::UpdateGameClock() {
	game_clock.Tick(time_scale);

	time = game_clock.GetDeltaTime();
}

float TimeManager::GetRealTimeSinceStart() const {
	return real_time_since_startup;
}

void TimeManager::SetGameTimeScale(float new_ts) {
	time_scale = new_ts;
}

void TimeManager::StartGameClock() {
	game_clock.Start();
}

float TimeManager::ReadGameClock() const {
	return game_clock.Read() * MSTOSEC;
}

void TimeManager::StopGameClock() {
	game_clock.Stop();
}

float TimeManager::GetGameDeltaTime() const{
	return game_clock.GetDeltaTime();
}