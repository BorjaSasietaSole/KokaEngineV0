#ifndef __WINDOWGUIEDITSCENE_H__
#define __WINDOWGUIEDITSCENE_H__


#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "WindowGui.h"

class WindowGuiEditScene : public WindowGui {
public:
	WindowGuiEditScene();
	~WindowGuiEditScene();

	void Draw() override;
	bool IsFocused() const;

private:
	bool focus = false;
};

#endif