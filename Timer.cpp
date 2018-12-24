#include "Timer.h"
#include "SDL.h"

///Miliseconds timer
void Timer::Start() {
	startTicks = SDL_GetTicks();
	running = true;
}

void Timer::Stop() {
	running = false;
}

float Timer::Read() {
	if (running)
		time = ((float) SDL_GetTicks() - startTicks + skippedTime);
	return time;
}

float Timer::ReadSeconds() {
	if (running)
		time = (SDL_GetTicks() - startTicks + skippedTime) / 1000.0f;
	return time;
}

void Timer::Pause() {
	skippedTime += (SDL_GetTicks() - startTicks);
	running = false;
}

void Timer::Reset() {
	startTicks = SDL_GetTicks();
	skippedTime = 0;
}