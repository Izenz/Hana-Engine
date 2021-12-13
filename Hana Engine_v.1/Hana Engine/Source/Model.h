#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <vector>
#include <string>
#include "ModuleTexture.h"
#include "Geometry/OBB.h"

class Mesh;

class Model	{
public:
	Model();
	~Model();

	bool Load(const char* file_name);
	void Draw() const;
	void CleanUp();
	bool IsLoaded() const;
	void LoadBoundingBox(const aiScene* scene);
	const vec& GetFocusTarget() const;

private:
	bool LoadMesh(const aiScene* scene);
	bool LoadTexture(const aiScene* scene);
	bool FindAndLoadTexture(const aiMaterial* mat);

	bool model_loaded = false, tex_loaded = false;
	std::string model_file_path, model_directory_path;

	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	OBB boundingBox;
};

