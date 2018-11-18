#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init() override;

	// Called before quitting
	bool CleanUp() override;

	void WindowResized(unsigned width, unsigned height);

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	float screenRatio = SCREEN_WIDTH / SCREEN_HEIGHT;

	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
};

#endif // __ModuleWindow_H__