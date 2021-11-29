#pragma once

#include "Module.h"
#include "GL/glew.h"
#include "il.h"
#include "SDL.h"
#include <assert.h>
#include <stdio.h>
#include <iostream>

class ModuleTexture : public Module {

public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	bool CleanUp();

	unsigned LoadTexture(const char* texturePath);
private:

};