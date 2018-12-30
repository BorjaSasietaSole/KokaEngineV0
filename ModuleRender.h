#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "ComponentCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "debugdraw.h"
#include "Math/float4x4.h"

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp();

	void InitSDL();
	void InitOpenGL() const;
	void SetViewMatrix(ComponentCamera* camera) const;
	void SetProjectionMatrix(ComponentCamera* camera) const;
	void DrawDebugData(ComponentCamera* camera) const;
	void GenerateBlockUniforms();

	bool vsyncEnabled = false;
	void* getContext() { return context; }
	bool getShowAxis() { return showAxis; }
	bool getShowGrid() { return showGrid; }

protected:

	void* context = nullptr;
	unsigned ubo = 0u;
	bool showAxis = true;
	bool showGrid = true;

};
#endif