#pragma once
#include "imgui.h"

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
	ImVector<int> line_offset;
};

extern Console* Logger;