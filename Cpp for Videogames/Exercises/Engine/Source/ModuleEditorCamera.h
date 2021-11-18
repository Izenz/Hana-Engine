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
private:
	Frustum frustum;
};

