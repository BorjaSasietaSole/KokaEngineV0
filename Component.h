#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "document.h"

class Config;
class GameObject;

enum class ComponentType {
	EMPTY,
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL
};

class Component
{
public:
	Component(GameObject* goContainer, ComponentType type);
	Component(const Component& duplicateComponent);
	virtual ~Component();

	bool DrawComponentState();
	virtual void DrawProperties(bool enabled) { };
	virtual Component* Duplicate() { return nullptr; };

	virtual void Enable() { enabled = true; };
	virtual void Update();
	virtual void Disable() { enabled = false; };

	virtual void Save(Config* config) { };
	virtual void Load(Config* config, rapidjson::Value& value) { };

	bool getTobeDelete() { return toBeDeleted; }
	bool getEnabled() { return enabled; }

	ComponentType getComponentType() { return componentType; }
	
	const char* getUuid() { return uuid; }
	const char* getParentUuid() { return parentUuid; }
	GameObject*	getGoContainer() { return goContainer; }

private:
	bool toBeDeleted = false;
	bool enabled = true;
	ComponentType componentType = ComponentType::EMPTY;
	char uuid[37];
	char parentUuid[37];
	GameObject*	goContainer = nullptr;

};

#endif