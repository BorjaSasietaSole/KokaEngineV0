#include "ModuleTime.h"
#include "SDL.h"

ModuleTime::ModuleTime() { }

ModuleTime::~ModuleTime() { }

update_status ModuleTime::PreUpdate() {

	float currentFrame = (float) SDL_GetTicks();
	deltaTime = (currentFrame - lastFrame) * 0.001f;
	lastFrame = currentFrame;

	return UPDATE_CONTINUE;
}