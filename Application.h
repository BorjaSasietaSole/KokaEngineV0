#ifndef __Application_H__
#define __Application_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Timer.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModulePrograms;
class ModuleModel;
class ModuleGui;
class ModuleCamera;
class ModuleTime;
class ModuleScene;
class ModuleSceneLoader;

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

	float lastTickTime = 0.0f;
	float auxTimer = 0.0f;
	int frameCounter = 0;
	int FPS = 0;

private:

	std::list<Module*> modules;
	Timer timer;

};

extern Application* App;

#endif // __Application_H__