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
	void CameraLookAt(const float3& newTargetPos);

	// Setters

	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition(float3 newPos);
	void SetOrientation();
	void SetRotationLock(bool leftMouseButtonPressed);

	// Getters

	float GetRotationSpeed() { return rotationSpeed; }

	
	
	
private:
	Frustum frustum;
	float movSpeed = 0.05f, rotationSpeed = 0.005f;
	float rotationAngleX = 0.0f, rotationAngleY = 0.0f, rotationAngleZ = 0.0f;
	int mouseX = 0, mouseY = 0;
	//bool RotationLock = false;				//	true when LMB is clicked to rotate the camera in the editor.

	void InitFrustum();
};

