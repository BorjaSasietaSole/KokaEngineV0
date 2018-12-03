#ifndef __MESH_H__
#define __MESH_H__

#include "Globals.h"
#include "MathGeoLib.h"
#include <assimp/mesh.h>
#include <assert.h>
#include <vector>
#include "GL/glew.h"

struct Texture{
	int id = 0;
	int width = 0;
	int height = 0;
	const Texture(int id, int width, int height) : id(id), width(width), height(height) { }
};

class Mesh
{
	public:
		Mesh(aiMesh* mesh);
		~Mesh();

		void Draw(unsigned shaderProgram, const std::vector<Texture>& textures) const;

		int numIndices = 0;
		int materialIndex = 0;

		const char* getName() { return name; }
		std::vector<math::float3> getVerts() { return vertices; }
		AABB getBbox() { return bbox; }

	private:

		const char* name = nullptr;

		std::vector<math::float3> vertices;
		AABB bbox;

		unsigned vao = 0u;
		unsigned vbo = 0u;
		unsigned ibo = 0u;
};

#endif //__MESH_H__
