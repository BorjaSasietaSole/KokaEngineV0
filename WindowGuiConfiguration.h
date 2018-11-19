#ifndef __WINDOWGUICONFIGURATION_H__
#define __WINDOWGUICONFIGURATION_H__

#include "WindowGui.h"
#include <vector>

#define NUMFPS 100

class WindowGuiConfiguration : public WindowGui
{
public:
	WindowGuiConfiguration();
	~WindowGuiConfiguration();

	void Draw();
	void DrawFPSgraph() const;
	void AddFps(float fps);


private:
	std::vector<float> fps;
};
#endif // __WINDOWGUICONFIGURATION_H__