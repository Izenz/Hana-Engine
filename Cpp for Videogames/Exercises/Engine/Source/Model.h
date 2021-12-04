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

class Mesh;

class Model	{
public:
	Model();
	~Model();

	bool Load(const char* file_name, const char* texture_path);
	void Draw();
	void CleanUp();

private:
	bool LoadMesh(const aiScene* scene);
	bool LoadTexture(const aiScene* scene);

	bool model_loaded = false, tex_loaded = false;
	aiString path;
	const char* tex_path;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
};

