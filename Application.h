#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderTriangle;
class ModulePrograms;
class ModuleLoader;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleRenderTriangle* triangle = nullptr;
	ModuleLoader* models = nullptr;
	ModulePrograms* programs = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
