#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) Output->Print(__FILE__, __LINE__, format, __VA_ARGS__);

//void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum class CAM_AXIS {
	X,
	Y,
	Z,
	X_NEGATIVE,
	Y_NEGATIVE,
	Z_NEGATIVE
};

// Configuration -----------
//#define SCREEN_WIDTH 640
//#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Hana Engine"
#define DEGTORAD 0.0174533