#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Console.h"
#include "TimeManager.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleEditor;
class ModuleScene;
class ModuleDebugDraw;
class ModuleTexture;


class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTexture* textures = nullptr;
	
	ModuleProgram* program = nullptr;
	ModuleScene* scene = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	
private:
	std::list<Module*> modules;
};

extern Application* App;
