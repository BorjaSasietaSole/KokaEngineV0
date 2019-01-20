#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Globals.h"
#include "Module.h"

#include "WindowGui.h"
#include "WindowGuiAboutOf.h"
#include "WindowGuiConfiguration.h"
#include "WindowGuiConsole.h"
#include "WindowGuiEditScene.h"
#include "WindowGuiHierarchy.h"
#include "WindowGuiInspector.h"
#include "WindowGuiTime.h"
#include "WindowGuiCamera.h"
#include "WindowGuiAssets.h"
#include "WindowGuiLight.h"
#include "WindowGuiQuad.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <vector>

class WindowGui;
class WindowGuiConfiguration;
class WindowGuiConsole;
class WindowGuiEditScene;
class WindowGuiHierarchy;
class WindowGuiInspector;
class WindowGuiTime;
class WindowGuiCamera;
class WindowGuiAssets;
class WindowGuiLight;
class WindowGuiQuad;

class ModuleGui : public Module 
{
public:
	ModuleGui();
	~ModuleGui();

	bool Init();
	update_status PreUpdate() override;
	update_status Update() override;

	void AddFPSCount(float fps, float ms) const;
	void AddGameFPSCount(float fps, float ms) const;
	void CreateDockSpace();
	void PrintDocks();
	void RenderGUI() const;
	bool SceneFocused() const;

	// SDL events
	void ProcessInputEvent(SDL_Event* event) const;

	WindowGuiAboutOf* about = nullptr;
	WindowGuiConfiguration* config = nullptr;
	WindowGuiConsole* console = nullptr;
	WindowGuiEditScene* scene = nullptr;
	WindowGuiHierarchy* hierarchy = nullptr;
	WindowGuiInspector* inspector = nullptr;
	WindowGuiTime* time = nullptr;
	WindowGuiCamera* camera = nullptr;
	WindowGuiAssets* assets = nullptr;
	WindowGuiLight* light = nullptr;
	WindowGuiQuad* quad = nullptr;

	const std::string FilePickerID = "###FilePicker";

private:
	const char* glsl_version;
	std::list<WindowGui*> windowsGui;
};
#endif __ModuleGui_H__