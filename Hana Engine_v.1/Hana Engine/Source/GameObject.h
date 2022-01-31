#pragma once


#include "Component.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include <list>
#include <vector>
#include <string>
#include <memory>

class Component;
class ComponentTransform;
class ModuleScene;

class GameObject
{

public:
	GameObject();
	~GameObject();

	void Init();
	void PreUpdate();
	void Update();
	void PostUpdate();

	void AddComponent(Component::COMPONENT_TYPE type);		// Habra que pasar el tipo de component y instanciarlo dentro de la funcion
	bool RemoveComponent(unsigned id);		// Habra que pasar el uid y/o el tipo de componente.
	Component* GetComponentById(unsigned int component_id) const;
	Component* GetComponent(Component::COMPONENT_TYPE type) const;
	std::vector<Component*>& GetAllComponents() const;

	std::vector<GameObject*>& GetChildren() const;

	void SetParent(GameObject& new_parent);
	void SetActive(bool flag);
	void AddChild(GameObject& child);
	void RemoveChild(GameObject& child);
	std::shared_ptr<GameObject> GetChild(unsigned int child_id) const;

private:

public:
	static GameObject* focused_game_object;

private:

	std::string name;
	unsigned int uid = 0;
	bool is_active = true;

	ComponentTransform* transform = nullptr;
	std::list<Component*> components;
	std::list<std::shared_ptr<GameObject>> childs;

	std::shared_ptr<GameObject> parent = nullptr;
	std::shared_ptr<ModuleScene> owner_scene = nullptr;
};