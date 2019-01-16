#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePrograms.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"
#include "ModuleTime.h"
#include "ModuleScene.h"
#include "ModuleDebugDraw.h"
#include "ModuleLibrary.h"
#include "ModuleFileSystem.h"


using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(fileSystem = new ModuleFileSystem());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(scene = new ModuleScene());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(input = new ModuleInput());
	modules.push_back(programs = new ModulePrograms());
	modules.push_back(options = new ModuleGui());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(timers = new ModuleTime());
	modules.push_back(library = new ModuleLibrary());
}

Application::~Application()
{
	for (std::list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend(); ++it) {
		delete(*it);
		*it = nullptr;
	}
	modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it) {
		ret = (*it)->Init();
	}

	return ret;
}

update_status Application::Update()
{
	BROFILER_FRAME("MainLoop");
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	int ms_cap = 1000 / App->timers->maxFps;
	if (App->timers->frameTimer.Read() < ms_cap)
		SDL_Delay((Uint32) (ms_cap - App->timers->frameTimer.Read()));

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	Timer timerOff;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it) {
		ret = (*it)->CleanUp();
	}

	return ret;
}