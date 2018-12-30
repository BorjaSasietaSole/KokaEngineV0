#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "assert.h"
#include "Component.h"
#include "ModuleTextures.h"
#include "Geometry/AABB.h"
#include "Math/float3.h"
#include "Math/Quat.h"
#include <assimp/mesh.h>
#include <vector>
#include "GL/glew.h"

struct par_shapes_mesh_s;
class ComponentMaterial;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer, aiMesh* mesh);
	ComponentMesh(const ComponentMesh& duplicatedComponent);
	~ComponentMesh();

	void ComputeMesh(aiMesh* mesh);
	void ComputeMesh(par_shapes_mesh_s* mesh);
	const unsigned MaterialIndex();

	void CleanUp();
	void Draw(unsigned shaderProgram, const Texture* textures) const;
	void DrawProperties() override;
	Component* Duplicate() override;

	std::vector<math::float3> getVertices() { return vertices; }
	AABB getBox() { return bbox; }

	const int getMaterialIndex() { return materialIndex; }
	const int getIndex() { return numIndices; }

	void setName(const char* newName);

private:
	const char*	name = nullptr;
	int	numIndices = 0;
	int	materialIndex = 0;
	std::vector<math::float3> vertices;
	AABB bbox;

	unsigned vao = 0u;
	unsigned vbo = 0u;
	unsigned ibo = 0u;
};

#endif