#pragma once
#include "Module.h"
#include "Globals.h"

#include "ModuleLoader.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

	void* context;

private:

	void RenderMesh(const ModuleLoader::Mesh& mesh, const ModuleLoader::Material& material,
		unsigned program, const math::float4x4& model,
		const math::float4x4& view, const math::float4x4& proj);

	Frustum frustum;
};
