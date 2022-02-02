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
	// TODO: Improve by checking if the type of component can coexist with its own kind.
	Component* comp = this->GetComponent(component.GetType());
	if (comp == NULL) {
		components.push_back(&component);
	}
	else {
		LOG("ERROR: Component not added - This GameObject already has that type of component.");
	}	
}


bool GameObject::RemoveComponent(unsigned id)
{
	// TODO: Remove without crashing
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
	return NULL;
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

	return NULL;
}

void GameObject::SetEnabled(bool value)
{
	is_active = value;

	if (childs.size() <= 0)		return;
	for (auto child : childs)
		child->SetEnabled(value);
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
	if (parent != NULL)
		if (parent->GetUid() == new_parent.GetUid())
			return;

	parent = std::make_shared<GameObject>(new_parent);
	new_parent.AddChild(*this);
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

void GameObject::DrawInHierarchy()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4 textColor = is_active ? ImVec4(1.f, 1.f, 1.f, 1.00f) : ImVec4(0.2f, 0.2f, 0.2f, 1.00f);

	if (childs.size() <= 0) {
		ImGui::PushStyleColor(ImGuiCol_Text, textColor);
		if (ImGui::Selectable(&name[0]))
			App->scene->SetSelected(this);
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Text, textColor);
		if (ImGui::TreeNode(&name[0])) {
			if(ImGui::IsItemClicked())	App->scene->SetSelected(this);

			for (auto child : childs) {
				child->DrawInHierarchy();
			}

			ImGui::TreePop();
		}
	}

	ImGui::PopStyleColor();
}

void GameObject::DrawComponentsInInspectorPanel() const {
	if (components.size() < 1) {
		ImGui::Separator();
		return;
	}

	for (Component* comp : components) {
		comp->DrawInspectorPanel();
		ImGui::Separator();
	}
}

