#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <vector>
#pragma once


class Model
{
public:
	Model();
	~Model();

	bool Load(const char* file_name);
	//void LoadTexture(const aiScene* scene);
	void LoadMesh(const aiScene* scene);
	bool LoadMaterial(const aiScene* scene);

	void SetPath(const char* file_path);


private:
	aiString path;
	std::vector<aiMesh*> meshes;
	std::vector<aiTexture*> textures;
};

