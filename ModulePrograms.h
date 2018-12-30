#ifndef __ModulePrograms_h__
#define __ModulePrograms_h__

#include "Module.h"
#include "assert.h"
#include "GL/glew.h"

class ModulePrograms : public Module
{
public:
	ModulePrograms();
	~ModulePrograms();

	bool CleanUp() override;
	bool LoadPrograms();
	unsigned LoadProgram(const char* vertShaderPath, const char* fragShaderPath);

	unsigned basicProgram = 0u;
	unsigned textureProgram = 0u;
	unsigned vertShader = 0u;
	unsigned fragShader = 0u;

private:
	char* ReadShaderFile(const char* shaderPath);
	bool CompileShader(unsigned shaderAddress, const char* shaderContent);
	void CompileProgram(unsigned programAddress);
};
#endif