#pragma once
#include "Module.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"

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

	// Setters

	void SetRotationLock(bool leftMouseButtonPressed);

	// Getters

	float GetRotationSpeed() { return rotationSpeed; }

	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition(float3 newPos);
	void SetOrientation();
	void LookAt(float3 newTargetPos);
	
private:
	Frustum frustum;
	float3 frustumPos =  float3(0.0f, 10.0f, 5.0f);
	float movSpeed = 2.0f, rotationSpeed = 0.5f;
	float rotationAngleX = 0.0f, rotationAngleY = 0.0f, rotationAngleZ = 0.0f;
	int mouseX = 0, mouseY = 0;
	bool RotationLock = false;				//	true when LMB is clicked to rotate the camera in the editor.

	
};

