#ifndef __COMPONENTCAMERA_H__
#define __COMPONENTCAMERA_H__

#include "Component.h"
#include "MathGeoLib.h"
#include "imgui/imgui.h"
#include "glew-2.1.0/include/GL/glew.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* goParent);
	~ComponentCamera();

	void DrawProperties(bool enabled) override;
	Component* Duplicate() override;
	void Update();

	void InitFrustum();

	void LookAt(math::float3 target);
	math::float4x4 GetViewMatrix();
	math::float4x4 GetProjectionMatrix();

	void Rotate(float dx, float dy);
	void Orbit(float dx, float dy);

	void SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
	void SetHorizontalFOV(float fovXDegrees);
	void SetVerticalFOV(float fovYDegrees);

	void setCameraPosition(const math::float3 newPosition);
	void setCameraFront(const math::float3 newPosition);
	void setCameraUp(const math::float3 newPosition);

	void setCameraSpeed(const float newSpeed);
	void setRotationSpeed(const float newSpeed);

	math::Frustum frustum;

	math::float3 getCameraPosition() { return cameraPosition; }
	math::float3 getCameraFront() { return cameraFront; }
	math::float3 getCameraUp() { return cameraUp; }

	float getMaxFov() { return maxFov; }
	float getMinFov() { return minFov; }
	float getPitch() { return pitch; }
	float getYaw() { return yaw; }
	float getCameraSpeed() { return cameraSpeed; }
	float getRotationSpeed() { return rotationSpeed; }

	unsigned getRenderTexture() { return renderTexture; }
	unsigned getFbo() { return fbo; }

	bool debugDraw = true;

	void CreateFrameBuffer();

	void Load(Config* config, rapidjson::Value& value) override;
	void Save(Config* config) override;

	private:

		math::float3 cameraPosition = math::float3(0.0f, 3.0f, 20.0f);
		math::float3 cameraFront = math::float3(0.0f, 0.0f, -1.0f);
		math::float3 cameraUp = math::float3(0.0f, 1.0f, 0.0f);

		// Camera specs
		float maxFov = 100.0f;
		float minFov = 10.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;

		unsigned screenWidth = SCREEN_WIDTH;
		unsigned screenHeight = SCREEN_HEIGHT;

		float screenRatio = screenWidth / screenHeight;

		float cameraSpeed = 15.0f;
		float rotationSpeed = 65.0f;
		float mouseSensitivity = 0.2f;

		float fovY = 45.0f;
		float fovX = 45.0f;
		float zoomValue = 0.0f;

		unsigned fbo = 0u;
		unsigned rbo = 0u;
		unsigned renderTexture = 0u;

		//Camera debug settings
		bool debugDraw = true;
		int	wireFrame = GL_FILL;

		void zCreateFrameBuffer(float winWidth, float winHeight);
		void SetHorizontalFOV(float fovXDegrees);
		void SetVerticalFOV(float fovYDegrees);
};

#endif
