#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include <vector>
#include <assimp/mesh.h>
#include "Component.h"
#include "Math/float3.h"
#include "ModuleTextures.h"

struct par_shapes_mesh_s;
class ComponentMaterial;
class GameObject;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer);
	ComponentMesh(const ComponentMesh& duplicatedComponent);
	~ComponentMesh();

	void CleanUp();

	void ComputeMesh();
	void ComputeMesh(par_shapes_mesh_s* parMesh);
	void Draw(unsigned shaderProgram, const ComponentMaterial* material) const;
	void DrawProperties(bool enabled) override;
	void LoadMesh(const char* name);
	Component* Duplicate() override;
	
	void Save(Config* config) override;
	void Load(Config* config, rapidjson::Value& value) override;

	Mesh getMesh() { return mesh; }
	std::vector<std::string> getFileMeshesList() { return fileMeshesList; }
	std::string getCurrentMesh() { return currentMesh; }

private:
	Mesh mesh;
	std::vector<std::string> fileMeshesList;
	std::string currentMesh;
};

#endif