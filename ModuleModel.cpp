#include "assert.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModulePrograms.h"
#include "ModuleModel.h"
#include "GL/glew.h"

ModuleModel::ModuleModel() { }

ModuleModel::~ModuleModel() { }

unsigned ModuleModel::Load(const char* path) {
	assert(path != nullptr);

	models.emplace_back(path);

	LOG("Loaded Model: %s", path);

	return 1;
}

void ModuleModel::DrawModels() {

	for (auto const& model : models) {
		model.Draw();
	}

}

void ModuleModel::ApplyTexture(Texture texture) {

	for (auto& model : models) {
		model.UpdateTexture(texture);
	}

}

void ModuleModel::DeleteModels() {
	models.clear();
}

void ModuleModel::DrawGui() {

	if (models.size() != 0) {

		if (ImGui::CollapsingHeader("Model")) {

			for (auto& model : models) {
				model.DrawInfo();
			}

		}

		if (ImGui::Checkbox("Checkers Texture", &checkersTexture)) {

			if (checkersTexture && checkTexture->id == 0) {
				checkTexture = App->textures->Load("checkersTexture.jpg");
			}
		}
	}
}
