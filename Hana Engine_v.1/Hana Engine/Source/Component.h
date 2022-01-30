#pragma once
class GameObject;

class Component
{

public:
	enum class ComponentTypes
	{
		Camera,
		Mesh,
		Material,
		Transform,
		BoundingBox,
		Light,
		UNDEFINED
	};

	GameObject* owner = nullptr;

public:
	Component();
	Component(GameObject* new_owner, ComponentTypes type);
	virtual ~Component() = default;

	unsigned int GetId() const;
	virtual ComponentTypes GetType() const;

	const GameObject* Parent() const;

	virtual void Enable();
	virtual void Disable();

	virtual void PreUpdate();
	virtual void Update();
	virtual void PostUpdate();


	bool isEnabled() const;

protected:

	bool enabled = false;


private:
	unsigned int SetId();
	unsigned int id = 0;
	ComponentTypes type = ComponentTypes::UNDEFINED;
};