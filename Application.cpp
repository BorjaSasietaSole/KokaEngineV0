#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePrograms.h"
#include "ModuleRenderTriangle.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"
#include "ModuleTime.h"
#include "Timer.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(timer = new ModuleTime());
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(programs = new ModulePrograms());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(options = new ModuleGui());
	modules.push_back(models = new ModuleLoader());
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

	Timer timer;
	timer.Start();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	LOG("Modules initialized in %d ms", timer.Stop());

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	

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