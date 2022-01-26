#pragma once
#include "Module.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleScene.h"

class ModuleEditorCamera : public Module {

public:
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

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
	Frustum frustum;
	float movSpeed = 0.05f, rotationSpeed = 0.005f, orbitSpeed = 0.02f;
	float rotationAngleX = 0.0f, rotationAngleY = 0.0f, rotationAngleZ = 0.0f;
	int mouseX = 0, mouseY = 0;
	bool isOrbitEnabled = false, isMouseControlEnabled = false;				//	true when LALT + LMB or LMB is clicked to rotate the camera in the editor.

	void InitFrustum();
};

