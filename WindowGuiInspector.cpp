#include "WindowGuiInspector.h"
#include "Application.h"
#include "ModuleScene.h"

WindowGuiInspector::WindowGuiInspector(): focus(false) {}
WindowGuiInspector::~WindowGuiInspector() {}

void WindowGuiInspector::Draw() {
	if(!ImGui::Begin("Inspector", &enabled)) {
		ImGui::End();
		return;
	}

	if (focus) {
		focus = false;
		ImGui::SetWindowFocus();
	}

	if (App->scene->getGoSelect() != nullptr) {
		App->scene->getGoSelect()->DrawProperties();

		if (ImGui::Button("Add Component", ImVec2(ImGui::GetWindowWidth(), 25))) {
			ImGui::OpenPopup("AddComponentPopup");
		}
		ImGui::SameLine();
		if (ImGui::BeginPopup("AddComponentPopup")) {
			ImGui::Text("Components");
			ImGui::Separator();
			if (ImGui::Selectable("Camera")) {
				App->scene->getGoSelect()->AddComponent(ComponentType::CAMERA);
			}
			ImGui::Separator();
			if (ImGui::Selectable("Mesh")) {
				App->scene->getGoSelect()->AddComponent(ComponentType::MESH);
			}
			if (ImGui::Selectable("Material")) {
				App->scene->getGoSelect()->AddComponent(ComponentType::MATERIAL);
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void WindowGuiInspector::Focus(GameObject* gameobject) {
	focus = true;
}