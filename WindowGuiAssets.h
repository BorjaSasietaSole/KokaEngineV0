#ifndef __WINDOWGUIASSETS_H__
#define __WINDOWGUIASSETS_H__

#include "WindowGui.h"

class WindowGuiAssets : public WindowGui {

public:

	WindowGuiAssets();
	~WindowGuiAssets();

	void Draw() override;
	bool IsFocused() const { return focus; }
	void DrawTreeNode(const char* name, bool isLeaf);
	void ClickBehaviour(const char* name);

private:

	bool focus;
	std::string itemSelected;

};

#endif