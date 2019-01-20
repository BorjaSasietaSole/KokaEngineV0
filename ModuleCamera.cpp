#include "Globals.h"
#include "Point.h"
#include "ModuleTime.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleGui.h"
#include "ModuleCamera.h"
#include "QuadTreeKoka.h"
#include "ComponentTransform.h"

ModuleCamera::ModuleCamera(): sceneFocused(false), firstMouse(true) { }

ModuleCamera::~ModuleCamera() {
	CleanUp();
}

bool ModuleCamera::Init() {

	sceneCamera = new ComponentCamera(nullptr);
	sceneCamera->InitFrustum();
	sceneCamera->debugDraw = true;

	quadCamera = new ComponentCamera(nullptr);
	quadCamera->InitOrthographicFrustum(math::float3(0.0f, 8.5f * App->scene->scaleFactor, 0.0f), math::float3(0.0f, -1.0f, 0.0f), math::float3(0.0f, 0.0f, 1.0f));
	quadCamera->debugDraw = true;

	return true;
}

update_status ModuleCamera::PreUpdate() {

	BROFILER_CATEGORY("CameraPreUpdate()", Profiler::Color::Plum);
	if (App->options->SceneFocused()) {

		MovementSpeed();

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
			Move();
			SDL_ShowCursor(SDL_DISABLE);
			sceneCamera->Rotate(sceneCamera->rotationSpeed * App->input->GetMouseMotion().x, sceneCamera->rotationSpeed * App->input->GetMouseMotion().y);
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP) {
			SDL_ShowCursor(SDL_ENABLE);
		}

		FocusSelectedObject();

		if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) {
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
				SDL_ShowCursor(SDL_DISABLE);
				sceneCamera->Orbit(sceneCamera->rotationSpeed * App->input->GetMouseMotion().x, sceneCamera->rotationSpeed * App->input->GetMouseMotion().y);
			}
			else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
				SDL_ShowCursor(SDL_ENABLE);
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_UP) {
			SDL_ShowCursor(SDL_ENABLE);
		}

		Zooming();

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && sceneFocused && !ImGuizmo::IsOver()) {
			SelectGameObject();
		}

	}

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() {
	BROFILER_CATEGORY("CameraUpdate()", Profiler::Color::Plum);

	if (selectedCamera != nullptr && selectedCamera->getEnabled()) {
		selectedCamera->Update();
	}

	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp() {

	for (auto& gameCam : gameCameras) {
		delete gameCam;
		gameCam = nullptr;
	}

	objectsPossiblePick.clear();

	selectedCamera = nullptr;

	delete sceneCamera;
	sceneCamera = nullptr;

	delete quadCamera;
	quadCamera = nullptr;

	return true;
}

void ModuleCamera::Zooming() {

	const int wheelSlide = App->input->GetMouseWheel();
	if (wheelSlide != 0) {
		float zoomValue = sceneCamera->frustum.verticalFov + -wheelSlide * 0.02f * App->scene->scaleFactor * App->timers->getRealDeltaTime();
		float newAngleFov = math::Clamp(zoomValue, math::DegToRad(sceneCamera->minFov), math::DegToRad(sceneCamera->maxFov));
		sceneCamera->frustum.verticalFov = newAngleFov;
		sceneCamera->frustum.horizontalFov = 2.0f * atanf(tanf(newAngleFov * 0.5f) * ((float)sceneCamera->screenWidth / (float)sceneCamera->screenHeight));
	}
}

void ModuleCamera::SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight) {
	
	for (auto& camera : gameCameras) {
		camera->SetScreenNewScreenSize(newWidth, newHeight);
	}
	selectedCamera->SetScreenNewScreenSize(newWidth, newHeight);
}

void ModuleCamera::FocusSelectedObject() {

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && App->scene->getGoSelect() != nullptr) {
		math::AABB& bbox = App->scene->getGoSelect()->ComputeBBox();
		math::float3 HalfSize = bbox.HalfSize();
		float distX = HalfSize.x / tanf(sceneCamera->frustum.horizontalFov*0.5f);
		float distY = HalfSize.y / tanf(sceneCamera->frustum.verticalFov*0.5f);
		float camDist = MAX(distX, distY) + HalfSize.z; //camera distance from model

		math::float3 center = bbox.FaceCenterPoint(5);
		sceneCamera->frustum.pos = center + math::float3(0, 0, camDist);
		sceneCamera->frustum.front = -math::float3::unitZ;
		sceneCamera->frustum.up = math::float3::unitY;
	}

}

void ModuleCamera::MovementSpeed() {
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) {
		sceneCamera->cameraSpeed = sceneCamera->cameraSpeed * 2;
		sceneCamera->rotationSpeed = sceneCamera->rotationSpeed * 2;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP) {
		sceneCamera->cameraSpeed = sceneCamera->cameraSpeed * 0.5f;
		sceneCamera->rotationSpeed = sceneCamera->rotationSpeed * 0.5f;
	}
}

void ModuleCamera::Move() {

	float distance = 5.0f * App->timers->getRealDeltaTime();
	float3 movement = float3::zero;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
		distance *= 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_Q)) {
		movement += math::float3::unitY*distance;
	}
	if (App->input->GetKey(SDL_SCANCODE_E)) {
		movement -= math::float3::unitY*distance;
	}
	if (App->input->GetKey(SDL_SCANCODE_S)) {
		movement -= sceneCamera->frustum.front*distance;
	}
	if (App->input->GetKey(SDL_SCANCODE_W)) {
		movement += sceneCamera->frustum.front*distance;
	}
	if (App->input->GetKey(SDL_SCANCODE_A)) {
		movement -= sceneCamera->frustum.WorldRight()*distance;
	}
	if (App->input->GetKey(SDL_SCANCODE_D)) {
		movement += sceneCamera->frustum.WorldRight()*distance;
	}

	sceneCamera->frustum.Translate(movement);
}

void ModuleCamera::SelectGameObject() {
	const fPoint mousePos = App->input->GetMousePosition();

	float normalizedX = -(1.0f - (float(mousePos.x - App->options->scene->viewport.x) * 2.0f) / App->options->scene->winSize.x);
	float normalizedY = 1.0f - (float(mousePos.y - App->options->scene->viewport.y) * 2.0f) / App->options->scene->winSize.y;

	rayCast = sceneCamera->frustum.UnProjectLineSegment(normalizedX, normalizedY);

	objectsPossiblePick.clear();
	App->scene->quadTree->CollectIntersections(objectsPossiblePick, rayCast);

	for (std::list<ComponentMesh*>::iterator iterator = App->renderer->getMeshes().begin(); iterator != App->renderer->getMeshes().end(); ++iterator) {
		if (!(*iterator)->goContainer->getStaticGo() && (*iterator)->getMesh().verticesNumber > 0 && rayCast.Intersects((*iterator)->goContainer->ComputeBBox)) {
			objectsPossiblePick.push_back((*iterator)->goContainer);
		}
	}

	float minDistance = -.1f * App->scene->scaleFactor;
	GameObject* gameObjectHit = nullptr;
	if (objectsPossiblePick.size() > 0) {
		for (std::vector<GameObject*>::iterator iterator = objectsPossiblePick.begin(); iterator != objectsPossiblePick.end(); ++iterator) {
			ComponentMesh* componentMesh = (ComponentMesh*)(*iterator)->GetComponent(ComponentType::MESH);
			ComponentTransform* componentTransform = (ComponentTransform*)(*iterator)->GetComponent(ComponentType::TRANSFORM);

			if (componentTransform != nullptr && componentMesh != nullptr) {
				Mesh mesh = componentMesh->getMesh();
				math::LineSegment localTransformPikingLine(rayCast);
				localTransformPikingLine.Transform(componentTransform->GetGlobalTransform().Inverted());

				math::Triangle triangle;
				for (unsigned i = 0u; i < mesh.indicesNumber; i += 3) {
					//Only the parmesh meshes does not contains indices, also we dont want to check triangles if GO has no mesh selected
					if (mesh.indices != nullptr && mesh.verticesNumber > 0) {
						triangle.a = { mesh.vertices[mesh.indices[i] * 3], mesh.vertices[mesh.indices[i] * 3 + 1], mesh.vertices[mesh.indices[i] * 3 + 2] };
						triangle.b = { mesh.vertices[mesh.indices[i + 1] * 3], mesh.vertices[mesh.indices[i + 1] * 3 + 1], mesh.vertices[mesh.indices[i + 1] * 3 + 2] };
						triangle.c = { mesh.vertices[mesh.indices[i + 2] * 3], mesh.vertices[mesh.indices[i + 2] * 3 + 1], mesh.vertices[mesh.indices[i + 2] * 3 + 2] };

						float triangleDistance;
						math::float3 hitPoint;
						if (localTransformPikingLine.Intersects(triangle, &triangleDistance, &hitPoint)) {
							if (minDistance == -.1f * App->scene->scaleFactor || triangleDistance < minDistance) {
								minDistance = triangleDistance;
								gameObjectHit = *iterator;
							}
						}
					}

				}
			}
		}
	}

	if (gameObjectHit != nullptr) {
		if (App->renderer->selectAncestorOnClick) {
			GameObject* inheritedTrasnform = gameObjectHit;
			while (inheritedTrasnform->getParent() != App->scene->getRoot()) {
				inheritedTrasnform = inheritedTrasnform->getParent();
			}
			App->scene->setGoSelected(inheritedTrasnform);
		}
		else {
			App->scene->setGoSelected(gameObjectHit);
		}
	}
	else {
		App->scene->setGoSelected(nullptr);
	}
}

void ModuleCamera::DrawGui() {

	ImGui::Checkbox("Debug", &sceneCamera->debugDraw);

	ImGui::Checkbox("Frustum culling", &App->renderer->frustCulling);
	if (App->renderer->frustCulling) {
		ImGui::RadioButton("Frustum", &App->renderer->frustumCullingType, 0); ImGui::SameLine();
		ImGui::RadioButton("QuadTree", &App->renderer->frustumCullingType, 1);
	}

	ImGui::Checkbox("Raycast drawing", &App->renderer->showRayCast);

	ImGui::Checkbox("Select ancestor on click", &App->renderer->selectAncestorOnClick);

	float fov = math::RadToDeg(sceneCamera->frustum.verticalFov);
	if (ImGui::SliderFloat("FOV", &fov, 40, 120)) {
		sceneCamera->frustum.verticalFov = math::DegToRad(fov);
		sceneCamera->frustum.horizontalFov = 2.f * atanf(tanf(sceneCamera->frustum.verticalFov * 0.5f) * ((float)App->window->width / (float)App->window->height));
	}

	ImGui::SliderFloat("zNear", &sceneCamera->frustum.nearPlaneDistance, 0.01f * App->scene->scaleFactor, sceneCamera->frustum.farPlaneDistance);
	ImGui::SliderFloat("zFar", &sceneCamera->frustum.farPlaneDistance, sceneCamera->frustum.nearPlaneDistance, 100.0f * App->scene->scaleFactor);
}

void ModuleCamera::setSceneCamera(ComponentCamera* newCamera) {
	sceneCamera = newCamera;
}

void ModuleCamera::setSelectedCamera(ComponentCamera* newCamera) {
	selectedCamera = newCamera;
}

void ModuleCamera::setQuadCamera(ComponentCamera* newCamera) {
	quadCamera = newCamera;
}