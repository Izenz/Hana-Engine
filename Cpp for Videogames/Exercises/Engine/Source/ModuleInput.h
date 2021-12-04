#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void HandleMouseButtonClick(SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonRelease(SDL_MouseButtonEvent& mouseEvent);

private:
	const Uint8 *keyboard = NULL;
	float2 mouse_pos_dif = float2::zero, mouse_wheel_dif = float2::zero;
};