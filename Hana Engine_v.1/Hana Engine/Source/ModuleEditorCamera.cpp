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
#include "ModuleWindow.h"



bool ModuleEditorCamera::Init() {

	InitFrustum();

	return true;
}

update_status ModuleEditorCamera::PreUpdate() {

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {
	if (isOrbitEnabled && isMouseControlEnabled) {
		Orbit();
	}
	else if (isMouseControlEnabled && !isOrbitEnabled) {
		Roam();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

void ModuleEditorCamera::InitFrustum() {
	unsigned width, height;
	App->window->GetWindowSize(width, height);

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, float(width) / float(height));

	float3 InitPos(0.0f, 0.0f, 3.0f);
	float3 targetDir = (float3::zero - InitPos).Normalized();

	frustum.SetPos(InitPos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);
}

void ModuleEditorCamera::RotateCamera(CAM_AXIS axis, bool shiftPressed) {
	vec oldFront, oldUp;
	float3x3 rotDeltaMatrix;
	float step = rotationSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	switch (axis) {
	case CAM_AXIS::X:
		rotDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), step);
		break;
	case CAM_AXIS::X_NEGATIVE:
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

void ModuleEditorCamera::RotateCameraMouse(CAM_AXIS axis, float step) {
	vec oldFront, oldUp;
	float3x3 rotDeltaMatrix;

	switch (axis) {
	case CAM_AXIS::X:
		rotDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), step * rotationSpeed * Time->GetRealDeltaTime());
		break;
	case CAM_AXIS::X_NEGATIVE:
		rotDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), -step * rotationSpeed * Time->GetRealDeltaTime());
		break;
	case CAM_AXIS::Y:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitY, step * rotationSpeed * Time->GetRealDeltaTime());
		break;
	case CAM_AXIS::Y_NEGATIVE:
		rotDeltaMatrix = float3x3::RotateAxisAngle(float3::unitY, -step * rotationSpeed * Time->GetRealDeltaTime());
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
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveRight(bool shiftPressed) {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveLeft(bool shiftPressed) {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveBackwards(bool shiftPressed) {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveUp(bool shiftPressed) {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.Up().Mul(step));
}

void ModuleEditorCamera::MoveDown(bool shiftPressed) {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (shiftPressed)	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.Up().Mul(step));
}

void ModuleEditorCamera::CameraLookAt(const float3& newTargetPos) {
	float3 frustumPos = frustum.Pos();
	float3 targetDir = (newTargetPos - frustumPos).Normalized();
	float3 newUp = frustum.WorldRight().Cross(targetDir);

	frustum.SetFront(targetDir);
	frustum.SetUp(newUp);
}

void ModuleEditorCamera::SetAspectRatio(unsigned width, unsigned height) {
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, float(width) / float(height));
}

void ModuleEditorCamera::SetPosition(const float3& newPos) {
	frustum.SetPos(newPos);
}

void ModuleEditorCamera::ToggleOrbit() {
	isOrbitEnabled = !isOrbitEnabled;
}

void ModuleEditorCamera::ToggleMouseControl() {
	isMouseControlEnabled = !isMouseControlEnabled;
}

void ModuleEditorCamera::Roam() {
	int motion_x, motion_y;
	App->input->GetMouseMotion(motion_x, motion_y);

	RotateCameraMouse(CAM_AXIS::Y, motion_x * orbitSpeed * Time->GetRealDeltaTime());
	RotateCameraMouse(CAM_AXIS::X, motion_y * orbitSpeed * Time->GetRealDeltaTime());
}

void ModuleEditorCamera::Orbit() {
	float3 focus = float3::zero;
	int motion_x, motion_y;
	App->input->GetMouseMotion(motion_x, motion_y);

	if (motion_x > 0)
	{
		MoveRight(false);
	}
	else if (motion_x < 0)
	{
		MoveLeft(false);
	}

	if (motion_y > 0)
	{
		MoveDown(false);
	}
	else if (motion_y < 0)
	{
		MoveUp(false);
	}

	//App->exercise->GetCurrentModelPos(focus);
	CameraLookAt(focus);
}

void ModuleEditorCamera::FocusModel() {
	
}