#pragma once

#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include <cmath>

#include "Application.h"
#include "Module.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleWindow.h"


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

	float4x4 GetProjMatrix();
	float4x4 GetViewMatrix();

	// Camera control

	void MoveForward(bool shiftPressed);
	void MoveLeft(bool shiftPressed);
	void MoveRight(bool shiftPressed);
	void MoveBackwards(bool shiftPressed);
	void MoveUp(bool shiftPressed);
	void MoveDown(bool shiftPressed);

	void RotateCamera(CAM_AXIS, bool shiftPressed);
	void RotateCameraMouse(CAM_AXIS, float step);
	void CameraLookAt(const float3& newTargetPos);
	void Orbit();
	void Roam();
	void FocusModel();

	// Setters
	
	void ToggleOrbit();
	void ToggleMouseControl();
	void SetAspectRatio(unsigned width, unsigned height);
	void SetPosition(const float3& newPos);

	// Getters
	float GetRotationSpeed() { return rotationSpeed; }

private:
	void InitFrustum();

	Frustum frustum;
	float movSpeed = 0.05f, rotationSpeed = 0.005f, orbitSpeed = 0.02f;
	math::Quat azimuth_angle = math::Quat::identity;
	math::Quat polar_angle = math::Quat::identity;
	bool isOrbitEnabled = false, isMouseControlEnabled = false;				//	true when LALT + LMB or LMB is clicked to rotate the camera in the editor.
};

