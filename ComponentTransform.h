#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Component.h"
#include "imgui.h"
#include "Math/MathFunc.h"
#include "Math/float4x4.h"
#include "Math/Quat.h"
#include <assimp/scene.h> 

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* goContainer, const math::float4x4& transform);
	ComponentTransform(const ComponentTransform& duplicatedTransform);
	~ComponentTransform();

	void AddTransform(const math::float4x4& transform);
	void SetRotation(const math::Quat& rot);
	void SetPosition(const float3& pos);
	void RotationToEuler();

	void SetLocalToWorld(const math::float4x4& localTrans);
	void SetWorldToLocal(const math::float4x4& parentTrans);

	void DrawProperties() override;
	Component* Duplicate() override;

	math::float3 getPosition() { return position; }
	math::Quat getRotation() { return rotation; }
	math::float3 getEulerRotation() { return eulerRotation; }
	math::float3 getScale() { return scale; }

private:
	math::float3 position = math::float3::zero;
	math::Quat rotation = math::Quat::identity;
	math::float3 eulerRotation = math::float3::zero;
	math::float3 scale = math::float3::zero;
};

#endif
