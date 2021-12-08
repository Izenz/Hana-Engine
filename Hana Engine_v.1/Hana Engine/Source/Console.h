#pragma once
#include "imgui.h"
#include <stdio.h>
#include <Windows.h>

class Console {

public:
	Console();
	~Console();

	void ClearLog();
	void Print(const char file[], int line, const char* format, ...) IM_FMTARGS(2);
	void DrawConsole(bool* p_open);
private:
	bool autoscroll = true;
	ImGuiTextBuffer buffer;
	ImGuiTextFilter filter;
	ImVector<int> lineOffsets;
};

extern Console* Output;