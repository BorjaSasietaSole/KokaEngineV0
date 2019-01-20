#include "Globals.h"

#include "ModuleTime.h"
#include "ModuleScene.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"

#include "ImGuizmo/ImGuizmo.h"

#include "GL/glew.h"
#include "SDL.h"

ModuleGui::ModuleGui() : glsl_version("#version 130") {
	windowsGui.push_back(console = new WindowGuiConsole());
	windowsGui.push_back(config = new WindowGuiConfiguration());
	windowsGui.push_back(scene = new WindowGuiEditScene());
	windowsGui.push_back(about = new WindowGuiAboutOf());
	windowsGui.push_back(hierarchy = new WindowGuiHierarchy());
	windowsGui.push_back(inspector = new WindowGuiInspector());
	windowsGui.push_back(time = new WindowGuiTime());
	windowsGui.push_back(camera = new WindowGuiCamera());
	windowsGui.push_back(light = new WindowGuiLight());
	windowsGui.push_back(assets = new WindowGuiAssets());
	windowsGui.push_back(quad = new WindowGuiQuad());
}

ModuleGui::~ModuleGui() {
	for (auto& window : windowsGui) {
		delete window;
		window = nullptr;
	}
	windowsGui.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

bool ModuleGui::Init() {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup style
	ImGui::StyleColorsDark();

	return true;
}

update_status ModuleGui::PreUpdate() {
	BROFILER_CATEGORY("EditorPreUpdate()", Profiler::Color::Azure);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	ImGuizmo::BeginFrame();

	// Style
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.3f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	struct ImVec3 { float x, y, z; ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) { x = _x; y = _y; z = _z; } };

	static ImVec3 color_for_text = ImVec3(236.f / 255.f, 240.f / 255.f, 241.f / 255.f);
	static ImVec3 color_for_head = ImVec3(41.f / 255.f, 128.f / 255.f, 185.f / 255.f);
	static ImVec3 color_for_area = ImVec3(57.f / 255.f, 79.f / 255.f, 105.f / 255.f);
	static ImVec3 color_for_body = ImVec3(44.f / 255.f, 62.f / 255.f, 80.f / 255.f);
	static ImVec3 color_for_pops = ImVec3(33.f / 255.f, 46.f / 255.f, 60.f / 255.f);

	style.Colors[ImGuiCol_Text] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.95f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.58f);
	style.Colors[ImGuiCol_Border] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.21f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.15f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.73f);
	
	CreateDockSpace();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update() {
	BROFILER_CATEGORY("EditorUpdate()", Profiler::Color::Azure);
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("App")) {

			if (ImGui::MenuItem("New scene")) {
				App->scene->ClearScene();
			}

			if (ImGui::MenuItem("Save scene")) {
				App->scene->SaveScene();
			}


			if (ImGui::MenuItem("Load scene")) {
				App->scene->LoadScene();
			}

			if (ImGui::MenuItem("Exit")) {
				ImGui::EndMenu();
				ImGui::EndMainMenuBar();
				ImGui::End();
				ImGui::EndFrame();
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Elements")) {

			if (ImGui::BeginMenu("Select camera in")) {
				if (App->camera->getGameCameras().size() == 0) {
					ImGui::Text("No game cameras available");
				}
				else {
					for (auto& camera : App->camera->getGameCameras()) {
						if (ImGui::MenuItem(camera->goContainer->getName().c_str(), NULL, App->camera->getSelectedCamera() == camera)) {
							App->camera->setSelectedCamera(camera);
						}
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Add new")) {
				if (ImGui::MenuItem("Empty GameObject")) {
					new GameObject(DEFAULT_GO_NAME, math::float4x4().identity, nullptr);
				}
				if (ImGui::MenuItem("Sphere")) {
					GameObject* sphereGO = new GameObject("Sphere", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(sphereGO, GeometryType::SPHERE);
					App->scene->setGoSelected(sphereGO);
				}
				if (ImGui::MenuItem("Torus")) {
					GameObject* torusGO = new GameObject("Torus", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(torusGO, GeometryType::TORUS);
					App->scene->setGoSelected(torusGO);
				}
				if (ImGui::MenuItem("Cube")) {
					GameObject* cubeGO = new GameObject("Cube", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(cubeGO, GeometryType::CUBE);
					App->scene->setGoSelected(cubeGO);
				}
				if (ImGui::MenuItem("Plane")) {
					GameObject* planeGO = new GameObject("Plane", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(planeGO, GeometryType::PLANE);
					App->scene->setGoSelected(planeGO);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window")) {

			if (ImGui::MenuItem("Scene", NULL, scene->IsEnabled())) {
				scene->ToggleEnabled();
			}

			if (ImGui::MenuItem("Game", NULL, camera->IsEnabled())) {
				camera->ToggleEnabled();
			}

			if (ImGui::MenuItem("Hierarchy", NULL, hierarchy->IsEnabled())) {
				hierarchy->ToggleEnabled();
			}

			if (ImGui::MenuItem("Lights", NULL, light->IsEnabled())) {
				light->ToggleEnabled();
			}

			if (ImGui::MenuItem("Assets", NULL, assets->IsEnabled())) {
				assets->ToggleEnabled();
			}

			if (ImGui::MenuItem("Time", NULL, time->IsEnabled())) {
				time->ToggleEnabled();
			}

			if (ImGui::MenuItem("Logs", NULL, console->IsEnabled())) {
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

	return UPDATE_CONTINUE;
}

void ModuleGui::RenderGUI() const {
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

void ModuleGui::ProcessInputEvent(SDL_Event* event) const {
	ImGui_ImplSDL2_ProcessEvent(event);
}

bool ModuleGui::SceneFocused() const {
	return scene->IsFocused();
}

void ModuleGui::AddFPSCount(float fps, float ms) const {
	config->AddFps(fps, ms);
}

void ModuleGui::AddGameFPSCount(float fps, float ms) const {
	config->AddGameFps(fps, ms);
}