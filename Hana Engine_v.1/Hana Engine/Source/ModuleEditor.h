#pragma once
#include "Module.h"
#include "Application.h"
#include "Globals.h"
#include "TimeManager.h"
#include "Application.h"
#include "ModuleScene.h"
#include "TimeManager.h"
#include "ModuleScene.h"
#include <vector>
#include "ComponentTransform.h"
#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

struct AboutInfo {

	unsigned char* system;
	int cpu;
	float ram;
	unsigned char* gpu;
	unsigned char* gpu_vendor;
	int vram_capacity;
	int vram_free;
	SDL_version sdl_version;
};

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void DrawEditorEnvironment();
	void DrawEditorMainMenu();
	void LoadSceneInEditor();

	// Draw methods for different windows

	void CreateDockingSpace() const;
	void DrawGameSceneWindow(bool* is_open) const;
	void DrawHierarchyWindow(bool* is_open) const;
	void DrawInspectorWindow(bool* is_open) const;
	void DrawResourcesWindow(bool* is_open) const;
	void DrawExplorerWindow(bool* is_open) const;
	void DrawTimeControlWindow(bool* is_open) const;
	void DrawEngineConfigWindow(bool* is_open) const;
	void DrawEngineInfoWindow(bool* p_open) const;
	void DrawPerformanceWindow(bool* p_open);
	float DrawFPS();

private:
	const char* default_scene_name = "untitled_scene";
	bool scene_open = true;
	bool draw_fps = true;
	std::vector<float> ms_buffer;
	std::vector<float> fps_buffer;
	bool window_active[(int) WINDOW_TYPES::MAX + 1];
	AboutInfo about;
};