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

#include "document.h"
#include "prettywriter.h"

class Config;
class Component;
class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;
enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(std::string goName, GameObject* goParent);
	GameObject(std::string goName, const math::float4x4& transform);
	GameObject(std::string goName, const math::float4x4& transform, GameObject* goParent);
	GameObject(const GameObject& duplicateGameObject);
	~GameObject();

	void Update();
	void DrawProperties();
	void DrawHierarchy(GameObject* goSelected);

	Component* AddComponent(ComponentType type);
	std::list<Component*>::iterator RemoveComponent(std::list<Component*>::iterator component);
	Component* GetComponent(ComponentType type) const;
	std::vector<Component*> GetComponents(ComponentType type) const;

	AABB& ComputeBBox();

	math::float4x4 GetLocalTransform() const;
	math::float4x4 GetGlobalTransform() const;
	void ModelTransform(unsigned shader) const;

	void UpdateStaticChilds(bool staticState);

	std::string getName() { return name; }
	void setName(const char* newName) { name = newName; }

	std::list<GameObject*> getGoChilds() { return goChilds; }

	ComponentTransform* getTransform() { return transform; }
	ComponentMesh* getMesh() { return mesh; }
	ComponentMaterial* getMatertial() { return material; }
	std::list<Component*> getComponents() { return components; }

	void setTransform(ComponentTransform* newTransform);

	bool Save(Config* config);
	void Load(Config* config, rapidjson::Value& value);

	bool geToBeDeleted() { return toBeDeleted; }
	bool getToBeCopied() { return toBeCopied; }
	bool getMoveGOUp() { return moveGOUp; }
	bool getMoveGODown() { return moveGODown; }
	bool getStaticGo() { return staticGo; }

	const char* getUuid() { return uuid; }
	const char* getParentUuid() { return parentUuid; }
	
	GameObject* getParent() { return parent; }

	bool getEnabled() {	return enabled;	}

private:
	char uuid[37];
	char parentUuid[37];
	bool enabled = true;
	bool drawGOBBox = false;
	bool duplicating = false;
	std::string	name = std::string(DEFAULT_GO_NAME);
	GameObject*	parent = nullptr;
	std::list<GameObject*> goChilds;

	math::AABB bbox;

	ComponentTransform*	transform = nullptr;
	ComponentMesh* mesh = nullptr;
	ComponentMaterial* material = nullptr;
	std::list<Component*> components;

	bool toBeDeleted = false;
	bool toBeCopied = false;
	bool moveGOUp = false;
	bool moveGODown = false;
	bool staticGo = false;
};

#endif