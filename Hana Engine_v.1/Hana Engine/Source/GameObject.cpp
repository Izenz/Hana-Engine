#include "GameObject.h"
#include "Component.h"
#include "Globals.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::PreUpdate()
{
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

void GameObject::AddComponent(Component::COMPONENT_TYPE type)
{
	/*
	switch (component->GetType())
		{
		case(Component::ComponentTypes::Transform):
		{
			if (!CheckComponent(Component::ComponentTypes::Transform))
			{
				components.push_back(component);
				transform = (ComponentTransform*)component;
				component->owner = this;
			}
			break;
		}
		case(Component::ComponentTypes::Mesh):
		{
			if (!CheckComponent(Component::ComponentTypes::Mesh))
			{
				components.push_back(component);
				component->owner = this;
				//Update bounding box
			}
			break;
		}
		case(Component::ComponentTypes::Material):
		{
			if (CheckComponent(Component::ComponentTypes::Mesh) && !CheckComponent(Component::ComponentTypes::Material))
			{
				components.push_back(component);
				component->owner = this;
			}

			break;
		}
		case(Component::ComponentTypes::Camera):
		{
			components.push_back((Component*)component);
			component->owner = this;
			break;
		}
	}*/
}


bool GameObject::RemoveComponent(unsigned id)
{
	return false;
}

Component* GameObject::GetComponent(Component::COMPONENT_TYPE type) const
{
	for (Component* component : components)
	{
		if (component->GetType() == type)
		{
			return component;
		}
	}
	return nullptr;
}

Component* GameObject::GetComponentById(unsigned int component_id) const
{
	for (Component* component : components)
	{
		if (component->GetId() == component_id)
		{
			return component;
		}
	}

	return nullptr;
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
	//parent = std::make_shared<GameObject>(new_parent);
	new_parent.AddChild(*this);
}

void GameObject::SetActive(bool flag)
{
	is_active = flag;
}

void GameObject::AddChild(GameObject& child)
{
	std::shared_ptr<GameObject> aux = std::make_shared<GameObject>(child);
	//Do check if child is already in vector childs
	childs.push_back(aux);
}

void GameObject::RemoveChild(GameObject& child)
{
	/*
	if (childs.size() > 0)
	{
		std::shared_ptr<GameObject> child = std::make_shared<GameObject>(child);
		childs.remove(child);
		//child.SetParent(root);
	}
	*/
}

std::shared_ptr<GameObject> GameObject::GetChild(unsigned int child_id) const
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


