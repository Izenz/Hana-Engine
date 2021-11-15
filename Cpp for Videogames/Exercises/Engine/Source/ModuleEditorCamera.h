#pragma once
#include "Module.h"
#include "Geometry\Frustum.h"

class ModuleEditorCamera : public Module {

public:
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
private:
	Frustum frustum;
};

