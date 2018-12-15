#ifndef __WINDOWGUI_H__
#define __WINDOWGUI_H__

#include "ImGui/imgui.h"

class WindowGui
{
public:
	WindowGui();
	~WindowGui();

	virtual void Draw() {}

	bool IsEnabled() const { return enabled; }
	void ToggleEnabled();
	bool IsFocused() const { return focused; }
	void ToggleFocused();

protected:
	bool enabled;
	bool focused;
};

#endif