#ifndef __WINDOWGUI_H__
#define __WINDOWGUI_H__

#include "ImGui/imgui.h"

class WindowGui
{
public:
	WindowGui();
	~WindowGui();

	virtual void Draw() {}

	bool IsEnabled() const {
		return enabled;
	}

	void ToggleEnabled() {
		enabled = !enabled;
	}

	bool enabled = true;
};

#endif //__WINDOWGUI_H__
