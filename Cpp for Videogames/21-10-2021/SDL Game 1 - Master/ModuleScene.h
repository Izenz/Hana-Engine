#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleScene : public Module
{
public:

	ModuleScene();
	~ModuleScene();

	bool Init();
	bool Start();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

private:
	SDL_Texture* texture;
	SDL_Renderer* render;
};