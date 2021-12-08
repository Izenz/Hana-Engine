#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	char* LoadShaderSource(const char* shader_file_name) const;
	unsigned CompileShader(unsigned type, const char* shader_data);

	bool Init();
	bool CleanUp();
	inline unsigned GetCurrentProgram() const { return program; };

private:
	unsigned shader_id, program;
};