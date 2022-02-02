#pragma once

#include "Component.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include <list>
#include <vector>
#include <string>
#include <memory>
#include "ModuleScene.h"

class Component;
class ComponentTransform;

class GameObject
{

public:
	GameObject();
	~GameObject() = default;

	void Init();
	void PreUpdate();
	void Update();
	void PostUpdate();

	void AddComponent(Component& component);
	bool RemoveComponent(unsigned id);
	Component* GetComponentById(unsigned int component_id) const;
	Component* GetComponent(Component::COMPONENT_TYPE type) const;
	inline u32 GetUid() const { return uid; };
	inline std::string GetName() const { return name; };
	inline void SetName(const char* name) { this->name = name; };
	inline char* GetNameChar() { return &name[0]; };
	inline bool IsEnabled() { return is_active; };
	void SetEnabled(bool value);
	std::vector<Component*>& GetAllComponents() const;

	std::vector<GameObject*>& GetChildren() const;

	void SetParent(GameObject& new_parent);
	void AddChild(GameObject& child);
	void RemoveChild(GameObject& child);
	std::shared_ptr<GameObject> GetChild(u32 child_id) const;

	bool operator == (const GameObject& go) const { return uid == go.GetUid(); }
	bool operator != (const GameObject& go) const { return !operator==(go); }

	void DrawInHierarchy();
	void DrawComponentsInInspectorPanel() const;
private:

public:
	static GameObject* focused_game_object;

private:

	std::string name;
	u32 uid;
	bool is_active = true;

	ComponentTransform* transform = nullptr;
	std::list<Component*> components;
	std::list<std::shared_ptr<GameObject>> childs;

	std::shared_ptr<GameObject> parent = nullptr;
};