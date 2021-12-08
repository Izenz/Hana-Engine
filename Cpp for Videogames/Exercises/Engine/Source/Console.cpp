#include "Console.h"
#include <stdio.h>
#include <Windows.h>

Console::Console() 
{
}

Console::~Console()
{
}

void Console::Print(const char file[], int line, const char* format, ...) IM_FMTARGS(2){
	const static int max_log_size = 4096;

	static char tmp_string[max_log_size];
	tmp_string[0] = '\n';
	static char tmp_string2[max_log_size];

	int old_size = buffer.size();

	va_list args;
	va_start(args, format);
	vsprintf_s(&tmp_string[1], max_log_size - 1, format, args);
	va_end(args);

	buffer.append(tmp_string);
	for (int new_size = buffer.size(); old_size < new_size; old_size++)
		if (buffer[old_size] == '\n')
			line_offset.push_back(old_size + 1);

	// Visual Studio prints log source
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, &tmp_string[1]);
	OutputDebugString(tmp_string2);
}

void Console::DrawConsole(bool* p_open) {
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x * 0.4, ImGui::GetMainViewport()->Size.x * 0.2), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Output", p_open)){
		ImGui::End();
		return;
	}
	if (ImGui::BeginPopup("Options")) {
		ImGui::Checkbox("Enable Auto scroll", &autoscroll);
		if(ImGui::MenuItem("Close Console"))
			*p_open = false;
		ImGui::EndPopup();
	}
	if (ImGui::Button("Options")) {
		ImGui::OpenPopup("Options");
	}

	ImGui::SameLine();
	if (ImGui::Button("Clear"))
		ClearLog();
	ImGui::SameLine();
	if (ImGui::Button("Copy")) {
		ImGui::LogToClipboard();
	}
	ImGui::SameLine();
	filter.Draw();
		
	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	const char* buffer_start = buffer.begin();
	const char* buffer_end = buffer.end();

	if (filter.IsActive()) {
		for (int line_no = 0; line_no < line_offset.Size; line_no++){
			const char* line_start = buffer_start + line_offset[line_no];
			const char* line_end = (line_no + 1 < line_offset.Size) ? (buffer_start + line_offset[line_no + 1] - 1) : buffer_end;
			if (filter.PassFilter(line_start, line_end))
				ImGui::TextUnformatted(line_start, line_end);
		}
	}
	else {
		ImGuiListClipper clipper;
		clipper.Begin(line_offset.Size);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buffer_start + line_offset[line_no];
				const char* line_end = (line_no + 1 < line_offset.Size) ? (buffer_start + line_offset[line_no + 1] - 1) : buffer_end;
				ImGui::TextUnformatted(line_start, line_end);
			}
		}
		clipper.End();
	}
	ImGui::PopStyleVar();

	if (autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);
	ImGui::EndChild();
	ImGui::End();
}

void Console::ClearLog() {

}