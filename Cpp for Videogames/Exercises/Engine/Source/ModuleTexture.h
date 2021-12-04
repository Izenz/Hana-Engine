#pragma once
#include "Module.h"
#include "GL/glew.h"
#include "il.h"
#include "SDL.h"
#include <assert.h>
#include <stdio.h>
#include <iostream>

struct Texture {
	bool isLoaded = false;
	unsigned id = 0, width = 0, height = 0;
	std::string path;

	Texture(unsigned _id, const char* _path) {
		id = _id;
		path = _path;
	}
};

class ModuleTexture : public Module {

public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	bool CleanUp();
	Texture Load(const char* texturePath);

private:
	unsigned LoadTexture(const char* texturePath);
	unsigned numLoadedTextures = 0;
};