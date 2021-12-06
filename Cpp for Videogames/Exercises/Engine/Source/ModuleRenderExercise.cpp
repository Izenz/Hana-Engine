#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleEditorCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"

bool ModuleRenderExercise::Init() {
	//GLfloat vertices[] = { -1, -1, 0,	1, -1, 0,	0, 1, 0 };

	GLfloat wColors[] = {	-1, -1, 0,		1, 0, 0,
							1, -1, 0,		0, 1, 0,
							0, 1, 0,		0, 0, 1	};
	GLint success;

	// Create VBO and load triangle within it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wColors), wColors, GL_STATIC_DRAW);

	// At Init method creates a program with Hello World vertex and fragment shaders
	char* vsData = App->program->LoadShaderSource("vertex_shader.glsl");
	unsigned vert_shader = App->program->CompileShader(GL_VERTEX_SHADER, vsData);

	char* fsData = App->program->LoadShaderSource("fragm_shader.glsl");
	unsigned fragm_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, fsData);

	program = glCreateProgram();

	glAttachShader(program, vert_shader);
	glAttachShader(program, fragm_shader);
	glLinkProgram(program);

	// Frustum setup
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT));

	float3 pos(2.0f, 4.0f, 6.0f);
	float3 targetDir = (float3::zero - pos).Normalized();

	frustum.SetPos(pos);
	frustum.SetFront(targetDir);
	frustum.SetUp(float3::unitY);
	
	return true;
}

update_status ModuleRenderExercise::Update() {

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-100, 100, 0.0f, 1.0f, dd::colors::Gray);

	//RenderVBO(vbo, program);
	//RenderTriangle();
	LoadBakerHouse();

	return UPDATE_CONTINUE;
}

void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program) {


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// https://computingonplains.wordpress.com/opengl-shaders/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glUseProgram(program);

	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(0);

}

void ModuleRenderExercise::RenderTriangle() {

	// Get matrices
	projection = App->editor->cam->GetProjMatrix();
	view = App->editor->cam->GetViewMatrix();
	model = float4x4::identity;

	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);

	//Bind buffer and vertex attributes

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(0);

	App->debugDraw->Draw(view, projection, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void ModuleRenderExercise::LoadBakerHouse() {
	
	projection = App->editor->cam->GetProjMatrix();
	view = App->editor->cam->GetViewMatrix();

	if(!houseModel.IsLoaded())
		houseModel.Load("Models/BakerHouse.fbx", "Models/Baker_house.png");
	houseModel.Draw();

	App->debugDraw->Draw(view, projection, SCREEN_WIDTH, SCREEN_HEIGHT);
}

update_status ModuleRenderExercise::PostUpdate() {

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp() {
	glDeleteBuffers(1, &vbo);

	return true;
}