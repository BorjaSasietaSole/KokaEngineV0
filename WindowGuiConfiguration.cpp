#include "WindowGuiConfiguration.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleScene.h"

#include "mmgr/mmgr.h"

WindowGuiConfiguration::WindowGuiConfiguration() : fps(NUMFPS), ms(NUMFPS), mem(NUMFPS),
gameFps(NUMFPS), gameMs(NUMFPS) {}

WindowGuiConfiguration::~WindowGuiConfiguration() {
	fps.clear();
	ms.clear();
	mem.clear();
	gameFps.clear();
	gameMs.clear();
}

void WindowGuiConfiguration::Draw() {
	if (!ImGui::Begin("Configuration", &enabled, ImGuiWindowFlags_NoFocusOnAppearing)) {
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Application")) {
		ImGui::DragInt("Scale factor", &App->scene->scaleFactor);

		ImGui::PushItemWidth(200.0f);
		static int framerateCap = App->timers->maxFps;

		if (ImGui::SliderInt("MaxFPS", &framerateCap, 1, 120)) {
			App->timers->maxFps = framerateCap;
		}

		ImGui::PopItemWidth();

		if (ImGui::Checkbox("Vsync", &App->renderer->vsyncEnabled)) {
			if (App->renderer->vsyncEnabled) {
				SDL_GL_SetSwapInterval(1);
			}
			else {
				SDL_GL_SetSwapInterval(0);
			}
		}

		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", fps[fps.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 120.0f, ImVec2(0, 80));
		sprintf_s(title, 25, "Milliseconds %0.1f", ms[ms.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &ms[0], ms.size(), 0, title, 0.0f, 40.0f, ImVec2(0, 80));
	}

	if (ImGui::CollapsingHeader("Time")) {
		char title[35];
		sprintf_s(title, 25, "Framerate %0.1f", gameFps[gameFps.size() - 1]);
		ImGui::PlotLines("##framerate", &gameFps[0], gameFps.size(), 0, title, 0.0f, 200.0f, ImVec2(300, 50));
		sprintf_s(title, 25, "Milliseconds %0.1f", gameMs[gameMs.size() - 1]);
		ImGui::PlotLines("##framerate", &gameMs[0], gameMs.size(), 0, title, 0.0f, 40.0f, ImVec2(300, 50));

		ImGui::SliderFloat("Time Scale", &App->timers->gameTimeScale, 0.1f, 5.0f, "%0.1f");

		ImGui::Separator();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Time since App start: %f seconds", App->timers->getRealTime());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Frames since App start: %u", App->timers->getRealFrameCount());

		if (App->timers->gameState == GameState::STOP) {
			ImGui::TextDisabled("Time since Game start: 0.0000000 seconds");
			ImGui::TextDisabled("Frames since Game start: 0");
		}
		else {
			ImGui::TextColored(ImVec4(0.3f, 0.5f, 0.3f, 0.7f), "Time since Game start: %f seconds", App->timers->getGameTime());
			ImGui::TextColored(ImVec4(0.3f, 0.5f, 0.3f, 0.7f), "Frames since Game start: %u", App->timers->totalFrames);
		}
	}

	if (ImGui::CollapsingHeader("Camera")) {
		App->camera->DrawGui();
	}

	if (ImGui::CollapsingHeader("Textures")) {
		App->textures->DrawGUI();
	}

	if (ImGui::CollapsingHeader("Window")) {
		App->window->DrawGui();
	}

	ImGui::End();
}

void WindowGuiConfiguration::AddFps(float fpsValue, float msValue) {
	fps.insert(fps.begin(), fpsValue);
	ms.insert(ms.begin(), msValue);
	if (fps.size() > NUMFPS) {
		fps.pop_back();
	}
	if (ms.size() > NUMFPS) {
		ms.pop_back();
	}
}

void WindowGuiConfiguration::AddGameFps(float fpsVal, float msVal) {
	gameFps.insert(gameFps.begin(), fpsVal);
	gameMs.insert(gameMs.begin(), msVal);

	if (gameFps.size() > NUMFPS) {
		gameFps.pop_back();
	}

	if (gameMs.size() > NUMFPS) {
		gameMs.pop_back();
	}
}

void WindowGuiConfiguration::AddMemory(float memVal) {

	for (unsigned i = 0u; i < NUMFPS - 1; ++i) {
		mem[i] = mem[i + 1];
	}

	mem[NUMFPS - 1] = memVal;
}