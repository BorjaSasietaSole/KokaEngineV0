#include "WindowGuiQuad.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "QuadTreeKoka.h"

WindowGuiQuad::WindowGuiQuad(): focus(false), maxNodes(1) {}
WindowGuiQuad::~WindowGuiQuad() {}

void WindowGuiQuad::Draw() {

	if (!ImGui::Begin("QuadTree", &enabled)) {
		ImGui::End();
		return;
	}

	ImVec2 winSize = ImGui::GetWindowSize();

	ImGui::Checkbox("Draw", &App->renderer->showQuad);

	if (App->renderer->showQuad) {
		if (App->camera->quadCamera != nullptr) {
			ImGui::Image((ImTextureID)App->camera->quadCamera->renderTexture, { winSize.x, winSize.x }, { 0,1 }, { 1,0 });
		}
	}

	ImGui::SliderInt("Min nodes", &maxNodes, 1, 5);
	if (ImGui::Button("Recalculate")) {
		App->scene->quadTree->InitQuadTree(App->scene->quadTree->quadLimits);
	}

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}