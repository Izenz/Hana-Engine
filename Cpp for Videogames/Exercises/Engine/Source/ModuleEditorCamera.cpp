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

void ModuleEditorCamera::RotateCamera(CAM_AXIS axis, bool shiftPressed) {
	vec oldFront, oldUp;
	float3x3 rotDeltaMatrix;
	float step = rotationSpeed * App->GetDeltaTime();
	step *= shiftPressed ? 2.0f : 1.0f;

	switch (axis) {
	case CAM_AXIS::X:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitX, step);
		break;
	case CAM_AXIS::X_NEGATIVE:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitX, -step);
		break;
	case CAM_AXIS::Y:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitY, step);
		break;
	case CAM_AXIS::Y_NEGATIVE:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitY, -step);
		break;
	default:
		break;
	}

	oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotDeltaMatrix.MulDir(oldFront));

	oldUp = frustum.Up().Normalized();
	frustum.SetUp(rotDeltaMatrix.MulDir(oldUp));


}

float4x4 ModuleEditorCamera::GetProjMatrix() {
	return frustum.ComputeProjectionMatrix();
}

float4x4 ModuleEditorCamera::GetViewMatrix() {
	return float4x4(frustum.ComputeViewMatrix());
}

void ModuleEditorCamera::MoveForward(bool shiftPressed) {
	frustumPos += frustum.Front().Mul(movSpeed * App->GetDeltaTime());
}

void ModuleEditorCamera::MoveRight(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	step *= shiftPressed ? 2.0f : 1.0f;

	frustumPos += frustum.WorldRight().Mul(step);
}

void ModuleEditorCamera::MoveLeft(bool shiftPressed) {
	//frustumPos -= float3(1.0f * movSpeed * App->GetDeltaTime(), 0.0f, 0.0f);
	frustumPos -= frustum.WorldRight().Mul(movSpeed * App->GetDeltaTime());
}

void ModuleEditorCamera::MoveBackwards(bool shiftPressed) {
	//frustumPos += float3(0.0f, 0.0f, 1.0f * movSpeed * App->GetDeltaTime());
	frustumPos -= frustum.Front().Mul(movSpeed * App->GetDeltaTime());
}

void ModuleEditorCamera::MoveUp(bool shiftPressed) {
	frustumPos += float3(0.0f, movSpeed * App->GetDeltaTime(), 0.0f);
}

void ModuleEditorCamera::MoveDown(bool shiftPressed) {
	frustumPos -= float3(0.0f, movSpeed * App->GetDeltaTime(), 0.0f);
}

void ModuleEditorCamera::SetRotationLock(bool leftMouseButtonPressed) {
	RotationLock = leftMouseButtonPressed;
}