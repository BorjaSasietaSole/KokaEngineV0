#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Timer.h"

class ModuleTime : public Module
{
public:
	ModuleTime();
	~ModuleTime();

	update_status PreUpdate() override;
	
	float getDeltaTime() { return deltaTime; }
	float getLastFrame() { return lastFrame; }

	Timer time;
	bool gamePaused = false;
	bool gameModeEnabled = false;
	int	framerateCap = 60;
	int gameframerateCap = 60;
	bool counting = false;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float gameDeltaTime = 0.0f;
	float gameLastFrame = 0.0f;	
};

#endif //__MODULETIME_H__