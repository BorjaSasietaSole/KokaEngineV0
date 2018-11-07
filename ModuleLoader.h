#ifndef __ModuleLoader_h__
#define __ModuleLoader_h__

#include "Module.h"

#include "MathGeoLib.h"

#include <vector>

struct aiScene;

class ModuleLoader : public Module
{
public:

	ModuleLoader();
	~ModuleLoader();

	bool            Init();
	update_status   Update();
	bool            CleanUp();

private:

	void            GenerateMeshes(const aiScene* scene);
	void            GenerateMaterials(const aiScene* scene);

public:

	struct Mesh
	{
		unsigned vbo = 0;
		unsigned ibo = 0;
		unsigned material = 0;
		unsigned num_vertices = 0;
		unsigned num_indices = 0;
	};

	struct Material
	{
		unsigned texture0 = 0;
	};

	std::vector<Mesh>     meshes;
	std::vector<Material> materials;
	math::float4x4        transform = math::float4x4::identity;
};

#endif // __ModuleLoader_h__ 
