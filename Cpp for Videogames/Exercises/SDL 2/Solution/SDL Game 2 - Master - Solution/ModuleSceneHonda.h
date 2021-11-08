#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda( bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect pool;
};

#endif // __MODULESCENEKEN_H__