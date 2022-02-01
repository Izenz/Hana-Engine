#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	uid = App->scene->GenerateUID();
	name = "Empty GameObject";
}

void GameObject::Init()
{
}

void GameObject::PreUpdate()
{
	if (!is_active)	return;

	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->PreUpdate();
	}

	if (childs.size() > 0)
	{
		for (auto child : childs)
		{
			if(child->is_active)
				child->PreUpdate();
		}
	}
}

void GameObject::Update()
{
	if (!is_active)	return;

	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}

	if (childs.size() > 0)
	{
		for (auto child : childs)
		{
			if (child->is_active)
				child->Update();
		}
	}
}

void GameObject::PostUpdate()
{
	if (!is_active)	return;

	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->PostUpdate();
	}

	if (childs.size() > 0)
	{
		for (auto child : childs)
		{
			if (child->is_active)
				child->PostUpdate();
		}
	}
}

void GameObject::AddComponent(Component& component)
{
	components.push_back(&component);
}


bool GameObject::RemoveComponent(unsigned id)
{
	return false;
}

Component& GameObject::GetComponent(Component::COMPONENT_TYPE type) const
{
	for (Component* component : components)
	{
		if (component->GetType() == type)
		{
			return *component;
		}
	}
}

Component& GameObject::GetComponentById(unsigned int component_id) const
{
	for (Component* component : components)
	{
		if (component->GetId() == component_id)
		{
			return *component;
		}
	}
}

std::vector<Component*>& GameObject::GetAllComponents() const
{
	// TODO: insert return statement here
	std::vector<Component*> result;
	return result;

}

std::vector<GameObject*>& GameObject::GetChildren() const
{
	std::vector<GameObject*> result;
	return result;

	// TODO: insert return statement here
}

void GameObject::SetParent(GameObject& new_parent)
{
	if (parent->GetUid() == new_parent.GetUid())	return;

	parent = std::make_shared<GameObject>(new_parent);
	new_parent.AddChild(*this);
}

void GameObject::SetActive(bool flag)
{
	is_active = flag;
}

void GameObject::AddChild(GameObject& child)
{
	for (auto child : childs) {
		if (child->GetUid() == this->uid)
			return;
	}

	std::shared_ptr<GameObject> aux = std::make_shared<GameObject>(child);
	childs.push_back(aux);
}

void GameObject::RemoveChild(GameObject& child)
{
	// TODO: Ask Carlos/Marc how the fuck we solve this.
	/*
	if (childs.size() > 0)
	{
		std::shared_ptr<GameObject> _child = std::make_shared<GameObject>(child);
		//childs.remove(_child); // <----ERROR: 
	}*/
}

std::shared_ptr<GameObject> GameObject::GetChild(u32 child_id) const
{
	if (childs.size() > 0)
	{
		for (auto child : childs)
		{
			if (child->uid == child_id)
			{
				return child;
			}
		}

	}

	return nullptr;
}


