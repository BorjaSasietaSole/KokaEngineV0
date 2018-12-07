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
#include "ModuleSceneLoader.h"
#include "Timer.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(timers = new ModuleTime());
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(options = new ModuleGui());
	modules.push_back(programs = new ModulePrograms());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(scene = new ModuleScene());
	modules.push_back(sceneLoader = new ModuleSceneLoader());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
		RELEASE(*it);
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	this->timers->time.Start();
	
	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	if (App->timers->gameModeEnabled && !App->timers->counting) {
		App->timers->counting = true;
		timer.Start();
	}

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	int ms_cap = 1000 / App->timers->framerateCap;
	if (App->timers->time.Read() < ms_cap)
		SDL_Delay(ms_cap - App->timers->time.Read());

	options->AddFPSCount(1 / App->timers->deltaTime, App->timers->deltaTime * 1000);

	if (!App->timers->gameModeEnabled || App->timers->gamePaused) {
		App->options->AddFPSCount(0, 0);
	}
	else {
		App->options->AddFPSCount(1 / App->timers->gameDeltaTime, App->timers->gameDeltaTime * 1000);
	}

	if (!App->timers->gameModeEnabled && App->timers->counting) {
		timer.Stop();
		App->timers->counting = false;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	Timer timerOff;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	LOG("Cleaned modules in %d ms", timerOff.Stop());

	return ret;
}