#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Globals.h"

#include "WindowGui.h"
#include "WindowGuiAboutOf.h"
#include "WindowGuiConfiguration.h"
#include "WindowGuiConsole.h"
#include "WindowGuiEditScene.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <vector>

class WindowGui;
class WindowGuiConfiguration;
class WindowGuiConsole;
class WindowGuiEditScene;

class ModuleGui : public Module 
{
public:
	ModuleGui();
	~ModuleGui();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void AddFPSCount(float fps, float ms) const;
	void CreateDockSpace();
	void PrintDocks();
	void RenderGUI();
	bool SceneFocused() const;

	void HandleInputs(SDL_Event* event) const;
	// SDL events
	void ProcessInputEvent(SDL_Event* event) const;

	WindowGuiAboutOf* about = nullptr;
	WindowGuiConfiguration* config = nullptr;
	WindowGuiConsole* console = nullptr;
	WindowGuiEditScene* scene = nullptr;

private:
	const char* glsl_version;
	std::list<WindowGui*> windowsGui;
};
#endif __ModuleGui_H__