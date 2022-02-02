#include "ComponentTransform.h"

ComponentTransform::ComponentTransform() {
	type = COMPONENT_TYPE::TRANSFORM;
	uid = App->scene->GenerateUID();

	pos = { 0.f, 0.f, 0.f };
	local_pos = { 0.f, 0.f, 0.f };

	rotation = Quat::identity;
	local_rotation = Quat::identity;

	scale = { 1.f, 1.f, 1.f };
	scale = { 1.f, 1.f, 1.f };

}

ComponentTransform::ComponentTransform(GameObject& newParent) {
	type = COMPONENT_TYPE::TRANSFORM;
	uid = App->scene->GenerateUID();

	pos = { 0.f, 0.f, 0.f };
	local_pos = { 0.f, 0.f, 0.f };

	rotation = Quat::identity;
	local_rotation = Quat::identity;

	scale = { 1.f, 1.f, 1.f };
	scale = { 1.f, 1.f, 1.f };

	parent = std::make_shared<GameObject>(newParent);
	newParent.AddComponent(*this);
}

void ComponentTransform::PreUpdate() {

}

void ComponentTransform::Update() {

}

void ComponentTransform::PostUpdate() {

}

void ComponentTransform::DrawInspectorPanel() {
	static float step = 0.01f;

	if(ImGui::TreeNode("Transform component")) {
		ImGui::Text("Pos: "); ImGui::SameLine();
		if (ImGui::DragFloat3("Px, Py, Pz", local_pos.ptr(), step, -inf, inf)) {}

		ImGui::Text("Rotation: "); ImGui::SameLine();
		if (ImGui::DragFloat3("Rx, Ry, Rz", local_rotation.ToEulerXYZ().ptr(), step, -inf, inf)) {}

		ImGui::Text("Scale: "); ImGui::SameLine();
		if (ImGui::DragFloat3("Sx, Sy, Sz", local_scale.ptr(), step, -inf, inf)) {}
		
		ImGui::TreePop();
	}
}

void ComponentTransform::UpdateGlobalValues() {

}