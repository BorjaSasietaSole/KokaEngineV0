#ifndef __MODULECAMERA_H_
#define __MODULECAMERA_H_

#include "Module.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "GameObject.h"
#include "Globals.h"
#include "Point.h"
#include "MathGeoLib.h"
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
	bool CleanUp() override;
	void DrawGui();

	// Movement
	void CameraMovementKeyboard();
	void RotateCamera(const fPoint& mousePosition, bool orbit = false);
	void MoveCamera(CameraMovement cameraSide);

	//Helper
	void FocusSelectedObject();
	void UpdatePitchYaw();
	void Zooming();

	GameObject* selectedObject = nullptr;

	math::float3 getCameraPos() { return cameraPos; }
	math::float3 getFront() { return front; }
	math::float3 getSide() { return side; }
	math::float3 getUp() { return up; }

private:

	// User attributes
	float mouseSensitivity = 65.0f;
	float rotationSpeed = 65.0f;
	float cameraSpeed = 17.0f;;

	// Camera specs
	float maxFov = 100.0f;
	float minFov = 10.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	math::float3 cameraPos;

	//ViewMatrix info
	math::float3 front;
	math::float3 side;
	math::float3 up;

	// Mouse 
	bool firstMouse = true;
	float lastX = 0.0f;
	float lastY = 0.0f;

};

#endif