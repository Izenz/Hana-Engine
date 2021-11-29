#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <vector>



class Model	{
public:
	Model();
	~Model();

	bool Load(const char* file_name);

	void SetPath(const char* file_path);


public:
	void LoadMesh(const aiScene* scene);
	bool LoadMaterial(const aiScene* scene);

	aiString path;
	std::vector<aiMesh*> meshes;
	std::vector<unsigned> textures;
};

