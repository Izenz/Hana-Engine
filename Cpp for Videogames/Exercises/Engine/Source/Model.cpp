#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Load(const char* file_name) {
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene) {
		LoadMesh(scene);
		LoadMaterial(scene);
		
		return true;
	}
	else {
		LOG("Error Loading %s: %s", file_name, aiGetErrorString());
		return false;
	}
}


void Model::LoadMesh(const aiScene* scene) {
	meshes.reserve(scene->mNumMeshes);

	for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
		meshes.push_back(scene->mMeshes[i]);
	}
}

bool Model::LoadMaterial(const aiScene* scene) {
	textures.reserve(scene->mNumMaterials);

	for (unsigned i = 0; i < scene->mNumTextures; ++i) {
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
			textures.push_back(App->textures->LoadTexture(path.data));
		}
		else {
			return false;
		}
	}
	
	return true;
}

void Model::SetPath(const char* file_path) {
	path.Set(file_path);
}