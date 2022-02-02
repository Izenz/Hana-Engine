#include "Component.h"
#include "ModuleScene.h"

Component::Component()
{
	uid = App->scene->GenerateUID();
	type = COMPONENT_TYPE::UNDEFINED;
}


Component::Component(GameObject& new_owner, COMPONENT_TYPE type)
{
	uid = App->scene->GenerateUID();
	this->type = type;

	parent = std::make_shared<GameObject>(new_owner);
	new_owner.AddComponent(*this);
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

void Component::DrawInspectorPanel()
{
}
