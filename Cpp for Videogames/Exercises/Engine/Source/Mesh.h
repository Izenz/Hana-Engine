#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include "GL/glew.h"
#include "MathGeoLib.h"
#pragma once

class Mesh
{

public:
	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);

private:
	unsigned vbo = 0, ebo = 0;

	unsigned num_indices = 0;
	unsigned num_vertices = 0;

};

