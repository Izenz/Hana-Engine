#include "Component.h"
#include "Globals.h"
#include "imgui.h"
#include "stdio.h"


Component::Component()
{
	this->id = SetId();
}


Component::Component(GameObject* new_owner, ComponentTypes type)
{
	this->id = SetId();
	this->type = type;
	this->owner = new_owner;
}


const GameObject* Component::Parent() const
{
	return owner;
}



void Component::Enable()
{
	enabled = true;
}

void Component::Disable()
{
	enabled = false;
}



unsigned int Component::SetId()
{
	return id++;
}


bool Component::isEnabled() const
{
	return enabled;
}

unsigned int Component::GetId() const
{
	return id;
}

Component::ComponentTypes Component::GetType() const
{
	return type;
}
