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
	void LookAt(float3 newTarget);
private:
	Frustum frustum;
};

