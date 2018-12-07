#include "WindowGuiConfiguration.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "SDL.h"

#include "mmgr/mmgr.h"

WindowGuiConfiguration::WindowGuiConfiguration() : fps(NUMFPS), ms(NUMFPS), mem(NUMFPS),
gameFps(NUMFPS), gameMs(NUMFPS) {}

WindowGuiConfiguration::~WindowGuiConfiguration() {}

void WindowGuiConfiguration::Draw() {
	if (!ImGui::Begin("Configuration", &enabled, ImGuiWindowFlags_NoFocusOnAppearing)) {
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Application")) {
		ImGui::PushItemWidth(200.0f);
		static int framerateCap = App->timers->framerateCap;
		if (ImGui::SliderInt("MaxFPS", &framerateCap, 1, 120)) {
			App->timers->framerateCap = framerateCap;
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

		sMStats stats = m_getMemoryStatistics();
		AddMemory((float)stats.totalReportedMemory);

		ImGui::PlotHistogram("##memory", &mem[0], mem.size(), 0, "Memory Consumption (Bytes)", 0.0f, (float)stats.peakReportedMemory * 1.2f, ImVec2(0, 80));

		ImGui::Text("Total Reported Mem: %u", stats.totalReportedMemory);
		ImGui::Text("Total Actual Mem: %u", stats.totalActualMemory);
		ImGui::Text("Peak Reported Mem: %u", stats.peakReportedMemory);
		ImGui::Text("Peak Actual Mem: %u", stats.peakActualMemory);
		ImGui::Text("Accumulated Reported Mem: %u", stats.accumulatedReportedMemory);
		ImGui::Text("Accumulated Actual Mem: %u", stats.accumulatedActualMemory);
		ImGui::Text("Accumulated Alloc Unit Count: %u", stats.accumulatedAllocUnitCount);
		ImGui::Text("Total Alloc Unit Count: %u", stats.totalAllocUnitCount);
		ImGui::Text("Peak Alloc Unit Count: %u", stats.peakAllocUnitCount);
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

void WindowGuiConfiguration::AddMemory(float memVal) {

	for (unsigned i = 0u; i < NUMFPS - 1; ++i) {
		mem[i] = mem[i + 1];
	}

	mem[NUMFPS - 1] = memVal;
}