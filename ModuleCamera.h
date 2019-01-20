#ifndef __MODULECAMERA_H_
#define __MODULECAMERA_H_

#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include "GameObject.h"
#include "GL/glew.h"
#include "SDL.h"

class Camera;

class ModuleCamera : public Module
{

	enum CameraMovement {
		Upwards,
		Downwards,
		Left,
		Right,
		Forward,
		Backwards
	};

public:

	ModuleCamera();
	~ModuleCamera();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;
	void DrawGui();

	void SelectGameObject();

	// Movement
	void Move();
	void MovementSpeed();

	//Helper
	void FocusSelectedObject();
	void Zooming();

	void SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);

	void setSceneCamera(ComponentCamera* newCamera);
	void setSelectedCamera(ComponentCamera* newCamera);
	void setQuadCamera(ComponentCamera* newCamera);

	ComponentCamera* getQuadCamera() { return quadCamera; }
	ComponentCamera* getSceneCamera() { return sceneCamera; }
	ComponentCamera* getSelectedCamera() { return selectedCamera; }
	std::vector<ComponentCamera*> getGameCameras() { return gameCameras; }

	GameObject* getGoSelected() { return goSelected; }
	std::vector<GameObject*> getObjectsPossible() { return objectsPossiblePick; }

	math::LineSegment getRayCast() { return rayCast; }
	bool getSceneFocus() { return sceneFocused; }

	bool getFirstMouse() { return firstMouse; }
	float getLastX() { return lastX; }
	float getLastY() { return lastY; }

private:

	ComponentCamera* quadCamera = nullptr;
	ComponentCamera* sceneCamera = nullptr;
	ComponentCamera* selectedCamera = nullptr;
	std::vector<ComponentCamera*> gameCameras;

	GameObject*					goSelected = nullptr;
	std::vector<GameObject*>	objectsPossiblePick;

	math::LineSegment	rayCast;
	bool				sceneFocused;

	// Mouse 
	bool firstMouse;
	float lastX = 0.0f;
	float lastY = 0.0f;

};

#endif