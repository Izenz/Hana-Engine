#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"

class ModuleRenderExercise : public Module
{
public:
	bool Init();
	bool CleanUp();
	update_status Update();

	
private:
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle();
private:
	GLuint vbo;
	GLuint program;

	//float4x4 model, view, projection;
	//Frustum frustum;
};
