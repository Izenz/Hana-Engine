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
	UP,
	DOWN,
	REPEAT,
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

	inline KEY_STATE GetKeyState(unsigned keyCode) const { return keyboard_state[keyCode]; };
	inline const float2& GetMousePos() const { return mouse_pos; };
	inline const float2& GetMouseMotion() const { return mouse_pos_delta; };
	inline const float2& GetWheelMotion() const { return mouse_wheel_delta; };

	bool isMouseButtonPressed(unsigned buttonCode) const;
	bool isKeyPressed(unsigned keyCode) const;

private:
	const Uint8 *keyboard = NULL;
	KEY_STATE* keyboard_state;

	KEY_STATE mouse_state[NUM_MOUSE_BUTTONS];
	float2 mouse_pos = float2::zero;
	float2 mouse_pos_delta = float2::zero;
	float2 mouse_wheel_delta = float2::zero;

	float2 window_size = float2(1920, 1080);
};