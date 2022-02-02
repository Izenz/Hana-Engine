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
	UpdateFPS();
	
}

void TimeManager::CapFps(unsigned fpsLimit) {
	// Limit fps to 'fpsLimit':
	if (fpsLimit != 0) {
		// Calculate how many ms we have to draw each frame
		float msForEachFrame = 1000.0f / float(fpsLimit);
		float waitingTime = (std::max)(0.0f, (msForEachFrame - real_delta_time));

		// If we have extra time, wait.
		//std::cout << "We waited for " << std::max(0.0f, (msForEachFrame - real_delta_time));
		rt_clock.Start();

		SDL_Delay(UINT32(waitingTime));
		rt_clock.AddWaitingTime(waitingTime);

		//std::cout << " and got back in " << rt_clock.Read() << std::endl;
	}
}

void TimeManager::DrawTimeWindow(bool* p_open) {
	// https://www.youtube.com/watch?v=lZuje-3iyVE
	// Scene Window: https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = 0;

	ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x * 0.4, ImGui::GetMainViewport()->Size.x * 0.2), ImGuiCond_FirstUseEver);
	ImGui::Begin("Time Management", p_open, window_flags);
	ImGui::End();
	
}

// Real-Time Clock

void TimeManager::StartRealClock() {
	rt_clock.Start();
}

float TimeManager::ReadRealClock() {
	return rt_clock.Read() * float(MSTOSEC);
}

void TimeManager::UpdateRealTimeClock() {
	rt_clock.Tick(REAL_TIME_SCALE);

	real_time_since_startup = float(rt_clock.GetTimeSinceStart()) * float(MSTOSEC);
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

void TimeManager::UpdateFPS()
{
	++frame_count;
	if (frames_clock.Read() >= 1000)
	{
		last_frame = frame_count;
		frame_count = 0;
		frames_clock.Start();
	}
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

float TimeManager::ReadGameClock() {
	return game_clock.Read() * float(MSTOSEC);
}

void TimeManager::StopGameClock() {
	game_clock.Stop();
}

float TimeManager::GetGameDeltaTime() const{
	return game_clock.GetDeltaTime();
}

float TimeManager::GetFPScount() const
{
	return last_frame;
}

void TimeManager::StartFramesClock()
{
	frames_clock.Start();
}

float TimeManager::ReadFramesClock()
{
	return frames_clock.Read() * float(MSTOSEC);
}

void TimeManager::StopFramesClock()
{
	frames_clock.Stop();
}
