#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
};