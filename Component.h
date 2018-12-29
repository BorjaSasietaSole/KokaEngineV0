#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "GameObject.h";

enum class ComponentType {
	EMPTY,
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT
};

class Component{

public:
	Component(GameObject* goContainer, ComponentType type);
	Component(const Component& duplicateComponent);
	virtual ~Component();

	bool DrawComponentState();
	virtual void DrawProperties() { };
	virtual Component*	Duplicate() { return nullptr; };

	virtual void Enable() { enabled = true; };
	virtual void Update();
	virtual void Disable() { enabled = false; };
	void Remove();

	void setGoContainer(GameObject* newContainer);
	void setParentUuid(std::string newParentUuid);

	GameObject* getGoContainer() { return goContainer; }
	ComponentType getComponentType() { return componentType; }
	bool getEnabled() { return enabled; }


private:
	bool enabled = true;
	ComponentType componentType = ComponentType::EMPTY;
	std::string	uuid = "";
	std::string	parentUuid = "";
	GameObject* goContainer = nullptr;
};

#endif