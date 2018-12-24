#include "ComponentMaterial.h"
#include "ModulePrograms.h"
#include "Application.h"

ComponentMaterial::ComponentMaterial(GameObject* goContainer) : Component(goContainer, ComponentType::MATERIAL) {
	shader = App->programs->textureProgram;
}

ComponentMaterial::ComponentMaterial(GameObject* goContainer, const aiMaterial* material) : Component(goContainer, ComponentType::MATERIAL) {
	shader = App->programs->textureProgram;
	ComputeMaterial(material);
}

ComponentMaterial::ComponentMaterial(const ComponentMaterial& duplicatedComponent) : Component(duplicatedComponent), shader(duplicatedComponent.shader),
	texture(duplicatedComponent.texture){}

ComponentMaterial::~ComponentMaterial() {
	DeleteTexture();
}

Component* ComponentMaterial::Duplicate() {
	return new ComponentMaterial(*this);
}

void ComponentMaterial::ComputeMaterial(const aiMaterial* material) {
	std::string texturePath;
	if (material != nullptr) {
		aiTextureMapping mapping = aiTextureMapping_UV;
		aiString file;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &file, &mapping, 0);
		texturePath = getGoContainer()->GetFileFolder() + file.C_Str();
	}
	else {
		texturePath = "checkersTexture.jpg";
	}

	DeleteTexture();
	texture = App->textures->Load(texturePath.c_str());
}

void ComponentMaterial::DeleteTexture() {
	if (texture != nullptr) {
		glDeleteTextures(1, (GLuint*)& texture->id);
	}

	delete texture;
	texture = nullptr;
}

void ComponentMaterial::DrawProperties() {

	ImGui::PushID(this);
	if (ImGui::CollapsingHeader("Material")) {
		bool removed = Component::DrawComponentState();
		if (removed) {
			ImGui::PopID();
			return;
		}
		ImGui::Text("Shader: PlaceHolder");
		if (texture != nullptr) {
			ImGui::Text("Texture width:%d height:%d", texture->width, texture->height);
			float size = ImGui::GetWindowWidth();
			ImGui::Image((ImTextureID)texture->id, { size,size });
			ImGui::Separator();
		}
	}
	ImGui::PopID();
}