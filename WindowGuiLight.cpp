#include "Component.h"
#include "WindowGuiLight.h"
#include "Application.h"
#include "ModuleScene.h"

WindowGuiLight::WindowGuiLight(): focus(false){}
WindowGuiLight::~WindowGuiLight(){}

void WindowGuiLight::Draw() {
	ImGui::Begin("Lights", &enabled, ImGuiWindowFlags_NoScrollbar);

	ImGui::Text("Ambient");
	ImGui::Separator();
	ImGui::SliderFloat("Intensity", &App->scene->ambientLight, 0.0f, 1.0f);
	ImGui::Text("Position");
	ImGui::DragFloat3("", (float*)&App->scene->lightPosition, 10.0f, -50000.f, 50000.f);

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}