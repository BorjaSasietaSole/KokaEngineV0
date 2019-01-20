#ifndef __Application_H__
#define __Application_H__

#include<list>
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleGui;
class ModuleCamera;
class ModuleInput;
class ModuleScene;
class ModulePrograms;
class ModuleTime;
class ModuleScene;
class ModuleDebugDraw;
class ModuleFileSystem;
class ModuleLibrary;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModulePrograms* programs = nullptr;
	ModuleGui* options = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTime* timers = nullptr;
	ModuleScene* scene = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleFileSystem* fileSystem = nullptr;
	ModuleLibrary* library = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif