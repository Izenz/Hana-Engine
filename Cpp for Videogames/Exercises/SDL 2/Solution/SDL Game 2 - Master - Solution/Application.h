#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleSceneKen;
class ModuleSceneHonda;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	// Should initialize variables.
	ModuleRender* renderer = nullptr;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleSceneKen* scene_ken;
	ModuleSceneHonda* scene_honda;

private:
	// Would be better to use a vector since we are not adding modules in execution time.
	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__