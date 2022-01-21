#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) Output->Print(__FILE__, __LINE__, format, __VA_ARGS__);

//void log(const char file[], int line, const char* format, ...);

enum class update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR,
};

enum class CAM_AXIS {
	X,
	Y,
	Z,
	X_NEGATIVE,
	Y_NEGATIVE,
	Z_NEGATIVE
};

enum class WINDOW_TYPES {
	GAME_VIEW = 0,
	HIERARCHY,
	INSPECTOR,
	RESOURCES,
	EXPLORER,
	CONSOLE,
	ENGINE_INFO,
	TIME_CONTROL,
	IMGUI_DEMO,
	MAX,
};

// Configuration -----------
//#define SCREEN_WIDTH 640
//#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Hana Engine"
#define DEGTORAD 0.0174533
#define MSTOSEC 0.001
#define INIT_SCREEN_WIDTH 800
#define INIT_SCREEN_HEIGHT 600