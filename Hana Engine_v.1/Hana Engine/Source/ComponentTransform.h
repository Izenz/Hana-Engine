#pragma once


#include "Application.h"
#include "ModuleScene.h"
#include "Component.h"
#include "GameObject.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform();
	ComponentTransform(GameObject& newParent);
	~ComponentTransform() = default;

	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;

	void DrawInspectorPanel() override;

	inline const float3& GetPos() const { return pos; };
	inline const float3& GetLocalPos() const { return local_pos; };
	inline void SetPos(const float3& newPos) { pos = newPos; };
	inline void SetLocalPos(const float3& newLocalPos) { local_pos = newLocalPos; };
	
	inline const Quat& GetRotation() const { return rotation; };
	inline const float3& GetRotationEuler() const { return rotation.ToEulerXYZ(); };
	inline const Quat& GetLocalRotation() const { return local_rotation; };
	inline const float3& GetLocalRotationEuler() const { return local_rotation.ToEulerXYZ(); };
	inline void SetRotation(const Quat& newRotation) { rotation = newRotation; };
	inline void SetLocalRotation(const Quat& newLocalRotation) { local_rotation = newLocalRotation; };

	inline const float3& GetScale() const { return scale; };
	inline const float3& GetLocalScale() const { return local_scale; };
	inline void SetScale(const float3& newScale) { pos = newScale; };
	inline void SetLocalScale(const float3& newLocalScale) { local_pos = newLocalScale; };
private:
	void UpdateGlobalValues();

private:
	float3 pos;
	float3 local_pos;

	Quat rotation;
	Quat local_rotation;

	float3 scale;
	float3 local_scale;
};

