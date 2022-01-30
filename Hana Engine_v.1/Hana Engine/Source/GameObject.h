#pragma once


#include "Component.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include <vector>
#include <string>

class Component;
class ComponentTransform;
class ModuleScene;

class GameObject
{

public:
	GameObject();
	GameObject(GameObject* parent, const float4x4& transform, const char* name = "");
	GameObject(GameObject* parent, const char* name = "", const float3& translation = float3::zero, const Quat& rotation = Quat::identity, const float3& scale = float3::one);
	~GameObject();

	void Init(std::string new_name);
	void PreUpdate();
	void Update();
	void PostUpdate();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	Component* CreateComponent(Component::ComponentTypes type) const;
	Component* GetComponent(Component::ComponentTypes type) const;
	Component* GetComponentById(unsigned int component_id) const;
	const std::vector<Component*>& GetAllComponents() const;
	bool CheckComponent(Component::ComponentTypes type);

	const std::vector<GameObject*>& GetChildren() const;


	void SetParent(GameObject* new_parent);
	void SetActive(bool flag);
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	GameObject* GetChild(unsigned int child_id) const;

private:

public:
	static GameObject* focused_game_object;

private:

	std::string name;
	unsigned int uid = 0;
	bool is_active = false;

	ComponentTransform* transform = nullptr;
	std::vector<Component*> components;
	std::vector<GameObject*> childs;

	GameObject* parent = nullptr;
	ModuleScene* owner_scene = nullptr;
	


};