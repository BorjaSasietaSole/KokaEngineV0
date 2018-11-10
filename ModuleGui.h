#pragma once
#include "Module.h"
#include "Application.h"
#include "Globals.h"
#include "./imgui/imgui.h"
#include "./imgui/imgui_impl_sdl.h"
#include "./imgui/imgui_impl_opengl3.h"
#include <SDL.h>

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
private:

	SDL_Window* window;
	const char* glsl_version;
	SDL_GLContext gl_context;

	ImGuiIO io;

	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;
};