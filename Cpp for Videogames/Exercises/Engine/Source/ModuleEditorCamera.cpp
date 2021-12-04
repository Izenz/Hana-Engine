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

	InitFrustum();

	return true;
}

update_status ModuleEditorCamera::PreUpdate() {

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {

	//if (RotationLock)	RotateCamera();

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

void ModuleEditorCamera::InitFrustum() {
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT));

	float3 InitPos(0.0f, 0.0f, 3.0f);
	float3 targetDir = (float3::zero - InitPos).Normalized();

	frustum.SetPos(InitPos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);
}

void ModuleEditorCamera::RotateCamera(CAM_AXIS axis, bool shiftPressed) {
	vec oldFront, oldUp;
	float3x3 rotDeltaMatrix;
	float step = rotationSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	switch (axis) {
	case CAM_AXIS::X:
		//rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitX, step);
		rotDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), step);
		break;
	case CAM_AXIS::X_NEGATIVE:
		//rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitX, -step);
		rotDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), -step);
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
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveRight(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveLeft(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveBackwards(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveUp(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + float3(0.0f, step, 0.0f));
}

void ModuleEditorCamera::MoveDown(bool shiftPressed) {
	float step = movSpeed * App->GetDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - float3(0.0f, step, 0.0f));
}

void ModuleEditorCamera::SetRotationLock(bool leftMouseButtonPressed) {
	//RotationLock = leftMouseButtonPressed;
}

void ModuleEditorCamera::CameraLookAt(const float3& newTargetPos) {
	float3 frustumPos = frustum.Pos();
	float3 targetDir = (newTargetPos - frustumPos).Normalized();

	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);
}