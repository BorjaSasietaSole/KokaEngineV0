#ifndef __WINDOWGUILIGHT_H__
#define __WINDOWGUILIGHT_H__

#include "WindowGui.h"

class WindowGuiLight : public WindowGui {

public:
	WindowGuiLight();
	~WindowGuiLight();

	void Draw() override;
	bool IsFocused() const { return focus; }

private:

	bool focus;
};

#endif