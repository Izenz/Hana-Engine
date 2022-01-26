#include "ModuleScene.h"
#include "ModuleProgram.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleEditorCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "ModuleWindow.h"

ModuleScene::ModuleScene() {
	cam = new ModuleEditorCamera();
}

ModuleScene::~ModuleScene() {
}

bool ModuleScene::Init() {
	cam->Init();
	//GenerateSceneFramebuffer();

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
	/*
	const unsigned shader = App->program->GetDefaultProgram();
	//const unsigned toTextureShader = App->program->CreateShadersProgram("Shaders/vert_renderToTexture.glsl", "Shaders/frag_renderToTexture.glsl");
	glUseProgram(shader);

	float4x4 model = float4x4::identity;
	float4x4 view = cam->GetViewMatrix();
	float4x4 proj = cam->GetProjMatrix();

	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_TRUE, &proj[0][0]);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader);
	DrawScene();
	App->debugDraw->Draw(view, proj, panel_width, panel_height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	cam->Update();
	*/
	//ImGui::ShowMetricsWindow();
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/*
	// Draw scene into texture
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Clear previous frame
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Draw scene to be rendered in Scene Viewer panel.
	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-100, 100, 0.0f, 1.0f, dd::colors::Gray);
	DrawScene();

	// Unbind texture framebuffer to not mess with other stuff
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	cam->Update();
	*/
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate() {
	cam->PostUpdate();
	return update_status::UPDATE_CONTINUE;
}

void ModuleScene::DrawScene() {
	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-100, 100, 0.0f, 1.0f, dd::colors::Gray);
	//if (!currentModel.IsLoaded())
	//	currentModel.Load(currentModelPath);
	//currentModel.Draw();

	//App->debugDraw->Draw(cam->GetViewMatrix(), cam->GetProjMatrix(), panel_width, panel_height);
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
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, panel_width, panel_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glBindTexture(GL_TEXTURE_2D, 0);

	//Create rbo to allow OpenGL to do depth and occasionally stencil testing
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, panel_width, panel_height);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach rbo to depth and stencil attachment of fb
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Attach it to currently bound FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	// Check if fb is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		LOG("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/*
	glCreateFramebuffers(1, &fbo_id);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

	//TODO consider rendering to screen size instead of viewport size
	//create associated texture
	glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);

	glTextureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTextureStorage2D(texture_id, 1, GL_RGB8, panel_width, panel_height);

	glNamedFramebufferTexture(fbo_id, GL_COLOR_ATTACHMENT0, texture_id, 0);

	//create render buffer (depth)
	glCreateRenderbuffers(1, &rbo_id);
	glNamedRenderbufferStorage(rbo_id, GL_DEPTH24_STENCIL8, panel_width, panel_height);
	glNamedFramebufferRenderbuffer(fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);

	//check if creation was successful
	assert(glCheckNamedFramebufferStatus(rbo_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
	*/
}

unsigned ModuleScene::GetSceneFramebuffer() const {
	return framebuffer;
}

ModuleEditorCamera* ModuleScene::GetCamera() const {
	return cam;
}

void ModuleScene::UpdateRenderValues(unsigned _panel_width, unsigned _panel_height)
{
	if (panel_width != _panel_width || _panel_height != _panel_height) {
		panel_width = _panel_width;
		panel_height = _panel_height;
		cam->SetAspectRatio(_panel_width, _panel_height);

		// TODO: If there was a previous framebuffer generated, delete it.
		GenerateSceneFramebuffer();
	}
}
