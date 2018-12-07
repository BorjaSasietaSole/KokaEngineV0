#include "ModuleTime.h"
#include "SDL.h"

ModuleTime::ModuleTime() { }

ModuleTime::~ModuleTime() { }

update_status ModuleTime::PreUpdate() {

	deltaTime = (float)time.Read() / 1000.0f;

	if (!gameModeEnabled || gamePaused) {
		gameDeltaTime = 0;
	}
	else {
		gameDeltaTime = deltaTime / ((float)gameframerateCap / (float)framerateCap);
	}

	time.Start();

	return UPDATE_CONTINUE;
}