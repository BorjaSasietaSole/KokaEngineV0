#include "ModuleScene.h"
#pragma warning(pop)

ModuleScene::ModuleScene() { }

ModuleScene::~ModuleScene() { }

bool ModuleScene::Init() {
	root = new GameObject();
	root->setName("root");

	return true;
}

update_status ModuleScene::Update() {
	update_status ret = UPDATE_CONTINUE;

	root->Update();

	return ret;
}

void ModuleScene::Draw() {
	root->Draw();
}

void ModuleScene::DrawHierarchy() {
	for (auto &child : this->root->getGoChilds()) {
		child->DrawHierarchy(goSelected);
	}
}


GameObject* ModuleScene::CreateGameObject(const char* goName, GameObject* goParent, const math::float4x4& transform, const char* fileLocation) {

	GameObject* gameObject = nullptr;

	if (goName != nullptr) {

		char* go_name = new char[strlen(goName)];
		strcpy(go_name, goName);

		gameObject = new GameObject(go_name, transform, goParent, fileLocation);

	}
	else {

		if (goParent != nullptr) {
			std::string childName = "ChildOf";
			childName += goParent->getName();

			gameObject = new GameObject(childName.c_str(), transform, goParent, fileLocation);
		}
		else {
			gameObject = new GameObject(std::string("GameObject").c_str(), transform, goParent, fileLocation);
		}

	}

	return gameObject;
}

GameObject* ModuleScene::CreateCamera(GameObject* goParent, const math::float4x4& transform) {
	GameObject* gameObject = nullptr;

	gameObject = new GameObject(DEFAULT_CAMERA_NAME, transform, goParent, nullptr);
	gameObject->AddComponent(ComponentType::CAMERA);

	return gameObject;
}

GameObject* ModuleScene::GenerateSphere(GameObject* goParent, int slices, int stacks, const math::float3& pos,
	const math::Quat& rot, const float size, const math::float4& color) {

	par_shapes_mesh* mesh = par_shapes_create_parametric_sphere(slices, stacks);

	if (mesh) {
		GameObject* sphere = new GameObject("Sphere", math::float4x4::identity, goParent, nullptr);
		sphere->getTransform()->SetRotation(rot);
		sphere->getTransform()->SetPosition(pos);

		par_shapes_scale(mesh, size, size, size);

		ComponentMesh* sphereMesh = (ComponentMesh*)sphere->AddComponent(ComponentType::MESH);
		sphereMesh->ComputeMesh(mesh);

		par_shapes_free_mesh(mesh);

		ComponentMaterial* sphereMaterial = (ComponentMaterial*)sphere->AddComponent(ComponentType::MATERIAL);
		sphereMaterial->setShader(App->programs->basicProgram);
		sphereMaterial->setColor(color);

		goSelected = sphere;

		return sphere;
	}

	LOG("Error: par_shape_mesh sphere error");
	return nullptr;
}

GameObject* ModuleScene::GenerateTorus(GameObject* goParent, const math::float3& pos, const math::Quat& rot,
	float innerRad, float outerRad, unsigned slices, unsigned stacks, const math::float4& color) {

	par_shapes_mesh* mesh = par_shapes_create_torus(slices, stacks, innerRad);

	if (mesh) {
		GameObject* torus = new GameObject("Torus", math::float4x4::identity, goParent, nullptr);
		torus->getTransform()->SetRotation(rot);
		torus->getTransform()->SetPosition(pos);

		par_shapes_scale(mesh, outerRad, outerRad, outerRad);

		ComponentMesh* torusMesh = (ComponentMesh*)torus->AddComponent(ComponentType::MESH);
		torusMesh->ComputeMesh(mesh);

		par_shapes_free_mesh(mesh);

		ComponentMaterial* torusMaterial = (ComponentMaterial*)torus->AddComponent(ComponentType::MATERIAL);
		torusMaterial->setShader(App->programs->basicProgram);
		torusMaterial->setColor(color);

		return torus;
	}

	LOG("Error: par_shape_mesh cylinder error");
	return nullptr;
}