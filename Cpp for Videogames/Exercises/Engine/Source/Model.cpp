#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "Mesh.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Load(const char* file_name, const char* texture_path) {
	const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate);
	LOG("Loading meshes... : %s", aiGetErrorString());
	tex_path = texture_path;

	if (scene) {
		model_loaded = LoadMesh(scene);
		tex_loaded = LoadTexture(scene);
		return true;
	}
	else {
		LOG("Error Loading %s: %s", file_name, aiGetErrorString());
		return false;
	}
}


bool Model::LoadMesh(const aiScene* scene) {
	meshes.reserve(scene->mNumMeshes);

	for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
		Mesh mesh;
		if (mesh.Load(scene->mMeshes[i])) {
			meshes.push_back(mesh);
		}
		else {
			LOG("Error returning mesh n: %d from %s: %s", i, path, aiGetErrorString());
			return false;
		}
	}

	return true;
}

bool Model::LoadTexture(const aiScene* scene) {
	textures.reserve(scene->mNumMaterials);

	if (scene->mNumTextures > 0) {
		for (unsigned i = 0; i < scene->mNumTextures; ++i) {
			if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				Texture texture = App->textures->Load(path.data);
				if (texture.isLoaded)	textures.push_back(texture);
			}
			else {
				LOG("Error loading texture from %s: %s", path, aiGetErrorString());
				return false;
			}
		}
	}
	else {
		Texture texture = App->textures->Load(tex_path);
		textures.push_back(texture);
	}
	

	return true;
}


void Model::Draw() {
	for (Mesh m : meshes) {
		m.Draw(textures);
	}
}

bool Model::IsLoaded() {
	return model_loaded;
}

void Model::CleanUp() {
	meshes.clear();
	textures.clear();
}