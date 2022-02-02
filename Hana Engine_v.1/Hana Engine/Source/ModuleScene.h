#pragma once
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "MathGeoLib_Source/Algorithm/Random/LCG.h"
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
#include "GameObject.h"


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

	void HandleKeyboardShortcuts();

	void ChangeModel(const char* file_path);
	const Model& GetCurrentModel() const;
	unsigned int GetSceneFramebuffer() const;
	GameObject* GetRoot() const { return root; };
	GameObject* GetSelected() const { return selected_object; };
	void SetSelected(GameObject* newSelected) { selected_object = newSelected; };

	ModuleEditorCamera* GetCamera() const;
	void UpdateRenderValues(unsigned width, unsigned height);
	u32 GenerateUID() const;

	void AddEmptyGameObject();
	void AddGameObject(GameObject & go);
	void RemoveGameObject(GameObject& go);
	void DrawHierarchy(); 
private:
	void DrawScene();
	void GenerateSceneFramebuffer();

	void TestHierarchy();
private:

	Model currentModel;
	const char* currentModelPath = "";

	ModuleEditorCamera* cam;
	unsigned panel_width = 800, panel_height = 300;
	
	GLuint framebuffer = 0;
	GLuint fbo_id = 0;
	GLuint texture_id = 0;
	GLuint rbo_id = 0;

	std::list<GameObject*> gameObjects;
	GameObject* root;
	GameObject* selected_object = nullptr;

	math::LCG* randomGenerator;
};
