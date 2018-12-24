#ifndef __Application_H__
#define __Application_H__

#include<list>
#include "Module.h"
#include "Globals.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModulePrograms;
class ModuleGui;
class ModuleCamera;
class ModuleTime;
class ModuleScene;
class ModuleSceneLoader;
class ModuleResourceManager;
class ModuleDebugDraw;

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
	ModuleSceneLoader* sceneLoader = nullptr;
	ModuleResourceManager* resourceManager = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif