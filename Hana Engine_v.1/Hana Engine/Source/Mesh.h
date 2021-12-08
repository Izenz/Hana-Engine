#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include "GL/glew.h"
#include "MathGeoLib.h"
#include <assert.h>
#include <vector>
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "ModuleEditorCamera.h"


class Mesh{
public:
	Mesh();
	~Mesh();

	bool Load(aiMesh* mesh);
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<Texture>& model_textures);

private:
	unsigned vbo = 0, ebo = 0, vao = 0;
	unsigned num_indices = 0;
	unsigned num_vertices = 0;

	bool isLoaded = false;
};

