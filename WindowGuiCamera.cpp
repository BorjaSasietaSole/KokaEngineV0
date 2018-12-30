#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "WindowGuiCamera.h"

WindowGuiCamera::WindowGuiCamera(){}

WindowGuiCamera::~WindowGuiCamera(){}

void WindowGuiCamera::Draw() {

	ImGui::Begin("Game", &enabled, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetCursorPos(ImVec2(-(App->window->width - size.x) * 0.5f, -(App->window->height - size.y) * 0.5f));
	if (App->camera->getSelectedCamera() != nullptr && App->camera->getSelectedCamera()->getEnabled() == true) {
		ImGui::Image((ImTextureID)App->camera->getSelectedCamera()->getRenderTexture(), { (float)App->window->width, (float)App->window->height }, { 0,1 }, { 1,0 });
	}
	else {
		ImGui::Image((ImTextureID)App->textures->noCameraSelectedTexture->id, { (float)App->window->width, (float)App->window->height }, { 0,1 }, { 1,0 });
	}
	ImGui::End();
}