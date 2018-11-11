#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleLoader.h"

#include "./imgui/imgui.h"
#include "./imgui/imgui_impl_sdl.h"
#include "./imgui/imgui_impl_opengl3.h"

#include "SDL.h"
#include "GL/glew.h"

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
	float bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	unsigned program0;
	unsigned program1;

private:

	void RenderMesh(const ModuleLoader::Mesh& mesh, const ModuleLoader::Material& material,
		unsigned program, const math::float4x4& model,
		const math::float4x4& view, const math::float4x4& proj);
	void DrawReferenceDebug(unsigned program, const math::float4x4& model, const math::float4x4& view, const math::float4x4& proj);
	Frustum frustum;
};
