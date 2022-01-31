#include "ModuleScene.h"


ModuleScene::ModuleScene() {
	cam = new ModuleEditorCamera();
}

ModuleScene::~ModuleScene() {
}

bool ModuleScene::Init() {
	cam->Init();
	GenerateSceneFramebuffer();

	currentModelPath = "Models/BakerHouse.fbx";
	//currentModelPath = "Models/BED.fbx";
	//currentModelPath = "Models/earth.fbx";
	return true;
}

update_status ModuleScene::PreUpdate()
{
	
	cam->PreUpdate();
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene::Update() {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-100, 100, 0.0f, 1.0f, dd::colors::Gray);

	DrawScene();

	App->debugDraw->Draw(cam->GetViewMatrix(), cam->GetProjMatrix(), panel_width, panel_height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	cam->Update();
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate() {
	cam->PostUpdate();
	return update_status::UPDATE_CONTINUE;
}

void ModuleScene::DrawScene() {
	if (!currentModel.IsLoaded())
		currentModel.Load(currentModelPath);
	currentModel.Draw();
}

bool ModuleScene::CleanUp() {
	delete cam;
	currentModel.CleanUp();
	glDeleteFramebuffers(1, &framebuffer);
	return true;
}

void ModuleScene::ChangeModel(const char* file_path) {
	currentModel.CleanUp();
	currentModelPath = file_path;
}

const Model& ModuleScene::GetCurrentModel() const {
	return currentModel;
}

void ModuleScene::GenerateSceneFramebuffer() {
	
	// Generate FB and bind it.
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create texture image with the size of the window and attach it to FB.
	GLuint textureColorbuffer = 0;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, panel_width, panel_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Create rbo to allow OpenGL to do depth and occasionally stencil testing
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, panel_width, panel_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach it to currently bound FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

	// Check if fb is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		LOG("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned ModuleScene::GetSceneFramebuffer() const {
	return texture_id;
}

ModuleEditorCamera* ModuleScene::GetCamera() const {
	return cam;
}

void ModuleScene::UpdateRenderValues(unsigned _panel_width, unsigned _panel_height)
{
	if (panel_width != _panel_width || _panel_height != _panel_height) {
		LOG("Updating camera values: w: %i, h: %i", _panel_width, _panel_height);
		panel_width = _panel_width;
		panel_height = _panel_height;
		cam->SetAspectRatio(_panel_width, _panel_height);

		if (framebuffer != 0)
			glDeleteFramebuffers(1, &framebuffer);
		GenerateSceneFramebuffer();
	}
}
