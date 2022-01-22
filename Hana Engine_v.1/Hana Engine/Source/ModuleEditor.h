#pragma once
#include "Module.h"
#include "Globals.h"
#include "TimeManager.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "TimeManager.h"
#include <vector>

class ModuleEditorCamera;

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

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
	

	ModuleEditorCamera* cam;
private:
	const char* default_scene_name = "untitled_scene";
	bool scene_open = true;
	bool window_active[(int) WINDOW_TYPES::MAX + 1];
};