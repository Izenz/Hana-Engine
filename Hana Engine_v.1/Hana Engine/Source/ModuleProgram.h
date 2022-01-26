#pragma once
#include "Globals.h"
#include <vector>
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

#include "Module.h"
#include "Console.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	bool CleanUp() override;

	inline unsigned GetDefaultProgram() const { return default_program; };
	unsigned CreateShadersProgram(const char* path_to_vert, const char* path_to_fragm);

private:
	char* LoadShaderSource(const char* shader_file_name) const;
	unsigned CompileShader(unsigned type, const char* shader_data);
	unsigned default_program;

	std::vector<unsigned> programs;
	std::vector<unsigned> shaders;
};