#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Application.h"
#include "SDL.h"
#include "GL/glew.h"

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

	/*glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char* logs = (char*)malloc(512);
		glGetProgramInfoLog(program, 512, NULL, logs);
		free(logs);
		glDeleteProgram(program);
	}*/

	return true;
}

update_status ModuleRenderExercise::Update() {
	RenderVBO(vbo, program);

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

}

bool ModuleRenderExercise::CleanUp() {
	glDeleteBuffers(1, &vbo);

	return true;
}