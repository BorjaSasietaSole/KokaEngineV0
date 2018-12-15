#ifndef __WINDOWGUIINSPECTOR_H__
#define __WINDOWGUINSPECTOR_H__

#include "WindowGui.h"
#include "Component.h"

class WindowGuiInspector : public WindowGui
{
public:
	WindowGuiInspector();
	~WindowGuiInspector();

	void Draw() override;
	void Focus(GameObject* gameobject);

private:
	bool focus = false;
};

#endif
