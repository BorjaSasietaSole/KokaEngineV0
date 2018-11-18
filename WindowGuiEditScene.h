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

	void Draw();
	bool IsFocused() const;

	bool focus = false;
};

#endif // __WINDOWGUIEDITSCENE_H__