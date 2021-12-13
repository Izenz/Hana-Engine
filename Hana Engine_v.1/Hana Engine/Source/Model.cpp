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

bool Model::Load(const char* file_name) {
	const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate);
	LOG("Loading model... : %s", file_name);
	//Output->Print("Loading model... : %s \n", file_name);

	//tex_path = texture_path;
	model_file_path = file_name;
	model_directory_path = model_file_path.substr(0, model_file_path.find_last_of("/\\") + 1);

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
			LOG("Error returning mesh n: %d from %s: %s", i, model_file_path, aiGetErrorString());
			return false;
		}
	}
	//LoadBoundingBox(scene);
	return true;
}

bool Model::LoadTexture(const aiScene* scene) {
	textures.reserve(scene->mNumMaterials);

	if (scene->mNumMaterials > 0) {
		for (unsigned i = 0; i < scene->mNumMaterials; ++i) {
			if(FindAndLoadTexture(scene->mMaterials[0])){
				return true;
			}
			else {
				LOG("\nError loading texture for %s: %s", model_file_path, aiGetErrorString());
				return false;
			}
		}
	}
	return true;
}

bool Model::FindAndLoadTexture(const aiMaterial* mat) {
	aiString path;
	if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
		std::string model_texture_data(path.data);
		std::string texture_file_name = model_texture_data.substr(model_texture_data.find_last_of("/\\") + 1);
		std::string default_textures_folder("Textures/");

		Texture texture = App->textures->Load(path.data);
		if (!texture.isLoaded) {
			LOG("Failed loading texture specified by model data: %s", texture.path);
			texture = App->textures->Load((model_directory_path + texture_file_name).c_str());
		}
		if (!texture.isLoaded) {
			LOG("Failed loading texture from model file directory: %s", texture.path);
			texture = App->textures->Load((default_textures_folder + texture_file_name).c_str());
		}
		if (!texture.isLoaded) {
			LOG("Failed to load texture from default Texture folder: %s", texture.path);
			return false;
		}
		textures.push_back(texture);
		LOG("Texture loaded from: %s", texture.path);
		return true;
	}
	LOG("Error. Path to texture not found.");
	return false;
}

void Model::LoadBoundingBox(const aiScene* scene) {
	std::vector<vec> vertices;

	unsigned numOfVertices = 0;
	if (scene->mNumMeshes > 0) {
		for (unsigned m = 0; m < scene->mNumMeshes; ++m) {
			for (unsigned v = 0; v < scene->mMeshes[m]->mNumVertices; ++v) {
				vertices.push_back(vec(scene->mMeshes[m]->mVertices[v].x, scene->mMeshes[m]->mVertices[v].y, scene->mMeshes[m]->mVertices[v].z));
			}
			numOfVertices += scene->mMeshes[m]->mNumVertices;
		}
	}
	boundingBox = OBB::OptimalEnclosingOBB(&vertices[0], numOfVertices);
}

void Model::Draw() const {
	for (Mesh m : meshes) {
		m.Draw(textures);
	}
}

bool Model::IsLoaded() const {
	return model_loaded;
}

void Model::CleanUp() {
	for (Mesh m : meshes)
		m.~Mesh();
	meshes.clear();
	model_loaded = false;

	for (Texture t : textures)
		t.~Texture();
	textures.clear();
	tex_loaded = false;
	
}