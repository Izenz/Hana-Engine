#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;

	Animation* currentAnimation = nullptr;

	Animation idle;
	Animation forward;
	Animation backward;
	iPoint position;

	int speed = 1;
};

#endif // __MODULEPLAYER_H__