#pragma once

#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "SDL.h"
#include "SDL/include/SDL_scancode.h"
#include <cmath>

#include "Application.h"
#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"
#include "ModuleScene.h"


struct Plan {
	float3	normal = {0.f, 1.f, 0.f};
	// Distance from origin to nearest point in the plan
	float	distance = 0.f;
};

struct Volume {
	virtual bool IsOnFrustum(const Frustum& cam, const float3x3& model) const = 0;
};

struct AABB : public Volume {
	float3	center{	0.f, 1.f, 0.f };
	float3	extents{ 0.f, 1.f, 0.f };

	bool IsOnFrustum(const Frustum& cam, const float3x3& model) const final {
		const float4 globalCenter{ model * float4(center, 1.f) };
		//const float3 right = transform.GetRight() * extents.x;
		//const float3 up = transform.GetUp() * extents.y;
		//const float3 forward = transform.GetForward() * extents.z;

		 
		return true;
	}
};

class ModuleEditorCamera : public Module {

public:
	bool Init();

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	float4x4 GetProjMatrix() const;
	float4x4 GetViewMatrix() const;

	// Camera control
	void MoveForward();
	void MoveLeft();
	void MoveRight();
	void MoveBackwards();
	void MoveUp();
	void MoveDown();

	void CameraLookAt(const float3& newTargetPos);
	void FocusObject();	// TODO

	// Setters
	void SetAspectRatio(unsigned width, unsigned height);

private:
	void InitFrustum();
	void HandleCameraMovement();
	void HandleCameraRotation();

	void Orbit();
	void RotateCamera();

	Frustum frustum;

	const float movSpeed = 0.02f;
	const float rotationSpeed = 0.002f;
	const float orbitSpeed = 0.02f;

	math::Quat azimuth_angle = math::Quat::identity;
	math::Quat polar_angle = math::Quat::identity;

	float3 pitch, yaw;	// up and front respectively
};

