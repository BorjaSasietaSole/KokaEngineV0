#ifndef __WINDOWGUICAMERA_H__
#define __WINDOWGUICAMERA_H__

#include "windowGui.h"
class WindowGuiCamera : public WindowGui
{
public:
	WindowGuiCamera();
	~WindowGuiCamera();

	void Draw() override;
	bool IsFocused() const { return focus; }

private:
	bool focus = false;

};

#endif
