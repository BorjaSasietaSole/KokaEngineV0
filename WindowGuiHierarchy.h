#ifndef __WINDOWGUIHERIARCHY_H__
#define __WINDOWGUIHERIARCHY_H__

#include "WindowGui.h"

class WindowGuiHierarchy : public WindowGui {

public:
	WindowGuiHierarchy();
	~WindowGuiHierarchy();

	void Draw() override;

};

#endif