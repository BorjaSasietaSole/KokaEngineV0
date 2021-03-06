#include "ModuleTime.h"
#include "Application.h"
#include "ModuleGui.h"

#include "Brofiler.h"

ModuleTime::ModuleTime() { }

ModuleTime::~ModuleTime() { }

bool ModuleTime::Init() {
	gameDeltaTime = 0.0f;
	frameTimer.Start();
	fpsTimer.Start();
	return true;
}

update_status ModuleTime::Update() {
	BROFILER_CATEGORY("TimeUpdate()", Profiler::Color::LightPink);
	++frameCount;
	++realFrameCount;

	// Time update
	realDeltaTime = frameTimer.ReadSeconds();
	realTime += realDeltaTime;

	App->options->AddFPSCount(FPS, realDeltaTime * 1000.0f);

	if (gameState == GameState::RUN) {
		App->options->AddGameFPSCount(FPS, gameDeltaTime * gameTimeScale * 1000.0f);
		++totalFrames;
		gameDeltaTime = frameTimer.ReadSeconds();
		gameTime += gameDeltaTime * gameTimeScale;
	}
	frameTimer.Reset();

	// Frames per second
	if (fpsTimer.ReadSeconds() >= 1.0f) {
		FPS = (float) frameCount;
		frameCount = 0u;
		fpsTimer.Reset();
	}
	return UPDATE_CONTINUE;
}

bool ModuleTime::CleanUp() {
	frameTimer.Stop();
	fpsTimer.Stop();
	return true;
}

void ModuleTime::StartGameClock() {
	gameState = GameState::RUN;
}

void ModuleTime::PauseGameClock(bool pause) {
	if (pause) {
		gameState = GameState::PAUSE;
		gameDeltaTime = 0.0f;
	}
	else {
		gameState = GameState::RUN;
	}
}

void ModuleTime::StopGameClock() {
	gameState = GameState::STOP;
	gameDeltaTime = 0.0f;
	gameTime = 0.0f;
	totalFrames = 0u;
}

void ModuleTime::Step() {
	nextFrame = true;
}

void ModuleTime::setFrameCount(int count)
{
	frameCount = count;
}