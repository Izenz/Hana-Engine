#include "GameObject.h"
#include "Component.h"
#include "Globals.h"

GameObject::GameObject()
{

}

GameObject::GameObject(GameObject* parent, const float4x4& transform, const char* name)
{
}

GameObject::GameObject(GameObject* parent, const char* name, const float3& translation, const Quat& rotation, const float3& scale)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init(std::string new_name)
{
}

void GameObject::PreUpdate()
{
	std::vector<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->PreUpdate();
	}

	if (childs.size() > 0)
	{
		for (GameObject* child : childs)
		{
			if(child->is_active)
				child->PreUpdate();
		}
	}
}

void GameObject::Update()
{
	std::vector<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}

	if (childs.size() > 0)
	{
		for (GameObject* child : childs)
		{
			if (child->is_active)
				child->Update();
		}
	}
}

void GameObject::PostUpdate()
{
	std::vector<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it)->PostUpdate();
	}

	if (childs.size() > 0)
	{
		for (GameObject* child : childs)
		{
			if (child->is_active)
				child->PostUpdate();
		}
	}
}

void GameObject::AddComponent(Component* component)
{

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
	}
}


void GameObject::RemoveComponent(Component* component)
{
}

Component* GameObject::CreateComponent(Component::ComponentTypes type) const
{
	return nullptr;
}

Component* GameObject::GetComponent(Component::ComponentTypes type) const
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

const std::vector<Component*>& GameObject::GetAllComponents() const
{
	// TODO: insert return statement here
}

bool GameObject::CheckComponent(Component::ComponentTypes type)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->GetType() == type)
			return true;
	}
	return false;
}

const std::vector<GameObject*>& GameObject::GetChildren() const
{
	// TODO: insert return statement here
}

void GameObject::SetParent(GameObject* new_parent)
{
	if (new_parent == nullptr)
	{
		return;
	}
	parent = new_parent;
	parent->AddChild(this);
}

void GameObject::SetActive(bool flag)
{
	is_active = flag;
}

void GameObject::AddChild(GameObject* child)
{
	//Do check if child is already in vector childs
	if (GetChild(child->uid) != nullptr)
	{
		return;
	}
	childs.push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	if (childs.size() > 0)
	{
		std::vector<GameObject*>::const_iterator child;
		for (child = childs.begin(); child < childs.end(); ++child)
		{
			if ((*child)->uid == this->uid)
			{
				childs.erase(child);
			}
		}
	}

}

GameObject* GameObject::GetChild(unsigned int child_id) const
{
	if (childs.size() > 0)
	{
		for (GameObject* child : childs)
		{
			if (child->uid == child_id)
			{
				return child;
			}
		}

	}

	return nullptr;
}


