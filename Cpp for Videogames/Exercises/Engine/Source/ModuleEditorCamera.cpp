#include "ModuleEditorCamera.h"
#include "Globals.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"


bool ModuleEditorCamera::Init() {

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT));

	float3 pos(0.0f, 2.0f, 3.0f);
	float3 targetDir = (float3::zero - pos).Normalized();

	frustum.SetPos(pos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);

	return true;
}

update_status ModuleEditorCamera::PreUpdate() {

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {

	frustum.SetPos(frustumPos);
	//if (RotationLock)	RotateCamera();
	
	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

void ModuleEditorCamera::RotateCamera(CAM_AXIS axis, float angle) {
	
	//SDL_GetMouseState(&mouseX, &mouseY);
	switch (axis) {
	case CAM_AXIS::X:
		// Should rotate with axis X local to camera, perpendicular to up and targetDir
		//float3x3::RotateAxisAngle( , angle);
		break;
	case CAM_AXIS::Y:
		// Check 15-11 Game Camera slides.
		float3x3::RotateAxisAngle(float3::unitY, angle);
		break;
	case CAM_AXIS::Z:
		// Should not be the case for now
		break;
	}
	
}

float4x4 ModuleEditorCamera::GetProjMatrix() {
	return frustum.ComputeProjectionMatrix();
}

float4x4 ModuleEditorCamera::GetViewMatrix() {
	return float4x4(frustum.ViewMatrix());
}

void ModuleEditorCamera::MoveForward() {
	frustumPos -= float3(0.0f, 0.0f, 1.0f * movSpeed * App->GetDeltaTime());
}

void ModuleEditorCamera::MoveRight() {
	frustumPos += float3(1.0f * movSpeed * App->GetDeltaTime(), 0.0f, 0.0f);
}

void ModuleEditorCamera::MoveLeft() {
	frustumPos -= float3(1.0f * movSpeed * App->GetDeltaTime(), 0.0f, 0.0f);
}

void ModuleEditorCamera::MoveBackwards() {
	frustumPos += float3(0.0f, 0.0f, 1.0f * movSpeed * App->GetDeltaTime());
}

void ModuleEditorCamera::SetRotationLock(bool leftMouseButtonPressed) {
	RotationLock = leftMouseButtonPressed;
}