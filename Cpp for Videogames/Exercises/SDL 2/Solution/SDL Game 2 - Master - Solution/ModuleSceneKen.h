#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;

	Animation flag;
	Animation girl;

	int shipMovementTimer = 0.0f;
	int shipMovementDirection = 1;
	int shipPositionY = -5;

private:
	void UpdateShipPosition();
};

#endif // __MODULESCENEKEN_H__