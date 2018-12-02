#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "GL/glew.h"
#include "IL/ilut.h"

struct Texture {
	int id = 0;
	int width = 0;
	int height = 0;
	Texture(int id, int width, int height) : id(id), width(width), height(height) { }
};

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init() override;
	Texture* Load(const char* path);
	void DrawGui();

	int pixelDepth = 0;
	int height = 0;
	int format = 0;
	int width = 0;

	bool anisotropic_filter = false;
	int filterType = GL_LINEAR;
	bool mipmaping = false;
	int wrapMode = 0;
	ILuint imageId = 0u;
};

#endif //__MODULETEXTURES_H__