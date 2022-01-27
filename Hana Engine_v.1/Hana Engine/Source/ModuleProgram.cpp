#include "Globals.h"
#include "ModuleProgram.h"


ModuleProgram::ModuleProgram() {
	default_program = 0;
}

ModuleProgram::~ModuleProgram() {

}

bool ModuleProgram::Init()
{
	// Default program to paint objects by passing MVP matrices.
	//default_program = CreateShadersProgram("Shaders/vertex_shader.glsl", "Shaders/fragm_shader.glsl");
	return true;
}

bool ModuleProgram::CleanUp()
{
	// Delete programs
	for (unsigned program : programs) {
		glDeleteProgram(program);
	}
	// Delete shaders
	for (unsigned shader : shaders) {
		glDeleteShader(shader);
	}

	return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name) const {
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");

	if (file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	
	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* shader_data) {
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_data, 0);
	glCompileShader(shader_id);

	GLint compilation = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation);
	if (compilation == GL_FALSE) {
		GLint logSize = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logSize);
		if (logSize > 0) {
			GLsizei written = 0;
			char* logs = (char*)malloc(logSize);
			glGetShaderInfoLog(shader_id, logSize, &written, logs);
			LOG("Compilation info: %s", logs);
			free(logs);
			glDeleteShader(shader_id);
		}
	}

	return shader_id;
}

/*
	This function recieves two paths: one for vertex shader and one for fragment shader and returns the id of the program it
	creates with them.
*/
unsigned ModuleProgram::CreateShadersProgram(const char* path_to_vert, const char* path_to_fragm) {
	
	char* vsData = LoadShaderSource(path_to_vert);
	unsigned vert_shader = CompileShader(GL_VERTEX_SHADER, vsData);
	shaders.push_back(vert_shader);

	char* fsData = LoadShaderSource(path_to_fragm);
	unsigned fragm_shader = CompileShader(GL_FRAGMENT_SHADER, fsData);
	shaders.push_back(fragm_shader);

	unsigned int program = glCreateProgram();
	programs.push_back(program);

	glAttachShader(program, vert_shader);
	glAttachShader(program, fragm_shader);
	glLinkProgram(program);

	return program;
}
