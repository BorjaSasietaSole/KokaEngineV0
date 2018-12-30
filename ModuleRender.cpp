#include "ModuleRender.h"

ModuleRender::ModuleRender() { }

// Destructor
ModuleRender::~ModuleRender() { }

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

	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update() {

	glBindFramebuffer(GL_FRAMEBUFFER, App->camera->getSceneCamera()->getFbo());
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetProjectionMatrix(App->camera->getSceneCamera());
	SetViewMatrix(App->camera->getSceneCamera());

	App->scene->Draw();

	DrawDebugData(App->camera->getSceneCamera());

	if (App->camera->getSelectedCamera() != nullptr) {
		glBindFramebuffer(GL_FRAMEBUFFER, App->camera->getSelectedCamera()->getFbo());
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SetProjectionMatrix(App->camera->getSelectedCamera());
		SetViewMatrix(App->camera->getSelectedCamera());

		// TODO: we will send the frustum to do the culling in the GOs
		App->scene->Draw();

		DrawDebugData(App->camera->getSelectedCamera());
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {

	App->options->RenderGUI();
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

void ModuleRender::DrawDebugData(ComponentCamera* camera) const {

	if (camera->debugDraw == false) return;

	if (showGrid) {
		dd::xzSquareGrid(-1000.0f, 1000.0f, 0.0f, 1.0f, math::float3(0.65f, 0.65f, 0.65f));
	}

	if (showAxis) {
		dd::axisTriad(math::float4x4::identity, 0.1f, 1.0f, 0, true);
	}

	App->debugDraw->Draw(camera, camera->getFbo(), App->window->height, App->window->width);
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
	unsigned uniformBlockIndexDefault = glGetUniformBlockIndex(App->programs->basicProgram, "Matrices");
	unsigned uniformBlockIndexTexture = glGetUniformBlockIndex(App->programs->textureProgram, "Matrices");

	glUniformBlockBinding(App->programs->basicProgram, uniformBlockIndexDefault, 0);
	glUniformBlockBinding(App->programs->textureProgram, uniformBlockIndexTexture, 0);

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

bool ModuleRender::CleanUp() {
	glDeleteBuffers(1, &ubo);
	return true;
}