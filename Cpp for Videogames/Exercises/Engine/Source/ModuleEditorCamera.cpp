#include "ModuleEditorCamera.h"
#include "Globals.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"


bool ModuleEditorCamera::Init() {

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);

	frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);

	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed();

	// Send frustum PROJECTION matrix to OpenGL

	//Direct Mode:
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*projectionGL.v);

	return true;
}

update_status ModuleEditorCamera::PreUpdate() {

	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {

	float3 pos(0.0f, 10.0f, 5.0f);
	frustum.SetPos(pos);

	float3x3 rotationMatrix = float3x3::FromEulerXYZ(DegToRad(0), DegToRad(0), DegToRad(-45));

	frustum.SetFront(rotationMatrix.WorldX());
	frustum.SetUp(rotationMatrix.WorldY());

	// Send the frustum VIEW matrix to openGL

	//Direct mode:
	/*
	float4x4 viewGL = float4x4(frustum.ViewMatrix()).Transposed();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*viewGL.v);
	*/
	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

float4x4 ModuleEditorCamera::GetProjMatrix() {
	return frustum.ProjectionMatrix().Transposed();
}

float4x4 ModuleEditorCamera::GetViewMatrix() {
	return float4x4(frustum.ViewMatrix()).Transposed();
}