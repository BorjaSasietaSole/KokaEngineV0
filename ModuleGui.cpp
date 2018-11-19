#include "Globals.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"

#include "GL/glew.h"
#include "SDL.h"

ModuleGui::ModuleGui() : glsl_version("#version 130") {
	windowsGui.push_back(console = new WindowGuiConsole());
	windowsGui.push_back(config = new WindowGuiConfiguration());
	windowsGui.push_back(scene = new WindowGuiEditScene());
	windowsGui.push_back(about = new WindowGuiAboutOf());
}

ModuleGui::~ModuleGui() {
}

bool ModuleGui::Init() {
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup style
	ImGui::StyleColorsDark();

	return true;
}

update_status ModuleGui::PreUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	CreateDockSpace();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update() {

	update_status ret = UPDATE_CONTINUE;
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("File")) {

			if (ImGui::MenuItem("Exit")) {
				ImGui::EndMenu();
				ImGui::EndMainMenuBar();
				ImGui::End();
				ImGui::EndFrame();
				ret = UPDATE_ERROR;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window")) {

			if (ImGui::MenuItem("Scene", nullptr, scene->IsEnabled())) {
				scene->ToggleEnabled();
			}

			if (ImGui::MenuItem("Logs", nullptr, console->IsEnabled())) {
				console->ToggleEnabled();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About")) {
				about->ToggleEnabled();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	PrintDocks();

	return ret;
}

update_status ModuleGui::PostUpdate() {
	
	return UPDATE_CONTINUE;
}

bool ModuleGui::CleanUp() {
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleGui::HandleInputs(SDL_Event* event) const {
	ImGui_ImplSDL2_ProcessEvent(event);
}

void ModuleGui::RenderGUI() {
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ModuleGui::PrintDocks() {
	// Print docks like we do with module
	for (std::list<WindowGui*>::iterator it = windowsGui.begin(); it != windowsGui.end(); ++it)
		if ((*it)->IsEnabled()) {
			(*it)->Draw();
		}
}

void ModuleGui::CreateDockSpace()
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ (float)App->window->width, (float)App->window->height });
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	//TODO: change this to a simple define
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceId = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
}

bool ModuleGui::SceneFocused() const {
	return scene->IsFocused();
}

void ModuleGui::AddFPSCount(float fps) const {
	config->AddFps(fps);
}