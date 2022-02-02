#include "ModuleEditorCamera.h"


bool ModuleEditorCamera::Init() {
	InitFrustum();
	pitch = frustum.Up();
	yaw = frustum.Front();
	return true;
}

update_status ModuleEditorCamera::PreUpdate() {
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {
	HandleCameraRotation();
	HandleCameraMovement();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}

void ModuleEditorCamera::InitFrustum() {
	unsigned width, height;
	App->window->GetWindowSize(width, height);

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);
	frustum.SetHorizontalFovAndAspectRatio(float(DEGTORAD)* 90.0f, float(width) / float(height));

	float3 InitPos(0.0f, 0.0f, 3.0f);
	float3 targetDir = (float3::zero - InitPos).Normalized();

	frustum.SetPos(InitPos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);
}

void ModuleEditorCamera::HandleCameraMovement() {
	if (App->input->isKeyPressed(SDL_SCANCODE_W))		MoveForward();
	if (App->input->isKeyPressed(SDL_SCANCODE_A))		MoveLeft();
	if (App->input->isKeyPressed(SDL_SCANCODE_S))		MoveBackwards();
	if (App->input->isKeyPressed(SDL_SCANCODE_D))		MoveRight();
	if (App->input->isKeyPressed(SDL_SCANCODE_Q))		MoveUp();
	if (App->input->isKeyPressed(SDL_SCANCODE_E))		MoveDown();	

	if (App->input->GetWheelMotion().y > 0)				MoveForward();
	else if (App->input->GetWheelMotion().y < 0)		MoveBackwards();
}

void ModuleEditorCamera::HandleCameraRotation() {
	if (App->input->isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
		App->input->isKeyPressed(SDL_SCANCODE_LALT) ? Orbit() : RotateCamera();
	}
}

float4x4 ModuleEditorCamera::GetProjMatrix() const {
	return frustum.ComputeProjectionMatrix();
}

float4x4 ModuleEditorCamera::GetViewMatrix() const {
	return float4x4(frustum.ComputeViewMatrix());
}

void ModuleEditorCamera::MoveForward() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveRight() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveLeft() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.WorldRight().Mul(step));
}

void ModuleEditorCamera::MoveBackwards() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.Front().Mul(step));
}

void ModuleEditorCamera::MoveUp() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() + frustum.Up().Mul(step));
}

void ModuleEditorCamera::MoveDown() {
	float step = movSpeed * Time->GetRealDeltaTime();
	if (App->input->isKeyPressed(SDL_SCANCODE_LSHIFT))	step *= 2.0f;

	frustum.SetPos(frustum.Pos() - frustum.Up().Mul(step));
}

void ModuleEditorCamera::RotateCamera()
{
	float2 mouse_delta = App->input->GetMouseMotion();
	float yaw_step = mouse_delta.x * rotationSpeed * Time->GetRealDeltaTime();
	float pitch_step = mouse_delta.y * rotationSpeed * Time->GetRealDeltaTime();

	if (yaw_step != 0.0f) {
		math::Quat rotation_vector = Quat::RotateY(yaw_step);
		yaw = rotation_vector.Mul(frustum.Front()).Normalized();
		pitch = rotation_vector.Mul(frustum.Up()).Normalized();
		frustum.SetFront(yaw);
		frustum.SetUp(pitch);
	}

	if (pitch_step != 0.0f) {
		math::Quat rotation_vector = Quat::RotateAxisAngle(frustum.WorldRight(), pitch_step);
		yaw = rotation_vector.Mul(frustum.Front()).Normalized();
		pitch = rotation_vector.Mul(frustum.Up()).Normalized();
		frustum.SetFront(yaw);
		frustum.SetUp(pitch);
	}
}

void ModuleEditorCamera::CameraLookAt(const float3& newTargetPos) {
	float3 newDir = (newTargetPos - frustum.Pos()).Normalized();
	float3 temp_right = float3::unitY.Cross(newDir).Normalized();
	float3 temp_up = newDir.Cross(temp_right).Normalized();

	frustum.SetFront(newDir);
	frustum.SetUp(temp_up);
}

void ModuleEditorCamera::SetAspectRatio(unsigned width, unsigned height) {
	frustum.SetHorizontalFovAndAspectRatio(float(DEGTORAD) * 90.0f, float(width) / float(height));
}

void ModuleEditorCamera::Orbit() {
	vec focus = float3::zero;		// Focusing Origin for now.

	float2 motion = App->input->GetMouseMotion();

	float x_delta = math::DegToRad(motion.x * orbitSpeed * Time->GetRealDeltaTime());
	float y_delta = math::DegToRad(motion.y * orbitSpeed * Time->GetRealDeltaTime());

	azimuth_angle = Quat::RotateAxisAngle(frustum.WorldRight(), -y_delta);
	polar_angle = Quat::RotateAxisAngle(frustum.Up(), -x_delta);
	
	float3 orbit_dir = float3::zero - frustum.Pos();
	orbit_dir = (polar_angle * azimuth_angle).Transform(orbit_dir);

	frustum.SetPos(focus - orbit_dir);
	CameraLookAt(orbit_dir);
}

void ModuleEditorCamera::FocusObject() {
	// TODO: Complete this function
	// Get point to look at (model's OBB center point)
	
	//vec modelCenterPos = current_model.GetFocusTarget();

	// Get Camera to look towards model center

	// Move Camera to fit OBB inside frustum
}

