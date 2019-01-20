#include "Globals.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModulePrograms.h"
#include "ModuleDebugDraw.h"
#include "QuadTreeKoka.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "SDL.h"
#include "GL/glew.h"
#include "debugdraw.h"
#include "imgui_internal.h"
#include "Math/float4x4.h"

ModuleRender::ModuleRender() { }

// Destructor
ModuleRender::~ModuleRender() {
	CleanUp();
}

// Called before render is available
bool ModuleRender::Init() {
	LOG("Creating Renderer context");

	InitSDL();
	glewInit();
	InitOpenGL();

	if (vsyncEnabled && SDL_GL_SetSwapInterval(1) < 0) {
		LOG("Error: VSync couldn't be enabled \n %s", SDL_GetError());
	}

	App->programs->LoadPrograms();
	GenerateBlockUniforms();
	GenerateFallBackMaterial();

	return true;
}

update_status ModuleRender::PreUpdate() {
	BROFILER_CATEGORY("RenderPreUpdate()", Profiler::Color::AliceBlue);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update() {
	BROFILER_CATEGORY("RenderUpdate()", Profiler::Color::Aqua);
	glBindFramebuffer(GL_FRAMEBUFFER, App->camera->getSceneCamera()->fbo);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, App->camera->getSceneCamera()->wireFrame);
	SetProjectionMatrix(App->camera->getSceneCamera());
	SetViewMatrix(App->camera->getSceneCamera());

	if (frustCulling && App->camera->getSelectedCamera() != nullptr) {
		DrawMeshes(App->camera->getSelectedCamera());
	}
	else {
		DrawMeshes(App->camera->getSceneCamera());
	}

	DrawDebugData(App->camera->getSceneCamera());


	if (App->camera->getSelectedCamera() != nullptr) {
		glBindFramebuffer(GL_FRAMEBUFFER, App->camera->getSelectedCamera()->fbo);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, App->camera->getSelectedCamera()->wireFrame);
		SetProjectionMatrix(App->camera->getSelectedCamera());
		SetViewMatrix(App->camera->getSelectedCamera());
		DrawMeshes(App->camera->getSelectedCamera());
		DrawDebugData(App->camera->getSelectedCamera());
	}

	if (showQuad && App->camera->getQuadCamera() != nullptr) {
		glBindFramebuffer(GL_FRAMEBUFFER, App->camera->getQuadCamera()->fbo);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SetProjectionMatrix(App->camera->getQuadCamera());
		SetViewMatrix(App->camera->getQuadCamera());
		PrintQuadNode(App->scene->quadTree->root);
		App->debugDraw->Draw(App->camera->getQuadCamera(), App->camera->getQuadCamera()->fbo, App->camera->getQuadCamera()->screenWidth, App->camera->getQuadCamera()->screenHeight);
	}

	//So we exclude the rest of the quad rendered background of the color selected
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {
	BROFILER_CATEGORY("RenderPostUpdate()", Profiler::Color::Orchid);
	App->options->RenderGUI();
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

void ModuleRender::DrawDebugData(ComponentCamera* camera) const {
	BROFILER_CATEGORY("DrawDebugData()", Profiler::Color::Orange);
	if (camera->debugDraw == false) return;

	if (App->camera->getSelectedCamera() != nullptr) {
		dd::frustum((App->camera->getSelectedCamera()->frustum.ProjectionMatrix() * App->camera->getSelectedCamera()->frustum.ViewMatrix()).Inverted(), dd::colors::Crimson);
	}

	if (App->camera->getQuadCamera != nullptr) {
		dd::frustum((App->camera->getQuadCamera()->frustum.ProjectionMatrix() * App->camera->getQuadCamera()->frustum.ViewMatrix()).Inverted(), dd::colors::HotPink);
	}

	for (auto& cam : App->camera->getGameCameras()) {
		dd::frustum((cam->frustum.ProjectionMatrix() * cam->frustum.ViewMatrix()).Inverted(), dd::colors::IndianRed);
	}

	if (showQuad) {
		PrintQuadNode(App->scene->quadTree->root);
	}

	if (showRayCast) {
		PrintRayCast();
	}

	App->debugDraw->Draw(camera, camera->fbo, App->window->height, App->window->width);
}

void ModuleRender::SetViewMatrix(ComponentCamera* camera) const {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(math::float4x4), sizeof(math::float4x4), &camera->GetViewMatrix()[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void ModuleRender::SetProjectionMatrix(ComponentCamera* camera) const {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(math::float4x4), &camera->GetProjectionMatrix()[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void ModuleRender::GenerateBlockUniforms() {
	unsigned uniformBlockIndexDefault = glGetUniformBlockIndex(App->programs->colorProgram, "Matrices");
	unsigned uniformBlockIndexTexture = glGetUniformBlockIndex(App->programs->textureProgram, "Matrices");
	unsigned uniformBlockIndexBlinn = glGetUniformBlockIndex(App->programs->blinnProgram, "Matrices");

	glUniformBlockBinding(App->programs->colorProgram, uniformBlockIndexDefault, 0);
	glUniformBlockBinding(App->programs->textureProgram, uniformBlockIndexTexture, 0);
	glUniformBlockBinding(App->programs->blinnProgram, uniformBlockIndexBlinn, 0);


	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(math::float4x4), nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(math::float4x4));
}

void ModuleRender::InitSDL() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->window->window);
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}

void ModuleRender::InitOpenGL() const {
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_TEXTURE_2D);

	glClearDepth(1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glViewport(0, 0, App->window->width, App->window->height);
}

void ModuleRender::GenerateFallBackMaterial() {
	char fallbackImage[3] = { GLubyte(255), GLubyte(255), GLubyte(255) };

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &fallback);
	glBindTexture(GL_TEXTURE_2D, fallback);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, fallbackImage);
}

void ModuleRender::DrawMeshes(ComponentCamera* camera) {
	BROFILER_CATEGORY("DrawMeshes()", Profiler::Color::Gold);
	for (std::list<ComponentMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
		if ((*it)->getEnabled()) {
			if (frustCulling) {
				if (frustumCullingType == 1) {
					CullingFromQuadTree(camera, *it);
				}
				else {
					CullingFromFrustum(camera, *it);
				}
			}
			else {
				DrawWithoutCulling(*it);
			}
		}
	}
}

void ModuleRender::DrawWithoutCulling(ComponentMesh* mesh) const {
	if (mesh->goContainer->getTransform() != nullptr) {
		if (App->scene->getGoSelect() == mesh->goContainer) {
			dd::aabb(mesh->goContainer->ComputeBBox().minPoint, mesh->goContainer->ComputeBBox().maxPoint, math::float3(0.0f, 1.0f, 0.0f), true);
		}

		unsigned program = App->programs->blinnProgram;
		ComponentMaterial* compMat = (ComponentMaterial*)mesh->goContainer->GetComponent(ComponentType::MATERIAL);

		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &mesh->goContainer->getTransform()->GetGlobalTransform()[0][0]);

		mesh->Draw(program, compMat);

		glUseProgram(0);
	}
}

void ModuleRender::CullingFromFrustum(ComponentCamera* camera, ComponentMesh* mesh) const {
	if (!camera->frustum.Intersects(mesh->goContainer->ComputeBBox())) {
		dd::aabb(mesh->goContainer->ComputeBBox().minPoint, mesh->goContainer->ComputeBBox().maxPoint, math::float3(0.0f, 1.0f, 0.0f), true);
	}
	else {
		DrawWithoutCulling(mesh);
	}
}

void ModuleRender::CullingFromQuadTree(ComponentCamera* camera, ComponentMesh* mesh) {
	quadGOCollided.clear();
	App->scene->quadTree->CollectIntersections(quadGOCollided, camera->frustum);

	for (std::list<ComponentMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
		if (!(*it)->goContainer->getStaticGo() && (*it)->getMesh().verticesNumber > 0 && camera->frustum.Intersects((*it)->goContainer->ComputeBBox())) {
			quadGOCollided.push_back((*it)->goContainer);
		}
	}

	for (std::vector<GameObject*>::iterator it = quadGOCollided.begin(); it != quadGOCollided.end(); ++it) {
		if ((*it)->getEnabled()) {
			DrawWithoutCulling((ComponentMesh*)(*it)->GetComponent(ComponentType::MESH));
		}
	}
}

bool ModuleRender::CleanUp() {
	glDeleteBuffers(1, &ubo);
	return true;
}