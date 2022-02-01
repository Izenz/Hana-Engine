#pragma once

#include "imgui.h"
#include "stdio.h"
#include <memory>

#include "Globals.h"
#include "Application.h"

class GameObject;

class Component
{
public:
	enum class COMPONENT_TYPE
	{
		//CAMERA,	Game Object?
		//LIGHT,	Game Object?
		TRANSFORM,
		MESH,
		MATERIAL,
		BOUNDING_BOX,
		UNDEFINED
	};
public:
	Component();
	Component(GameObject& new_owner, COMPONENT_TYPE type);
	virtual ~Component() = default;

	inline unsigned int GetId() const { return uid; };
	inline COMPONENT_TYPE GetType() const { return type; };

	inline const std::shared_ptr<GameObject> Parent() const { return parent; };

	inline void Enable() { enabled = true; };
	inline void Disable() { enabled = false; };
	inline bool isEnabled() const { return enabled; };

	virtual void PreUpdate();
	virtual void Update();
	virtual void PostUpdate();

protected:
	bool enabled = true;
	std::shared_ptr<GameObject> parent = nullptr;
	unsigned int uid;
	COMPONENT_TYPE type = COMPONENT_TYPE::UNDEFINED;
};