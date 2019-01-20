#include "WindowGuiEditScene.h"
#include "ModuleCamera.h"
#include "ImGuizmo/ImGuizmo.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

WindowGuiEditScene::WindowGuiEditScene(): focus(false), viewport(math::float2::zero) {}

WindowGuiEditScene::~WindowGuiEditScene() {}

void WindowGuiEditScene::Draw() {
	ImGui::Begin("Scene", &enabled, ImGuiWindowFlags_NoScrollbar);

	ImVec2 size = ImGui::GetWindowSize();
	
	App->camera->getSceneCamera()->SetScreenNewScreenSize(winSize.x, winSize.y);

	ImVec2 pos = ImGui::GetWindowPos();

	viewport.x = ImGui::GetCursorPosX() + pos.x;
	viewport.y = ImGui::GetCursorPosY() + pos.y;

	ImGui::Image((ImTextureID)App->camera->getSceneCamera()->getRenderTexture(), winSize, { 0,1 }, { 1,0 });
	App->renderer->DrawImGuizmo(winSize.x, winSize.y, pos.x, pos.y);

	App->camera->sceneFocused = ImGui::IsMouseHoveringWindow();

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}