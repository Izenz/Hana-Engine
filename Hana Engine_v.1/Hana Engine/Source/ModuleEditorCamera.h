#pragma once

#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "SDL.h"
#include "SDL/include/SDL_scancode.h"
#include <cmath>

#include "Application.h"
#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"
#include "ModuleScene.h"


struct Plan {
	float3	normal = {0.f, 1.f, 0.f};
	// Distance from origin to nearest point in the plan
	float	distance = 0.f;

	float getSignedDistanceToPlan(const float3& point) const {
		return normal.Dot(point) - distance;
	}
};

struct AABB {
	float3	center{	0.f, 1.f, 0.f };
	float3	extents{ 0.f, 1.f, 0.f };

	AABB(const float3& _center, float li, float lj, float lk) {
		center = _center;
		extents.x = li;
		extents.y = lj;
		extents.z = lk;
	}

	bool isOnOrForwardPlan(const math::Plane& plane) const
	{
		// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		const float r = extents.x * std::abs(plane.normal.x) +
			extents.y * std::abs(plane.normal.y) + extents.z * std::abs(plane.normal.z);

		return -r <= plane.SignedDistance(center);
	}
	/*
	bool IsOnFrustum(const Frustum& cam, const Transform& transform) const final {
		const float3 globalCenter{ float4x4::identity * float4(center, 1.f) };
		const float3 right = transform.GetRight() * extents.x;
		const float3 up = transform.GetUp() * extents.y;
		const float3 forward = transform.GetForward() * extents.z;

		const float new_li = std::abs(float3(1.f, 0.f, 0.f).Dot(right)) +
			std::abs(float3(1.f, 0.f, 0.f).Dot(up)) +
			std::abs(float3(1.f, 0.f, 0.f).Dot(forward));
		const float new_lj = std::abs(float3(0.f, 1.f, 0.f).Dot(right)) +
			std::abs(float3(0.f, 1.f, 0.f).Dot(up)) +
			std::abs(float3(0.f, 1.f, 0.f).Dot(forward));
		const float new_lk = std::abs(float3(0.f, 0.f, 1.f).Dot(right)) +
			std::abs(float3(0.f, 0.f, 1.f).Dot(up)) +
			std::abs(float3(0.f, 0.f, 1.f).Dot(forward));

		const AABB globalAABB(globalCenter, new_li, new_lj, new_lk);

		return (globalAABB.isOnOrForwardPlan(cam.LeftPlane()) &&
			globalAABB.isOnOrForwardPlan(cam.RightPlane()) &&
			globalAABB.isOnOrForwardPlan(cam.TopPlane()) &&
			globalAABB.isOnOrForwardPlan(cam.BottomPlane()) &&
			globalAABB.isOnOrForwardPlan(cam.NearPlane()) &&
			globalAABB.isOnOrForwardPlan(cam.FarPlane()));
	}*/
};

class ModuleEditorCamera : public Module {

public:
	bool Init();

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	float4x4 GetProjMatrix() const;
	float4x4 GetViewMatrix() const;

	// Camera control
	void MoveForward();
	void MoveLeft();
	void MoveRight();
	void MoveBackwards();
	void MoveUp();
	void MoveDown();

	void CameraLookAt(const float3& newTargetPos);
	void FocusObject();	// TODO

	// Setters
	void SetAspectRatio(unsigned width, unsigned height);

private:
	void InitFrustum();
	void HandleCameraMovement();
	void HandleCameraRotation();

	void Orbit();
	void RotateCamera();

	Frustum frustum;

	const float movSpeed = 0.02f;
	const float rotationSpeed = 0.002f;
	const float orbitSpeed = 0.02f;

	math::Quat azimuth_angle = math::Quat::identity;
	math::Quat polar_angle = math::Quat::identity;

	float3 pitch, yaw;	// up and front respectively
};

