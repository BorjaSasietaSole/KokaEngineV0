#include "WindowGuiTime.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleWindow.h"

WindowGuiTime::WindowGuiTime() {}
WindowGuiTime::~WindowGuiTime(){}

void WindowGuiTime::Draw() {
	ImGui::Begin("Time", &enabled, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetCursorPos(ImVec2(-(App->window->width - size.x) * 0.5f, -(App->window->height - size.y) * 0.5f));

	ImGui::BeginMenuBar();

	if (App->timers->gameState == GameState::STOP) {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.5f, 0.5f, 0.7f });
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.3f, 0.5f, 0.3f, 0.7f });
	}

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 1.0f, 1.0f, 0.2f });

	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 85) / 2);
	if (ImGui::ArrowButton("Play", ImGuiDir_Right)) {
		if (App->timers->gameState == GameState::STOP) {
			App->timers->StartGameClock();
		}
		else {
			App->timers->StopGameClock();
		}
	}

	ImGui::PopStyleColor(2);
	if (App->timers->gameState == GameState::PAUSE) {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.3f, 0.5f, 0.3f, 0.7f });
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.5f, 0.5f, 0.7f });
	}

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 1.0f, 1.0f, 0.2f });
	ImGui::SameLine();

	if (ImGui::Button("||", { 23,19 })) {
		if (App->timers->gameState == GameState::RUN) {
			App->timers->PauseGameClock(true);
		}
		else if (App->timers->gameState == GameState::PAUSE) {
			App->timers->PauseGameClock(false);
		}
	}

	ImGui::PopStyleColor(2);
	ImGui::SameLine();

	if (App->timers->gameState == GameState::PAUSE) {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.3f, 0.5f, 0.3f, 0.7f });
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.5f, 0.5f, 0.7f });
	}

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 1.0f, 1.0f, 0.2f });
	if (App->timers->nextFrame) {
		App->timers->nextFrame = false;
		App->timers->PauseGameClock(true);
	}

	if (ImGui::Button("->", { 23,19 }) && App->timers->gameState == GameState::PAUSE) {
		App->timers->nextFrame = true;
		App->timers->PauseGameClock(false);
	}

	ImGui::PopStyleColor(2);
	ImGui::EndMenuBar();

	ImGui::End();
}