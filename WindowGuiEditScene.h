#ifndef __WINDOWGUIEDITSCENE_H__
#define __WINDOWGUIEDITSCENE_H__

#include "WindowGui.h"
#include "Math/float2.h"

class WindowGuiEditScene : public WindowGui {
public:
	WindowGuiEditScene();
	~WindowGuiEditScene();

	void Draw() override;
	bool IsFocused() const { return focus; }
	ImVec2 getWinSize() { return winSize; }
	math::float2 getViewport() { return viewport; }

private:
	bool focus;
	ImVec2 winSize;
	math::float2 viewport;
};
#endif