#ifndef __WINDOWGUIHERIARCHY_H__
#define __WINDOWGUIHERIARCHY_H__

#include "WindowGui.h"

class WindowGuiHierarchy : WindowGui {

public:
	WindowGuiHierarchy();
	~WindowGuiHierarchy();

	void Draw() override;

};

#endif