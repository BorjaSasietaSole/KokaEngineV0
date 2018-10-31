#ifndef __ModuleRenderTriangle_h__
#define __ModuleRenderTriangle_h__

#include "Module.h"

class ModuleRenderTriangle : public Module
{
public:
    ModuleRenderTriangle();
    ~ModuleRenderTriangle();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
    unsigned vbo = 0;

};

#endif /* __ModuleRenderTriangle_h__ */
