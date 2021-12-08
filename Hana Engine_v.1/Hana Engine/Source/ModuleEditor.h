#pragma once
#include "Module.h"
#include "Globals.h"

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

	ModuleEditorCamera* cam;
private:
	
	void* context;
	bool b = false;
	bool p_open = true;
};