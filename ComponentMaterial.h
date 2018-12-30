#ifndef __COMPONENTTMATERIAL_H__
#define __COMPONENTTMATERIAL_H__

#include "assert.h"
#include "GL/glew.h"
#include "Component.h"
#include "Component.h"
#include "Imgui/imgui.h"
#include "ModuleTextures.h"
#include "assimp/material.h"
#include "Math/float4.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* goContainer);
	ComponentMaterial(GameObject* goContainer, const aiMaterial* material);
	ComponentMaterial(const ComponentMaterial& duplicatedComponent);
	~ComponentMaterial();

	void ComputeMaterial(const aiMaterial* material);
	void DeleteTexture();

	Texture* GetTexture() const { return texture; }
	unsigned GetShader() const { return shader; }
	math::float4 getColor() { return color; }

	void DrawProperties() override;
	Component* Duplicate() override;

	void setShader(const unsigned newShader);
	void setTexture(Texture* newTexture);
	void setColor(math::float4 newColor);

private:
	unsigned shader = 0u;
	Texture* texture = nullptr;
	math::float4 color = math::float4::one;
};

#endif