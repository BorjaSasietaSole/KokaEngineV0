#pragma once
#include<list>
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	unsigned Load(const char* path, bool mipmaps);
	void ReloadTexture(const char* newPath, unsigned texture);
	void Unload(unsigned id);
	void SetNewParameter(const char* newPath, unsigned texture, unsigned newTextFilter, unsigned newResizeMethod, unsigned newWrapMethod, unsigned newClampMethod);
	void SwitchMipMaps(const char* newPath, unsigned texture, bool state);

	char* imgFormat;
	unsigned textFilter = 0;
	unsigned resizeMethod = 0;
	unsigned wrapMethod = 0;
	unsigned clampMethod = 0;
	bool generateMipMaps = false;
};