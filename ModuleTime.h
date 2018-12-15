#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Timer.h"
#include "Globals.h"

enum class GameState { RUN, PAUSE, STOP };

class ModuleTime : public Module
{
public:
	ModuleTime();
	~ModuleTime();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void StartGameClock();
	void PauseGameClock(bool pause);
	void StopGameClock();
	void Step();
	
	float getGameDeltaTime() { return gameDeltaTime; }
	float getGameTime() { return gameTime; }
	float getRealDeltaTime() { return realDeltaTime; }
	float getRealTime() { return realTime; }

	int FPS = 0;
	bool nextFrame = false;
	unsigned maxFps = 144u;
	unsigned totalFrames = 0u;
	GameState gameState = GameState::STOP;

	Timer frameTimer;
	Timer fpsTimer;

	float gameTimeScale = 1.0f;

private:

	// Game Clock
	float gameTime = 0.0f;
	float gameDeltaTime = 0.0f;

	// RealTime Clock
	float realTime = 0.0f;
	float realDeltaTime = 0.0f;

	unsigned realFrameCount = 0u;
	unsigned frameCount = 0u;
};

#endif //__MODULETIME_H__