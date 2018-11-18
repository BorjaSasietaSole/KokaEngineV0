#include "WindowGuiConfiguration.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleModel.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "SDL.h"

WindowGuiConfiguration::WindowGuiConfiguration() {}

WindowGuiConfiguration::~WindowGuiConfiguration() {}

void WindowGuiConfiguration::Draw() {
	if (!ImGui::Begin("Configuration", &enabled)) {
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Application")) {
		DrawFPSgraph();
	}

	if (ImGui::CollapsingHeader("Camera")) {
		App->camera->DrawGui();
	}

	if (ImGui::CollapsingHeader("Input")) {
		App->input->DrawGui();
	}

	if (ImGui::CollapsingHeader("Textures")) {
		App->textures->DrawGui();
	}

	if (ImGui::CollapsingHeader("Renderer")) {
		App->renderer->DrawGui();
	}

	if (ImGui::CollapsingHeader("Models")) {
		App->model->DrawGui();
	}

	if (ImGui::CollapsingHeader("Window")) {
		App->window->DrawGui();
	}

	ImGui::End();
}

void WindowGuiConfiguration::AddFps(float fpsValue) {
	fps.insert(fps.begin(), fpsValue);
	if (fps.size() > NUMFPS) {
		fps.pop_back();
	}
}

void WindowGuiConfiguration::DrawFPSgraph() const{
	float total = 0.0f;
	for (int i = 0; i < fps.size(); i++) {
		total += fps[i];
	}
	char avg[32];
	sprintf_s(avg, "%s%.2f", "avg:", total / fps.size());
	ImGui::PlotHistogram("FPS", &fps[0], fps.size(), 0, avg, 0.0f, 120.0f, ImVec2(0, 80));
}