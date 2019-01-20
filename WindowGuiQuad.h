#ifndef __WINDOWGUIQUAD_H__
#define __WINDOWGUIQUAD_H__

#include "WindowGui.h"

class WindowGuiQuad : public WindowGui {
public:
	WindowGuiQuad();
	~WindowGuiQuad();

	void Draw() override;
	bool IsFocused() const { return focus; }

private:
	bool focus;
	int maxNodes;
};

#endif
