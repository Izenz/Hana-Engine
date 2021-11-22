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

	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition(float3 newPos);
	void SetOrientation();
	void MoveForward();
	void MoveLeft();
	void MoveRight();
	void MoveBackwards();
	void LookAt(float3 newTarget);
	void RotateCamera(CAM_AXIS, float angle);
	void SetRotationLock(bool leftMouseButtonPressed);
	float GetRotationSpeed() { return rotationSpeed; }
private:
	Frustum frustum;
	float3 frustumPos =  float3(0.0f, 10.0f, 5.0f);
	float movSpeed = 2.0f, rotationSpeed = 3.0f;
	float rotationAngleX = 0.0f, rotationAngleY = 0.0f, rotationAngleZ = 0.0f;
	int mouseX = 0, mouseY = 0;
	bool RotationLock = false;				//	true when LMB is clicked to rotate the camera in the editor.

	
};

