#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "Model.h"
#include "ModuleTexture.h"

class ModuleRenderExercise : public Module
{
public:
	bool Init();
	bool CleanUp();
	update_status Update();
	update_status PostUpdate();
	GLuint program;
	
private:
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle();
	void LoadBakerHouse();
	
private:
	GLuint vbo;
	Model houseModel;

	float4x4 model, view, projection;
	Frustum frustum;
};
