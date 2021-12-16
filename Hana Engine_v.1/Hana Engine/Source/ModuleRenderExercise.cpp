#include "ModuleRenderExercise.h"
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


bool ModuleRenderExercise::Init() {
	UpdateWindowSize();
	InitFrustum();
	RenderSceneToTexture();

	currentModelPath = "Models/BakerHouse.fbx";
	//currentModelPath = "Models/BED.fbx";
	//currentModelPath = "Models/earth.fbx";
	return true;
}

update_status ModuleRenderExercise::Update() {
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
	return update_status::UPDATE_CONTINUE;
}

void ModuleRenderExercise::DrawScene() {
	
	projection = App->editor->cam->GetProjMatrix();
	view = App->editor->cam->GetViewMatrix();

	if(!currentModel.IsLoaded())
		currentModel.Load(currentModelPath);
	currentModel.Draw();

	App->debugDraw->Draw(view, projection, window_width, window_height);
}

update_status ModuleRenderExercise::PostUpdate() {

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp() {
	currentModel.CleanUp();

	return true;
}

void ModuleRenderExercise::ChangeModel(const char* file_path) {
	currentModel.CleanUp();
	currentModelPath = file_path;
}

void ModuleRenderExercise::UpdateWindowSize() {
	App->window->GetWindowSize(window_width, window_height);
}

const Model& ModuleRenderExercise::GetCurrentModel() const {
	return currentModel;
}

void ModuleRenderExercise::RenderSceneToTexture() {
	// Generate FB and bind it.
	glGenFramebuffers(1, &framebuffer);
	glBindBuffer(GL_FRAMEBUFFER, framebuffer);

	// Create texture image with the size of the window and attach it to FB.
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach it to currently bound FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	//Create rbo to allow OpenGL to do depth and ocasionally stencil testing
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_width, window_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach rbo to depth and stencil attachment of fb
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Check if fb is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		LOG("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ModuleRenderExercise::InitFrustum() {
	// Frustum setup
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);
	frustum.SetHorizontalFovAndAspectRatio(float(DEGTORAD) * 90.0f, float(window_width) / float(window_height));

	float3 pos(2.0f, 4.0f, 6.0f);
	float3 targetDir = (float3::zero - pos).Normalized();

	frustum.SetPos(pos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);

}

unsigned ModuleRenderExercise::GetSceneTexture() const {
	return framebuffer;
}