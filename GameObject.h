#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <list>
#include <vector>
#include "imgui.h"
#include "assert.h"
#include "Globals.h"
#include "assimp/matrix4x4.h"
#include "Math/float4x4.h"
#include "Geometry/AABB.h"


class Component;
class ComponentTransform;
enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(const char* goName, const aiMatrix4x4& transform, const char* fileLocation);
	GameObject(const char* goName, const aiMatrix4x4& transform, GameObject* goParent, const char* fileLocation);
	GameObject(const GameObject& duplicateGameObject);
	~GameObject();

	void Update();
	void Draw() const;
	void CleanUp();
	void DrawProperties() const;
	void DrawHierarchy(GameObject* goSelected);
	std::string	GetFileFolder() const;

	Component* AddComponent(ComponentType type);
	void RemoveComponent(Component* component);
	Component*	GetComponent(ComponentType type) const;
	std::vector<Component*> GetComponents(ComponentType type) const;

	AABB& ComputeBBox() const;

	math::float4x4 GetLocalTransform() const;
	math::float4x4 GetGlobalTransform() const;
	void ModelTransform(unsigned shader) const;

	const char* getName() { return name; }
	void setName(const char* newName) { name = newName; }

	std::vector<Component*>	getComponents() { return components; }
	std::list<GameObject*> getGoChilds() { return goChilds; }

private:
	std::string				uuid = "";
	std::string				parentUuid = "";
	bool					enabled = true;
	bool					drawGOBBox = false;
	bool					drawChildsBBox = false;
	bool					duplicating = false;
	const char*				filePath = nullptr;
	const char*				name = DEFAULT_GO_NAME;
	GameObject*				parent = nullptr;
	std::vector<Component*>	components;
	std::list<GameObject*>	goChilds;

	ComponentTransform*		transform = nullptr;
	AABB&					bbox = AABB();

	bool					toBeDeleted = false;
	bool					toBeCopied = false;
	bool					moveGOUp = false;
	bool					moveGODown = false;
};

#endif