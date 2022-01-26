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
	unsigned GetSceneFramebuffer() const;

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
	unsigned panel_width = 0, panel_height = 0;
	GLuint framebuffer = 0;

	unsigned int fbo_id = 0;
	unsigned int texture_id = 0;
	unsigned int rbo_id = 0;
	//std::vector<GameObject> gameObjects;
};
