#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "Model.h"
#include "ModuleTexture.h"
#include "Console.h"

class ModuleRenderExercise : public Module
{
public:
	bool Init();
	bool CleanUp();
	update_status Update();
	update_status PostUpdate();
	void ChangeModel(const char* file_path);
	void UpdateWindowSize();
	const Model& GetCurrentModel() const;
	
private:
	void LoadModel();
	
private:
	Model currentModel;
	const char* currentModelPath = "";

	float4x4 model, view, projection;
	Frustum frustum;

	unsigned window_width = 0, window_height = 0;
};
