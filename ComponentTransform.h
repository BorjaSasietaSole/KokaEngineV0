#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Math/float4x4.h"
#include "Math/Quat.h"
#include <assimp/scene.h> 

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* goContainer, const aiMatrix4x4& transform);
	~ComponentTransform();

	void AddTransform(const aiMatrix4x4& transform);
	void SetRotation(const math::Quat& rot);
	void SetPosition(const float3& pos);
	void RotationToEuler();

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
