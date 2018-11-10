#include "ModuleGui.h"
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

static void ShowMenuBar();
//static void ShowAbout();
static void ShowHardware();
static void ShowTextureConfig();
static void ShowConsole();
//static void ShowZoomMagnifier();
static void PrintTextureParams(const char* currentTexture);
static void PrintMipMapOption(const char* currentTexture);

ModuleGui::ModuleGui() {
}

ModuleGui::~ModuleGui() {
}

bool ModuleGui::Init() {
	
	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 Core + GLSL 150
	glsl_version = "#version 150";
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	SDL_GL_SetSwapInterval(1);

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

														   // Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("./imgui/misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("./imgui/misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../imgui/misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("./imgui/misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	show_demo_window = true;
	show_another_window = false;
	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	return !err;
}

update_status ModuleGui::PreUpdate() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update() {

	update_status ret = UPDATE_CONTINUE;
	ShowMenuBar();

	if (showAboutMenu) {
		//ShowAbout();
	}

	if (showHardwareMenu) {
		ShowHardware();
	}

	if (showSceneConfig) {
		//ShowSceneConfig(fps_log, ms_log);
	}

	if (showTextureConfig) {
		ShowTextureConfig();
	}

	if (showConsole) {
		ShowConsole();
	}

	if (showZoomMagnifier) {
		//ShowZoomMagnifier();
	}

	if (requestedExit)
		ret = UPDATE_STOP;

	return ret;
}

update_status ModuleGui::PostUpdate() {
	// Rendering
	ImGui::Render();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

bool ModuleGui::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(App->renderer->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

void ModuleGui::HandleInputs(SDL_Event& event) {
	ImGui_ImplSDL2_ProcessEvent(&event);
}

// General menu options
static void ShowMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Exit")) { App->options->requestedExit = true; }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene")) {
			if (ImGui::MenuItem("Configuration")) { App->options->showSceneConfig = true; }
			if (ImGui::MenuItem("Textures")) { App->options->showTextureConfig = true; }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) {
			if (ImGui::MenuItem("Console")) { App->options->showConsole = true; }
			if (ImGui::MenuItem("Hardware")) { App->options->showHardwareMenu = true; }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About")) { App->options->showAboutMenu = true; }
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}

// Hardware
static void ShowHardware() {
	ImGui::Begin("Hardware specs", &App->options->showHardwareMenu, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("CPU Count: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.5f, 1.0f, 1.0f), "%d", SDL_GetCPUCount());
	ImGui::Text("System RAM: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.5f, 1.0f, 1.0f), "%d", SDL_GetSystemRAM());
	ImGui::End();
}

// Scene config
/*static void ShowSceneConfig(std::vector<float> fps, std::vector<float> ms) {
	ImGui::Begin("Camera", &App->editor->showSceneConfig, ImGuiWindowFlags_AlwaysAutoResize);
	bool fovXEdited = false, fovYEdited = false;
	if (ImGui::CollapsingHeader("Performance")) {
		char title[25];
		sprintf_s(title, 25, "Framerate %0.1f", fps[fps.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 200.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", ms[ms.size() - 1]);
		ImGui::PlotHistogram("##framerate", &ms[0], ms.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	}
	if (ImGui::CollapsingHeader("Camera properties")) {
		float camPos[3] = { App->camera->cameraPos.x, App->camera->cameraPos.y, App->camera->cameraPos.z };
		ImGui::InputFloat3("Cam position", camPos, "%.3f");
		ImGui::Separator();
		float front[3] = { App->camera->front.x, App->camera->front.y, App->camera->front.z };
		ImGui::InputFloat3("Front", front, "%.3f");
		float side[3] = { App->camera->side.x, App->camera->side.y, App->camera->side.z };
		ImGui::InputFloat3("Side", side, "%.3f");
		float up[3] = { App->camera->up.x, App->camera->up.y, App->camera->up.z };
		ImGui::InputFloat3("Up", up, "%.3f");
		ImGui::Separator();
		ImGui::InputFloat("Pitch", &App->camera->pitch, 0, 0, 0);
		ImGui::InputFloat("Yaw", &App->camera->yaw, 0, 0, 0);
	}
	if (ImGui::CollapsingHeader("Camera config")) {
		ImGui::SliderFloat("Mov Speed", &App->camera->cameraSpeed, 0.0f, 100.0f);
		ImGui::SliderFloat("Rot Speed", &App->camera->rotationSpeed, 0.0f, 100.0f);
		ImGui::SliderFloat("Mouse Sens", &App->camera->mouseSensitivity, 0.0f, 1.0f);
		ImGui::Separator();
		fovXEdited = ImGui::SliderFloat("Horz. Fov", &App->camera->fovX, 1.0f, 45.0f, "%.00f", 1.0f);
		if (ImGui::IsItemEdited()) {
			App->camera->SetHorizontalFOV(App->camera->fovX);
		}
		// TODO: Not working properly
		fovYEdited = ImGui::SliderFloat("Vertical. Fov", &App->camera->fovY, 1.0f, 45.0f, "%.00f", 1.0f);
		if (ImGui::IsItemEdited()) {
			App->camera->SetVerticalFOV(App->camera->fovY);
		}
		ImGui::InputFloat("AspectRatio", &App->camera->screenRatio, 0, 0, "%.3f");
		ImGui::SliderFloat("Near Plane", &App->camera->frustum.nearPlaneDistance, 0.1f, App->camera->frustum.farPlaneDistance);
		ImGui::SliderFloat("Far Plane", &App->camera->frustum.farPlaneDistance, 0.1f, 500.0f);
		ImGui::Separator();
		ImGui::SliderFloat3("Background color", App->renderer->bgColor, 0.0f, 1.0f);
	}
	ImGui::End();
}*/

//Texture config
static void ShowTextureConfig() {
	ImGui::Begin("Textures", &App->options->showTextureConfig, ImGuiWindowFlags_AlwaysAutoResize);
	const char* items[] = { "./textures/Lenna.png", "./textures/Lennin.dds", "./textures/Lolnope.jpg", "./textures/Lolyes.gif" };
	static const char* current_item = items[0];
	if (ImGui::BeginCombo("Available textures", current_item, ImGuiComboFlags_NoArrowButton))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]);
			if (ImGui::Selectable(items[n], is_selected)) {
				current_item = items[n];
				// App->textures->ReloadTexture(items[n], App->renderer->texture0);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Texture information")) {
		ImGui::InputText("Format", App->textures->imgFormat, sizeof(App->textures->imgFormat));
		// TODO: this should be something like App->exercise->texture0.Width
		/*ImGui::InputInt("Width", &App->textures->imgWidth, 0, 0);
		ImGui::InputInt("Height", &App->textures->imgHeight, 0, 0);
		ImGui::InputInt("Pixel depth", &App->textures->imgPixelDepth, 0, 0);*/
	}
	if (ImGui::CollapsingHeader("Texture config")) {
		PrintTextureParams(current_item);
		ImGui::Separator();
		PrintMipMapOption(current_item);
	}

	ImGui::End();
}

// Texture functions
static void PrintTextureParams(const char* currentTexture) {
	// Wrap methods
	const char* wrapMethods[] = { "GL_TEXTURE_WRAP_R", "GL_TEXTURE_WRAP_S", "GL_TEXTURE_WRAP_T" };
	const int wrapMethodsValues[] = { GL_TEXTURE_WRAP_R, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T };
	static const char* currentWrap = wrapMethods[0];
	if (ImGui::BeginCombo("Wrap methods", currentWrap, ImGuiComboFlags_NoArrowButton))
	{
		for (int wr = 0; wr < IM_ARRAYSIZE(wrapMethods); wr++)
		{
			bool wrapSelected = (currentWrap == wrapMethods[wr]);
			if (ImGui::Selectable(wrapMethods[wr], wrapSelected)) {
				currentWrap = wrapMethods[wr];
				// App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, App->textures->resizeMethod, wrapMethodsValues[wr], App->textures->clampMethod);
			}
			if (wrapSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	// Resize methods
	const char* resizeMethods[] = { "Linear", "Nearest" };
	const int resizeMethodsValues[] = { GL_LINEAR, GL_NEAREST };
	static const char* currentResize = resizeMethods[0];
	if (ImGui::BeginCombo("Resize methods", currentResize, ImGuiComboFlags_NoArrowButton))
	{
		for (int rs = 0; rs < IM_ARRAYSIZE(resizeMethods); rs++)
		{
			bool resizeSelected = (currentResize == resizeMethods[rs]);
			if (ImGui::Selectable(resizeMethods[rs], resizeSelected)) {
				currentResize = resizeMethods[rs];
				// App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, resizeMethodsValues[rs], App->textures->wrapMethod, App->textures->clampMethod);
			}
			if (resizeSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	// Clamp methods
	const char* clampMethods[] = { "GL_CLAMP", "GL_CLAMP_TO_BORDER", "GL_REPEAT", "GL_MIRRORED_REPEAT" };
	const int clampMethodsValues[] = { GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT };
	static const char* currentClamp = clampMethods[0];
	if (ImGui::BeginCombo("Clamp methods", currentClamp, ImGuiComboFlags_NoArrowButton))
	{
		for (int cl = 0; cl < IM_ARRAYSIZE(clampMethods); cl++)
		{
			bool clampSelected = (currentClamp == clampMethods[cl]);
			if (ImGui::Selectable(clampMethods[cl], clampSelected)) {
				currentClamp = clampMethods[cl];
				// App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, App->textures->resizeMethod, App->textures->wrapMethod, clampMethodsValues[cl]);
			}
			if (clampSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	// Texture filter methods
	const char* filterMethods[] = { "GL_TEXTURE_MIN_FILTER", "GL_TEXTURE_MAG_FILTER" };
	const int filterMethodsValues[] = { GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER };
	static const char* currentFilter = filterMethods[0];
	if (ImGui::BeginCombo("Filter methods", currentFilter, ImGuiComboFlags_NoArrowButton))
	{
		for (int fl = 0; fl < IM_ARRAYSIZE(filterMethods); fl++)
		{
			bool filterSelected = (currentFilter == filterMethods[fl]);
			if (ImGui::Selectable(filterMethods[fl], filterSelected)) {
				currentFilter = filterMethods[fl];
				// App->textures->SetNewParameter(currentTexture, App->exercise->texture0, filterMethodsValues[fl], App->textures->resizeMethod, App->textures->wrapMethod, App->textures->clampMethod);
			}
			if (filterSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

static void PrintMipMapOption(const char* currentTexture) {
	const char* mipMapState[] = { "Disabled", "Enabled" };
	bool valueMipMapValue[] = { false, true };
	static const char* currentMMState = mipMapState[0];
	if (ImGui::BeginCombo("MipMap", currentMMState, ImGuiComboFlags_NoArrowButton))
	{
		for (int mm = 0; mm < IM_ARRAYSIZE(mipMapState); mm++)
		{
			bool is_selected = (currentMMState == mipMapState[mm]);
			if (ImGui::Selectable(mipMapState[mm], is_selected)) {
				currentMMState = mipMapState[mm];
				// App->textures->SwitchMipMaps(currentTexture, App->exercise->texture0, valueMipMapValue[mm]);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

static void ShowConsole() {
	// CONSOLE("Console", &App->options->showConsole);
}