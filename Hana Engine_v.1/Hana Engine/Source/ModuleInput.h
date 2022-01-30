#pragma once

#include "Globals.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "SDL/include/SDL.h"

#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleScene.h"
#include "ModuleEditorCamera.h"
#include "ModuleRender.h"

typedef unsigned __int8 Uint8;
constexpr size_t NUM_MAX_KEYS = 300;
constexpr size_t NUM_MOUSE_BUTTONS = 5;

enum class KEY_STATE {
	IDLE = 0,
	DOWN,
	REPEAT,
	UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	//void HandleMouseButtonClick(SDL_MouseButtonEvent& mouseEvent);
	//void HandleMouseButtonRelease(SDL_MouseButtonEvent& mouseEvent);
	void GetMouseMotion(int& x, int& y);

private:
	const Uint8 *keyboard = NULL;
	KEY_STATE* keyboard_state;

	KEY_STATE mouse_state[NUM_MOUSE_BUTTONS];
	float2 mouse_pos = float2::zero;
	float2 mouse_pos_delta = float2::zero;
	float2 mouse_wheel_delta = float2::zero;

	float2 window_size = float2(1920, 1080);
};