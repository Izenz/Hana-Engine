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
	// Frustum setup
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);
	frustum.SetHorizontalFovAndAspectRatio(float(DEGTORAD)* 90.0f, float(window_width) / float(window_height));

	float3 pos(2.0f, 4.0f, 6.0f);
	float3 targetDir = (float3::zero - pos).Normalized();

	frustum.SetPos(pos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);

	currentModelPath = "Models/BakerHouse.fbx";
	//currentModelPath = "Models/BED.fbx";
	//currentModelPath = "Models/earth.fbx";
	return true;
}

update_status ModuleRenderExercise::Update() {

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-100, 100, 0.0f, 1.0f, dd::colors::Gray);

	LoadModel();
	
	return update_status::UPDATE_CONTINUE;
}

void ModuleRenderExercise::LoadModel() {
	
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