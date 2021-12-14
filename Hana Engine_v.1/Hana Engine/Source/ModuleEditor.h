#pragma once
#include "Module.h"
#include "Globals.h"
#include "TimeManager.h"
#include "Application.h"

class ModuleEditorCamera;

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void DrawEditorEnvironment();

	void DrawWindowMainMenu();
	void DrawEngineInfoWindow(bool* p_open) const;

	ModuleEditorCamera* cam;
private:
	bool b = false;
	bool p_open = true;

	bool showEngineInfo = false, showConsole = true, showTimeWindow = true;
	bool showModulesInfoWindow = false, showResourceManager = false, showConsumptionWindow = false;
};