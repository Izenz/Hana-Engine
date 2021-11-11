#include "Globals.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleProgram::ModuleProgram() {

}

ModuleProgram::~ModuleProgram() {

}

bool ModuleProgram::Init()
{
	/*
	char* vert_shader = LoadShaderSource("shaderfilename");
	CompileShader(GL_VERTEX_SHADER, vert_shader);

	char* frag_shader = LoadShaderSource("shaderfilename");
	CompileShader(GL_FRAGMENT_SHADER, frag_shader);
	*/
	return true;
}

bool ModuleProgram::CleanUp()
{
	LOG("Dummy CleanUp!");
	return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name) {
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