#ifndef __WINDOWGUICONSOLE_H__
#define __WINDOWGUICONSOLE_H__

#include "WindowGui.h"

class WindowGuiConsole : public WindowGui
{
public:
	WindowGuiConsole();
	~WindowGuiConsole();

	void Clear();
	void AddLog(const char* log);
	void Draw() override;

private:
	ImGuiTextBuffer buf;
	ImVector<int> lineOffsets;
	bool scrollToBottom = true;
};

#endif
