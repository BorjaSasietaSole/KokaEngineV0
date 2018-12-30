#ifndef __MODULECAMERA_H_
#define __MODULECAMERA_H_

#include "Module.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "GameObject.h"
#include "Point.h"
#include "GL/glew.h"
#include "SDL.h"

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

	bool Init();
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;
	void DrawGui();

	// Movement
	void Move();
	void MovementSpeed();

	//Helper
	void FocusSelectedObject();
	void Zooming();

	void SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);

	void setSceneCamera(ComponentCamera* newCamera);
	void setSelectedCamera(ComponentCamera* newCamera);

	ComponentCamera* getSceneCamera() { return sceneCamera; }
	ComponentCamera* getSelectedCamera() { return selectedCamera; }
	std::vector<ComponentCamera*> getGameCameras() { return gameCameras; }

	float getCameraSpeed() { return cameraSpeed; }
	float getRotationSpeed() { return rotationSpeed; }
	float getMouseSensitivity() { return mouseSensitivity; }

	bool getFirstMouse() { return firstMouse; }
	float getLastX() { return lastX; }
	float getLastY() { return lastY; }

	GameObject* getSelectedObject() { return selectedObject; }

private:

	GameObject* selectedObject = nullptr;

	// User attributes
	float mouseSensitivity = 65.0f;
	float rotationSpeed = 65.0f;
	float cameraSpeed = 17.0f;;

	ComponentCamera* sceneCamera = nullptr;
	ComponentCamera* selectedCamera = nullptr;
	std::vector<ComponentCamera*> gameCameras;

	// Mouse 
	bool firstMouse = true;
	float lastX = 0.0f;
	float lastY = 0.0f;

};

#endif