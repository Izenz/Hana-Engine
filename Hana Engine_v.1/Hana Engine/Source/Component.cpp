#include "Component.h"

Component::Component()
{
	//this->id = SetId();
}


Component::Component(GameObject& new_owner, COMPONENT_TYPE type)
{
	//this->id = SetId();
	this->type = type;
	// Call owner method AddComponent
	// this->owner = new_owner;
}

Component::COMPONENT_TYPE Component::GetType() const
{
	return type;
}

void Component::PreUpdate()
{
}

void Component::Update()
{
}

void Component::PostUpdate()
{
}
