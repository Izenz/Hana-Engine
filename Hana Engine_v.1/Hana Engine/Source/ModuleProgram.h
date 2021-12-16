#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	unsigned CreateShadersProgram(const char* path_to_vert, const char* path_to_fragm);

	bool Init();
	bool CleanUp();
	inline unsigned GetDefaultProgram() const { return default_program; };

private:
	char* LoadShaderSource(const char* shader_file_name) const;
	unsigned CompileShader(unsigned type, const char* shader_data);
	unsigned default_program;

	std::vector<unsigned> programs;
	std::vector<unsigned> shaders;
};