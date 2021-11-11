#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"

class ModuleRenderExercise : public Module
{
public:
	bool Init();
	bool CleanUp();
	update_status Update();
private:
	void RenderVBO(unsigned vbo, unsigned program);
private:
	GLuint vbo;
	GLuint program;
};
