#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include <list>
#include "Module.h"
#include "GameObject.h"
#include "assimp/matrix4x4.h"
#include "ComponentMesh.h"
#include "ModulePrograms.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentLight.h"

enum class ComponentType;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool Init() override;
	update_status Update() override;
	void Draw();
	void DrawHierarchy();

	GameObject* CreateGameObject(const char* goName, GameObject* goParent, const math::float4x4& transform = math::float4x4(), const char* fileLocation = nullptr);
	GameObject* CreateCamera(GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity);
	GameObject* GenerateSphere(GameObject* goParent, int slices, int stacks, const math::float3& pos, const math::Quat& rot, const float size, const math::float4& color);
	GameObject* GenerateTorus(GameObject* goParent, const math::float3& pos, const math::Quat& rot, float innerRad, float outerRad, unsigned slices, unsigned stacks, const math::float4& color);

	GameObject* getRoot() { return root; }
	GameObject* getGoSelect() { return goSelected; }

	void setGoSelected(GameObject* selected);

private:
	GameObject* root = nullptr;
	GameObject* goSelected = nullptr;
};

#endif