#ifndef __WINDOWGUITIME_H__
#define __WINDOWGUITIME_H__

#include "imgui.h"
#include "WindowGui.h"

class WindowGuiTime : public WindowGui
{
public:
	WindowGuiTime();
	~WindowGuiTime();

	void Draw() override;
};

#endif
