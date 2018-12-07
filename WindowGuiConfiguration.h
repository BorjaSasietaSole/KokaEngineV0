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
	void AddFps(float fps, float ms);


private:
	void AddMemory(float mem);

	std::vector<float> fps;
	std::vector<float> ms;
	std::vector<float> gameFps;
	std::vector<float> gameMs;
	std::vector<float> mem;
};
#endif // __WINDOWGUICONFIGURATION_H__