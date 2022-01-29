#pragma once
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "debugdraw.h"

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"
#include "ModuleEditorCamera.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "Model.h"
#include "Console.h"


class ModuleEditorCamera;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool Init() override;
	bool CleanUp() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	void ChangeModel(const char* file_path);
	const Model& GetCurrentModel() const;
	unsigned int GetSceneFramebuffer() const;

	ModuleEditorCamera* GetCamera() const;
	void UpdateRenderValues(unsigned width, unsigned height);
private:
	void DrawScene();
	void GenerateSceneFramebuffer();
private:

	Model currentModel;
	const char* currentModelPath = "";

	unsigned renderPanelShader = 0;

	// Render values used to print the editors Game View
	ModuleEditorCamera* cam;
	unsigned panel_width = 800, panel_height = 300;
	
	GLuint framebuffer = 0;
	GLuint fbo_id = 0;
	GLuint texture_id = 0;
	GLuint rbo_id = 0;
	//std::vector<GameObject> gameObjects;
};
