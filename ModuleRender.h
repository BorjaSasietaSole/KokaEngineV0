#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModulePrograms.h"
#include "ModuleDebugDraw.h"
#include "ComponentCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "debugdraw.h"
#include "Math/float4x4.h"

class ComponentCamera;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	void DrawGui();
	bool CleanUp();

	void InitSDL();
	void InitOpenGL() const;
	void SetViewMatrix(ComponentCamera* camera) const;
	void SetProjectionMatrix(ComponentCamera* camera) const;
	void DrawDebugData(ComponentCamera* camera) const;
	void GenerateBlockUniforms();

	bool getVsyncEnable() { return vsyncEnabled; }
	void* getContext() { return context; }
	bool getShowAxis() { return showAxis; }
	bool getShowGrid() { return showGrid; }

protected:

	bool vsyncEnabled = false;
	void* context = nullptr;
	unsigned ubo = 0u;
	bool showAxis = true;
	bool showGrid = true;

};
#endif